/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;

TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim9;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM9_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
volatile unsigned int flag_sw = 0;
volatile int USART3_flag = 0;
volatile uint8_t systick_flag = 0;
volatile char ch;

void UART3_Send_Byte(char ch);
static void SysTick_Interrupt_Init(void);


int main(void)
{
  SystemClock_Config();

  MX_GPIO_Init();

  SysTick_Interrupt_Init();

  //-----------------------------------------------exti
  RCC->AHB1ENR |= (3 << 1);

	/*gpio B out mode 설정*/
  GPIOB->MODER &= ~(3 << (7 * 2));
  GPIOB->MODER |=  (1 << (7 * 2));


  SYSCFG->EXTICR[3] &= ~(0xF << 4);
  SYSCFG->EXTICR[3] |=  (0x1 << 5);
  EXTI->RTSR |= (1<<13);
  EXTI->IMR |= (1<<13);

  //----------------------------------------uart
  /* USER CODE BEGIN 2 */

  // [1] CLOCK Enable : GPD, UART3
  RCC->AHB1ENR |= 0x1 << 3;        //    GPD CLOCK Enable
  RCC->APB1ENR |= 0x1 << 18;    //    UART3 CLOCK Enable

  // [2] Pin config : AF, MUX : UART3
  // PD8(TX) OUTPUT PP
  // PD9(RX) INPUT FLOATING
  // PD8, PD9 -> AF:0x7
  GPIOD->MODER = (GPIOD->MODER & ~(0xF << 16)) | (0xa << 16);
  GPIOD->AFR[1] = ((GPIOD->AFR[1] & ~(0xFF << 0)) | (0x77 << 0));

  // baudrate, frame : 115200, 8bit, stop:1, parity:none
  double div;
  unsigned int baud=115200, pclk1 = 42000000;
  unsigned int mant, frac;

  div = ((double)pclk1 / (8.0 * 2 * baud));
  mant = ((unsigned int)div);                //    정수부 저장
  frac = ((unsigned int)(div-mant)*8.0 * 2 + 0.5);    //    소수부를 정수로 변환해서 *8 저장 + 반올림

  // frac 반올림 결과 8이 되었다면 (ex. 0.999)
  mant += (frac>>4);
  frac = frac & 0xF;

  USART3->BRR = ((mant << 4) | (frac << 0));

  // CR1 : 0:15 / 1:13 / 1:3 / 1:2 + Bits 5번 RXNEIE Enable
  USART3->CR1 |= ( 0<<15 | 1<<13 | 1<<5 |1<<3 | 1<<2 );

  extern volatile int USART3_flag;
  extern volatile char ch;
  //--------------------------------------------------------------------------
  // 1. 클럭 활성화 (GPIOE: bit 4, TIM9: bit 16)
    RCC->AHB1ENR |= (0x1 << 4) ;
    RCC->APB2ENR |= (0x1 << 16);

    // 2. GPIOE 5, 6번 설정
    // MODER: PE5, PE6을 Alternate Function(10)으로 설정
    GPIOE->MODER &= ~( (0x3 << (5*2)) | (0x3 << (6*2)) );
    GPIOE->MODER |=  ( (0x2 << (5*2)) | (0x2 << (6*2)) );

    // AFR: PE5, PE6에 AF3(TIM9) 할당
    // AFR[0]은 AFRL입니다. 5번 핀(bit 20~23), 6번 핀(bit 24~27)
    GPIOE->AFR[0] &= ~( (0xF << (5*4)) | (0xF << (6*4)) );
    GPIOE->AFR[0] |=  ( (0x3 << (5*4)) | (0x3 << (6*4)) );

    // 3. TIM9 설정
    TIM9->PSC  = 167;    // 168MHz 기준 -> 1MHz clock
    TIM9->ARR  = 999;    // 1kHz PWM 주가
    TIM9->CCR1 = 500;    // Duty 50% (ARR이 999이므로 500이 절반입니다)
    TIM9->CCR2 = 250;    // Duty 25% (테스트를 위해 다르게 설정)

    // CCMR1: CH1, CH2를 PWM Mode 1(110)로 설정 일단 mode2번도 존재 하더라
    TIM9->CCMR1 &= ~( (0x7 << 4) | (0x7 << 12) );
    TIM9->CCMR1 |= (6 << 4) | (6 << 12);

    // CCER: 각 채널 출력 활성화 (중요!)
    TIM9->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);

    // CR1: 타이머 시작
    TIM9->CR1 |= TIM_CR1_CEN;



  //-----------------------------------------------------------------------------
  NVIC_EnableIRQ(40) ;
  NVIC_EnableIRQ(39) ;

  while (1)
  {
	  if (flag_sw){
		  GPIOB->ODR ^= (1 << 7);
		  flag_sw = 0;
	  }
      if(USART3_flag == 1)
      {
          USART3_flag = 0;
          UART3_Send_Byte(ch);
      }
      if (systick_flag == 1)
      {
          systick_flag = 0;

          HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
      }
  }
}
//pending은 인터럽트 발생 시 자동으로 set 됩니다
void EXTI15_10_IRQHandler(void) {
        if (EXTI->PR & (1 << 13)) { // 13번 라인 확인
            flag_sw = 1;
            EXTI->PR = (1 << 13);    // Pending bit 클리어 (W1C)
        }
    }

/* USER CODE BEGIN 1 */
void USART3_IRQHandler(void)
{
    USART3_flag = 1;
    ch = USART3->DR;
}
/* USER CODE END 1 */


void UART3_Send_Byte(char ch){
  if (ch=='\r'){                        // new line인 경우  '\n'을 추가전송
      USART3->DR = 0x0a;
      while (((USART3->SR >> 7)&0x1)==0);
      USART3->DR = 0x0d;
      while (((USART3->SR >> 7)&0x1)==0);
  }
  USART3->DR = ch;
  while (((USART3->SR >> 7)&0x1)==0);    // wait TXE
}

void UART3_Send_String(char* p){
    while (*p){
        UART3_Send_Byte(*p++);            // 널문자 전까지 출력
    }
}

static void SysTick_Interrupt_Init(void)
{
    /*
     * CLKSOURCE = 0이므로 SysTick clock = SystemCoreClock / 8
     *
     * HSI 168MHz 기준:
     * SystemCoreClock = 168,000,000
     * SysTick clock   = 21,000,000
     */
    uint32_t systick_clk = SystemCoreClock >> 3;

    /*
     * 0.5초 주기
     *
     * 2MHz 기준:
     * 0.5초 = 10,500,000 count
     * LOAD에는 N - 1
     */
    uint32_t reload_value = (systick_clk >> 1) - 1;

    /*
     * 설정 전에 SysTick 정지
     */
    SysTick->CTRL = 0;

    /*
     * SysTick은 24-bit down counter
     */
    SysTick->LOAD = reload_value & 0x00FFFFFF;

    /*
     * 현재 counter 초기화
     */
    SysTick->VAL = 0;

    /*
     * CLKSOURCE = 0 : AHB/8
     * TICKINT   = 1 : SysTick exception enable
     * ENABLE    = 1 : counter enable
     */
    SysTick->CTRL = (0 << 2) |
                    (1 << 1) |
                    (1 << 0);
}

/*
 * SysTick exception handler
 *
 * 0.5초마다 이 함수로 들어온다.
 * Green LED LD1, PB0 토글.
 */

//#define RCC_AHB1ENR   (*(volatile unsigned int *)0x40023830)
//#define GPIOB_MODER   (*(volatile unsigned int *)0x40020400)
//#define GPIOB_BSRR    (*(volatile unsigned int *)0x40020418)
//#define GPIOB_ODR    (*(volatile unsigned int *)0x40020414)
//#define GPIOC_IDR    (*(volatile unsigned int *)0x40020810)
//
//// LED 핀 위치 정의
//#define LD2_PIN 7   // PB7
//
//#define SW1_PIN 13  // PC13

//int main(void) {
//    /* 0. FPU 활성화 (경고 방지 및 안정성) */
//    (*(volatile unsigned int *)0xE000ED88) |= ((3UL << 20) | (3UL << 22));
//
//    /* 1. GPIOB, C 클럭 활성화 */
//    RCC_AHB1ENR |= (3 << 1); // GPIOB, GPIOC 비트 셋
//
//    /* 2. 핀을 출력 모드(01)로 설정 */
//
//    // PB7 설정
//    GPIOB_MODER &= ~(3 << (LD2_PIN * 2));
//    GPIOB_MODER |=  (1 << (LD2_PIN * 2));
//
//    /* 3. BSRR 레지스터를 사용하여 3개 LED 모두 켜기 (High 출력) */
//
//    volatile unsigned int curr,prev = 0;
////
////	while(1){
////		if(GPIOC_IDR & (1 << SW1_PIN)){ //led on
////			GPIOB_BSRR = (1 << LD2_PIN);
////		}
////		else{ //led off
////			GPIOB_BSRR = (1 << LD2_PIN + 16);
////		}
////	};


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 0;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 65535;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
