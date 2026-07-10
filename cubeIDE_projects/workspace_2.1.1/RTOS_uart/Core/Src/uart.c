//#include "uart.h"
//#include "string.h"
//#include "cmsis_os.h"

#include "main.h"
#include "string.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "shm.h"
#include "uart.h"

#define RX_BUF_SIZE 256
#define TX_BUF_SIZE 256

volatile char rx_buffer[RX_BUF_SIZE];
volatile uint16_t rx_head = 0;
volatile uint16_t rx_tail = 0;

volatile char tx_buffer[TX_BUF_SIZE];
volatile uint16_t tx_head = 0;
volatile uint16_t tx_tail = 0;

extern SemaphoreHandle_t shm_mutex;
extern SystemSharedData_t RPi_Shared_Data;

// 하드웨어 UART3 초기화 (기존 성공하신 레지스터 설정 유지)
void UART3_Init(void) {
    RCC->AHB1ENR |= (0x1 << 3);  // GPIOD clk enable
    RCC->APB1ENR |= (0x1 << 18); // UART3 clk enable

    GPIOD->MODER &= ~((0x3 << 8*2) | (0x3 << 9*2));
    GPIOD->MODER |=  ((0x2 << 8*2) | (0x2 << 9*2));  // AF mode
    GPIOD->AFR[1] = ((GPIOD->AFR[1] & ~(0xff<<0)) | (0x77<<0));
    GPIOD->OSPEEDR |= ((0x3 << 8*2) | (0x3 << 9*2));

    USART3->CR1 |= (0x1 << 13);  // UART3 enable
    USART3->CR1 &= ~(0x1 << 12); // 8bit length set
    USART3->CR2 &= ~(0x3 << 12); // stop bit 1 length
    USART3->BRR = 0x16D;         // 42MHz 기준 115200

    USART3->CR1 |= (0x1 << 5);   // RXNEIE 활성화
    USART3->CR1 &= ~(0x1 << 7);  // TXEIE 초기 비활성화

    NVIC_SetPriority(USART3_IRQn, 5); // FreeRTOS 안전 우선순위
    NVIC_EnableIRQ(USART3_IRQn);

    USART3->CR1 |= (0x3 << 2);   // Tx, Rx Enable
}

// 인터럽트 1Byte 송신
void UART3_Send_Byte_IT(char ch) {
    uint16_t next_head = (tx_head + 1) % TX_BUF_SIZE;
    while (next_head == tx_tail); // 버퍼 Full 대기

    tx_buffer[tx_head] = ch;
    tx_head = next_head;
    USART3->CR1 |= (0x1 << 7); // TXEIE 활성화
}

// 인터럽트 핸들러
void USART3_IRQHandler(void) {
    uint32_t sr = USART3->SR;
    uint32_t cr1 = USART3->CR1;

    // 수신 인터럽트
    if ((sr & (0x1 << 5)) && (cr1 & (0x1 << 5))) {
        char rx_data = (char)(USART3->DR & 0xFF);
        uint16_t next_head = (rx_head + 1) % RX_BUF_SIZE;
        if (next_head != rx_tail) {
            rx_buffer[rx_head] = rx_data;
            rx_head = next_head;
        }
    }

    // 송신 인터럽트
    if ((sr & (0x1 << 7)) && (cr1 & (0x1 << 7))) {
        if (tx_head != tx_tail) {
            USART3->DR = tx_buffer[tx_tail];
            tx_tail = (tx_tail + 1) % TX_BUF_SIZE;
        } else {
            USART3->CR1 &= ~(0x1 << 7);
        }
    }
}

// 링 버퍼에 쌓인 데이터 바이트 수 확인
static uint16_t Get_RX_Buffer_Count(void) {
    if (rx_head >= rx_tail) return rx_head - rx_tail;
    return (RX_BUF_SIZE - rx_tail) + rx_head;
}

// 링 버퍼에서 1바이트 꺼내기 (Non-blocking)
static uint8_t Pop_RX_Byte(uint8_t *byte) {
    if (rx_head == rx_tail) return 0;
    *byte = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % RX_BUF_SIZE;
    return 1;
}

// 통신 Task 초기화
void UART_Task_Init(void) {
    UART3_Init();
}

#define RX_SOF 0xBB  // 패킷 시작 바이트 정의

void StartUARTTask(void *argument) {
    (void)argument;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(50);

    StR_Packet_t tx_pkt;
    tx_pkt.sof = 0xAA; // 송신 SOF (0xAA)

    RtS_Packet_t rx_pkt;
    uint8_t rx_temp_buf[sizeof(RtS_Packet_t)];
    uint8_t rx_idx = 0;
    uint8_t searching = 1; // 0xBB를 찾고 있는 상태인지 나타내는 플래그

    for(;;) {
        /* [1. 수신 처리] 바이트 스트림 파싱 */
        while (Get_RX_Buffer_Count() > 0) {
            uint8_t byte;
            Pop_RX_Byte(&byte);

            // 1. SOF(0xBB) 탐색 단계
            if (searching) {
                if (byte == RX_SOF) {
                    searching = 0; // SOF 발견! 이제 데이터 수신 모드로 전환
                    rx_idx = 0;    // 데이터 인덱스 초기화
                }
                continue; // SOF가 아니면 무시하고 다음 바이트로
            }

            // 2. 데이터 수신 단계
            rx_temp_buf[rx_idx++] = byte;

            // 요구사항 패킷 크기 도달 시
            if (rx_idx == sizeof(RtS_Packet_t)) {
                memcpy(&rx_pkt, rx_temp_buf, sizeof(RtS_Packet_t));

                // 공유 메모리 업데이트 (Mutex 사용)
                if (shm_mutex != NULL && xSemaphoreTake(shm_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
                    RPi_Shared_Data.module_type       = (ModuleType_t)rx_pkt.module_type;
                    RPi_Shared_Data.module_id         = rx_pkt.module_id;
                    RPi_Shared_Data.granted_power_w   = rx_pkt.granted_power_w;
                    RPi_Shared_Data.target_temp_c     = rx_pkt.target_temp_c;
                    RPi_Shared_Data.target_speed_rpm  = rx_pkt.target_speed_rpm;
                    RPi_Shared_Data.warning_flag      = rx_pkt.warning_flag;
                    xSemaphoreGive(shm_mutex);

                    if(RPi_Shared_Data.target_temp_c == 0.5f)
                    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
                }

                // 패킷 처리 완료 후 다음 SOF를 찾기 위해 초기화
                rx_idx = 0;
                searching = 1;
            }
        }

        /* [2. 송신 처리] 주도적 주기적 송신 (50ms) */
        // ... (이하 동일: 송신 로직은 유지)
        if (shm_mutex != NULL && xSemaphoreTake(shm_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
            tx_pkt.module_type       = (uint32_t)RPi_Shared_Data.module_type;
            tx_pkt.module_id         = RPi_Shared_Data.module_id;
            tx_pkt.reported_power_w  = RPi_Shared_Data.reported_power_w;
            tx_pkt.current_pressure  = RPi_Shared_Data.pressure_value;
            tx_pkt.current_temp_c    = RPi_Shared_Data.current_temp_c;
            tx_pkt.current_speed_rpm = RPi_Shared_Data.current_speed_rpm;
            tx_pkt.warning_flag      = RPi_Shared_Data.warning_flag;
            xSemaphoreGive(shm_mutex);

            uint8_t *ptr = (uint8_t*)&tx_pkt;
            for (size_t i = 0; i < sizeof(StR_Packet_t); i++) {
                UART3_Send_Byte_IT((char)ptr[i]);
            }
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
