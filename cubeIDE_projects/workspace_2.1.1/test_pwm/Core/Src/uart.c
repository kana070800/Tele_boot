
#include "main.h"
#include "stdio.h"
#include "stdarg.h"
#include "uart.h"

void UART3_Init(){
	// clk enable
	RCC->AHB1ENR |= (0x1 << 3); // gpiod clk enable
	RCC->APB1ENR |= (0x1 << 18); // uart3 clk enable

	// GPIO mode
	GPIOD->MODER &= ~((0x3 << 8*2) | (0x3 << 9*2));
	GPIOD->MODER |=  ((0x2 << 8*2) | (0x2 << 9*2));  // AF mode

	GPIOD->AFR[1] = ((GPIOD->AFR[1] & ~(0xff<<0))| (0x77<<0));

	GPIOD->OSPEEDR |= ((0x3 << 8*2) | (0x3 << 9*2));

	//uart setting
	USART3->CR1 |= (0x1 << 13); // uart3 enable
	USART3->CR1 &= ~(0x1 << 12); // 8bit length set

	USART3->CR2 &= ~(0x3 << 12); //stop bit 1 length

	// systemclock_config() 함수 사용시 uart에 42Mhz clk 인가 >> 0x16D
	// systemclock_config() 함수 사용X 시 uart에 16Mhz clk 인가
	USART3->BRR = 0x16D;

	USART3->CR1 |= (0x3 << 2); // Tx, Rx enable
}

void UART3_Send_Byte(char ch){
	if (ch == '\n'){
		USART3->DR = 0x0d; // new line인 경우, '\n' 추가전송
		while(((USART3->SR >> 7) & 0x1) == 0);
	}
	USART3->DR = ch;
	while(((USART3->SR >> 7) & 0x1) == 0); // wait TXE
}

void UART3_Send_String(char* p){
    while (*p){
        UART3_Send_Byte(*p++);
    }
}

uint32_t UART3_Printf(const char* msg, ...){
	va_list args;
	char res_msg[200];
	uint32_t cnt_rtn = 0;
	va_start(args, msg);
	vsprintf(res_msg, msg, args);
	va_end(args);

	UART3_Send_String(res_msg);

	return cnt_rtn; // 출력한 문자 수 반환
}
