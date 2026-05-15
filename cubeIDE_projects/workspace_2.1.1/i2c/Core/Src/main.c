#include "stm32f4xx.h"

/* --- LCD 및 I2C 설정 --- */
#define SLAVE_ADDR     0x27    // LCD 주소가 0x3F인 경우 수정 필요
#define RS_BIT         0x01    // P0: Register Select
#define EN_BIT         0x04    // P2: Enable
#define BACKLIGHT      0x08    // P3: Backlight On

/* --- 함수 선언 --- */
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void I2C1_Config(void);
void I2C1_Write(uint8_t data);
void LCD_Send(uint8_t data, uint8_t flags);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Init(void);
void LCD_Print(char *str);

/* --- 메인 함수 --- */
int main(void) {
    // 하드웨어 초기화
    I2C1_Config();
    LCD_Init();

    // 초기 화면 출력
    LCD_Command(0x80); // 1행 시작
    LCD_Print("Nucleo-F429ZI");
    LCD_Command(0xC0); // 2행 시작
    LCD_Print("I2C1 PB8/PB9 OK");

    while (1) {
        // 어플리케이션 루프
    }
}

/* --- I2C1 설정 (PB8: SCL, PB9: SDA) --- */
void I2C1_Config(void) {
    // 1. GPIOB 및 I2C1 클럭 활성화
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // 2. GPIO PB8, PB9 설정 (Alternate Function 모드)
    GPIOB->MODER   &= ~((3 << (8 * 2)) | (3 << (9 * 2)));
    GPIOB->MODER   |=  ((2 << (8 * 2)) | (2 << (9 * 2)));

    GPIOB->OTYPER  |=  (1 << 8) | (1 << 9);               // Open-Drain [cite: 236]
    GPIOB->OSPEEDR |=  (3 << (8 * 2)) | (3 << (9 * 2));   // High Speed
    GPIOB->PUPDR   |=  (1 << (8 * 2)) | (1 << (9 * 2));   // Pull-up

    // 3. AF4 (I2C1) 설정 - PB8, PB9는 AFRH(AFR[1]) 레지스터 사용
    GPIOB->AFR[1] &= ~((0xF << (0 * 4)) | (0xF << (1 * 4)));
    GPIOB->AFR[1] |=  ((4 << (0 * 4)) | (4 << (1 * 4)));

    // 4. I2C1 주변장치 통신 설정 (100kHz)
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2 = 45;       // APB1 클럭 45MHz 가정
    I2C1->CCR = 225;      // Standard Mode 100kHz [cite: 543]
    I2C1->TRISE = 46;
    I2C1->CR1 |= I2C_CR1_PE;
}

/* --- I2C 데이터 전송 (레지스터 직접 제어) --- */
void I2C1_Write(uint8_t data) {
    // START 신호 [cite: 379]
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // 주소 전송 [cite: 369]
    I2C1->DR = (SLAVE_ADDR << 1);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2; // ADDR 플래그 클리어

    // 데이터 전송 [cite: 362]
    I2C1->DR = data;
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    // STOP 신호 [cite: 418]
    I2C1->CR1 |= I2C_CR1_STOP;
}

/* --- LCD로 4비트 데이터 전송 --- */
void LCD_Send(uint8_t data, uint8_t flags) {
    uint8_t up = (data & 0xF0) | flags | BACKLIGHT;
    uint8_t lo = ((data << 4) & 0xF0) | flags | BACKLIGHT;

    // 상위 4비트 전송 (Enable Pulse 포함)
    I2C1_Write(up | EN_BIT);
    Delay_us(1);
    I2C1_Write(up & ~EN_BIT);
    Delay_us(50);

    // 하위 4비트 전송
    I2C1_Write(lo | EN_BIT);
    Delay_us(1);
    I2C1_Write(lo & ~EN_BIT);
    Delay_us(50);
}

void LCD_Command(uint8_t cmd) {
    LCD_Send(cmd, 0);
}

void LCD_Data(uint8_t data) {
    LCD_Send(data, RS_BIT);
}

/* --- LCD 초기화 (PCF8574/HD44780 시퀀스) --- */
void LCD_Init(void) {
    Delay_ms(50);

    // 4비트 모드 진입 시퀀스
    LCD_Command(0x33);
    Delay_ms(5);
    LCD_Command(0x32);

    // 동작 설정
    LCD_Command(0x28); // 2라인, 5x8 폰트
    LCD_Command(0x0C); // 디스플레이 ON, 커서 OFF
    LCD_Command(0x01); // 화면 클리어
    Delay_ms(2);
    LCD_Command(0x06); // 엔트리 모드: 커서 우측 이동
}

void LCD_Print(char *str) {
    while (*str) LCD_Data(*str++);
}

/* --- 지연 함수 --- */
void Delay_us(uint32_t us) {
    uint32_t count = us * 45;
    while (count--);
}

void Delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) Delay_us(1000);
}
