/*
 * ledon.c
 *
 *  Created on: 2026. 5. 1.
 *      Author: kanaw
 */

#include "led.h"

int LED_init(void){

	// GPIOB CLK  active
	RCC_AHB1ENR |= (0x1 << 1);

	/* GPIO B pin config*/
	// pin output setting
    GPIOB_MODER &= ~((3 << (LD1_PIN * 2))|(3 << (LD2_PIN * 2))|(3 << (LD3_PIN * 2)));
    GPIOB_MODER |=  (1 << (LD1_PIN * 2))|(1 << (LD2_PIN * 2))|(1 << (LD3_PIN * 2));

    // push pull setting
    GPIOB_OTYPER &=  ~((1 << (LD1_PIN))|(1 << (LD2_PIN))|(1 << (LD3_PIN)));

    // speed low
    GPIOB_OSPEED &= ~((3 << (LD1_PIN * 2))|(3 << (LD2_PIN * 2))|(3 << (LD3_PIN * 2)));

    // pin floating
    GPIOB_PUPD &= ~((3 << (LD1_PIN * 2))|(3 << (LD2_PIN * 2))|(3 << (LD3_PIN * 2)));

    //alternative function don't use
    GPIOB_AFRL &= ~((0xF << (LD1_PIN * 4))|(0xF << (LD2_PIN * 4)));
    GPIOB_AFRH &= ~((0xF << ((LD3_PIN - 8) * 4)));

    return 0;
}

int SW_init(void){
	RCC_AHB1ENR |= (0x1 << 2);
    /* GPIO C pin config*/
    // pin input setting
    GPIOC_MODER &= ~((3 << (SW1_PIN * 2)));

    // pin floating
    GPIOC_PUPD &= ~((3 << (SW1_PIN * 2)));

    //alternative function don't use
    GPIOC_AFRH &= ~((0xF << ((SW1_PIN - 8) * 4)));

	return 0;
}


void LED_ctrl(int num, int flag){
	if ((flag != LEDOFF) && (flag != LEDON) && (num != LED_1) && (num != LED_2) && (num != LED_3)){
		return;
	}

	if (flag == LEDON){
		GPIOB_ODR |= (1 << num);
	}
	if (flag == LEDOFF){
		GPIOB_ODR &= ~(1 << num);
	}
}

int SW_ON(){
	return ((GPIOC_IDR >> SW1_PIN) & 1);
}
