/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
#include "stm32f103x6.h"
#include "stm32f103C6_GPIO.h"
#include "keypad.h"
#include "lcd.h"

typedef volatile unsigned int vuint32_t;

#define ZERO 0x01
#define ONE 0x79
#define TWO 0x24
#define THREE 0x30
#define FOUR 0x4C
#define FIVE 0x12
#define SIX 0x02
#define SEVEN 0x19
#define EIGHT 0x00
#define NINE 0x10


void Clock_init(){
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
}

void GPIO_init(){
	GPIO_PinConfig_t PinCFG;

	PinCFG.GPIO_PinNumber = GPIOx_PIN_9;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(GPIOB, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_10;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(GPIOB, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_11;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(GPIOB, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_12;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(GPIOB, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_13;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(GPIOB, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_14;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(GPIOB, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_15;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(GPIOB, &PinCFG);
}



int main(void)
{
	Clock_init();
	LCD_INIT();

	LCD_WRITE_STRING("hey there");
	wait(50);
	LCD_clear_screen();

	GPIO_init();


	unsigned char key_pressed;
	unsigned char LCD_DISPLAY [11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
	unsigned char DISPLAY [11] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};
	for(unsigned char i = 0; i < 11; i++){
		MCAL_GPIO_WritePort(GPIOB, DISPLAY[i]<<9);
		LCD_WRITE_CHAR(LCD_DISPLAY[i]);
		wait(50);
	}
	LCD_clear_screen();

	Keypad_init();
	LCD_WRITE_STRING("Keypad ready!");
	wait(50);
	LCD_clear_screen();

	while(1){
		key_pressed = Keypad_getkey();
		switch(key_pressed){
		case 'A':
			break;
		case '?':
			LCD_clear_screen();
			break;
		default:
			LCD_WRITE_CHAR(key_pressed);
			break;
		}

		//    	if(MCAL_GPIO_ReadPin(GPIOA, GPIOx_PIN_1) == 0){
		//    		MCAL_GPIO_TogglePin(GPIOB, GPIOx_PIN_1);
		//    		while(MCAL_GPIO_ReadPin(GPIOA, GPIOx_PIN_1) == 0);
		//    	}
		//    	if(MCAL_GPIO_ReadPin(GPIOA, GPIOx_PIN_13) == 1){
		//    		MCAL_GPIO_TogglePin(GPIOB, GPIOx_PIN_13);
		//    	}
		//    	wait(1);
	}
}

