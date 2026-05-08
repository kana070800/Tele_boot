/*
 * led.h
 *
 *  Created on: 2026. 5. 1.
 *      Author: kanaw
 */
#ifndef __LEDH__
#define __LEDH__

#define RCC_AHB1ENR   (*(volatile unsigned int *)0x40023830)
#define GPIOB_MODER   (*(volatile unsigned int *)0x40020400)
#define GPIOB_OTYPER  (*(volatile unsigned int *)0x40020404)
#define GPIOB_OSPEED  (*(volatile unsigned int *)0x40020408)
#define GPIOB_PUPD    (*(volatile unsigned int *)0x4002040C)
#define GPIOB_LCKR    (*(volatile unsigned int *)0x4002041C)
#define GPIOB_AFRL    (*(volatile unsigned int *)0x40020420)
#define GPIOB_AFRH    (*(volatile unsigned int *)0x40020424)

#define GPIOB_BSRR    (*(volatile unsigned int *)0x40020418)
#define GPIOB_ODR    (*(volatile unsigned int *)0x40020414)

#define GPIOC_MODER   (*(volatile unsigned int *)0x40020800)
#define GPIOC_PUPD    (*(volatile unsigned int *)0x4002080C)
#define GPIOC_IDR    (*(volatile unsigned int *)0x40020810)
#define GPIOC_LCKR    (*(volatile unsigned int *)0x4002081C)
#define GPIOC_AFRL    (*(volatile unsigned int *)0x40020820)
#define GPIOC_AFRH    (*(volatile unsigned int *)0x40020824)

// LED 핀 위치 정의
#define LD1_PIN 0   // PB0
#define LD2_PIN 7   // PB7
#define LD3_PIN 14  // PB14

#define SW1_PIN 13  // PC13


enum{
	LEDON = 0,
	LEDOFF
};

enum LED{
	LED_1 = 0,
	LED_2 = 7,
	LED_3 = 14
};


int LED_init(void);
int SW_init(void);
void LED_ctrl(int num, int flag);
int SW_ON();


#endif
