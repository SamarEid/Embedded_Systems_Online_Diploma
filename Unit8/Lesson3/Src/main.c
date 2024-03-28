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
#include "stm32f103C6_EXTI.h"
#include "stm32f103C6_RCC.h"
#include "stm32f103C6_USART.h"
#include "keypad.h"
#include "lcd.h"

unsigned char ch;


void UART_IRQ_CallBack(void){
	MCAL_UART_ReceiveData(USART1, &ch, disable);
	MCAL_UART_SendData(USART1, &ch, enable);
}

int main(void)
{

	// Enable Clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	UART_Config uartCFG;

	uartCFG.USART_BaudRate = UART_BaudRate_115200;
	uartCFG.FlowControl = UART_FlowControl_None;
	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	uartCFG.P_IRQ_CallBack = UART_IRQ_CallBack;
	uartCFG.Payload_Length = UART_Payload_Length_8B;
	uartCFG.Parity = UART_Parity_NONE;
	uartCFG.StopBit = UART_StopBit_1B;
	uartCFG.USART_Mode = UART_Mode_TX_RX;

	MCAL_UART_Init(USART1, &uartCFG);
	MCAL_UART_GPIO_Pins(USART1);

	while(1){
		//MCAL_UART_ReceiveData(USART1, &ch, enable);
		//MCAL_UART_SendData(USART1, &ch, enable);
	}

}

