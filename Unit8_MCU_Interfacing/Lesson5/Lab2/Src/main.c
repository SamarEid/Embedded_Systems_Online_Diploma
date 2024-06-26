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

/*
 * Terminal1 <----> USART1 : MCU1 : (SPI1 Master) ---> (SPI2 Slave) :MCU2: USART2 ---> Terminal2
*/
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define MCU_Act_As_Slave
//#define MCU_Act_As_Master


#include "stm32f103x6.h"
#include "stm32f103C6_GPIO.h"
#include "stm32f103C6_EXTI.h"
#include "stm32f103C6_RCC.h"
#include "stm32f103C6_USART.h"
#include "stm32f103C6_SPI.h"
#include "keypad.h"
#include "lcd.h"

void Clock_Init(void){
	RCC_GPIOA_CLK_EN(); // GPIOA
	RCC_GPIOB_CLK_EN(); // GPIOB
	RCC_AFIO_CLK_EN();  // AFIO
}

uint16_t ch;

void SPI1_IRQ_CallBack(struct S_IRQ_SRC irq_src)
{
#ifdef MCU_Act_As_Slave
	if(irq_src.RXNE){
		ch = 0xf;
		MCAL_SPI_Tx_Rx(SPI1, &ch, Pollingdisable);
		MCAL_UART_SendData(USART1, &ch, enable);
	}
#endif
}

void UART_IRQ_CallBack(void){
#ifdef MCU_Act_As_Master
	MCAL_UART_ReceiveData(USART1, &ch, disable);
	MCAL_UART_SendData(USART1, &ch, enable);
	MCAL_GPIO_WritePin(GPIOA, GPIOx_PIN_4, GPIO_PIN_Reset);
	MCAL_SPI_Tx_Rx(SPI1, &ch, Pollingenable);
	MCAL_GPIO_WritePin(GPIOA, GPIOx_PIN_4, GPIO_PIN_Set);
#endif
}
int main(void)
{
	UART_Config uartCFG;
	SPI_Config_t spiCFG;
	GPIO_PinConfig_t pinCFG;

	// Enable Clock
	Clock_Init();

	//---------------------UART INIT---------------------------
	// PA9 TX
	// PA10 RX
	//PA11 CTS
	//PA12 CTS
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

	//-----------------SPI INIT--------------------------------
	// SCK	PA5
	// MOSI PA7
	// MISO PA6
	// NSS PA4
	//Common Configuration
	spiCFG.Clk_Phase = SPI_CLK_Phase_Second;
	spiCFG.Clk_Polarity = SPI_CLK_Polarity_1_Idle;
	spiCFG.Data_Size = SPI_Data_Size_8;
	spiCFG.Frame_Format = SPI_Frame_Format_MSB_First;
	//Assume by default pCLK2 = 8MHZ
	spiCFG.Baud_Rate = SPI_fPCLK_Over8;
	spiCFG.Communication_Mode = SPI_Communication_Mode_2Line;

#ifdef MCU_Act_As_Master
	spiCFG.Device_Mode = SPI_Device_Mode_MASTER;
	spiCFG.IRQ_Enable = SPI_IRQ_Disable;
	spiCFG.NSS = SPI_NSS_SW_Set;
	spiCFG.P_IRQ_CallBack = NULL;
	//Configure SS on PA4 by GPIO
	pinCFG.GPIO_PinNumber = GPIOx_PIN_4;
	pinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(GPIOA, &pinCFG);
	//Force the slave select Idle mode (High)
	MCAL_GPIO_WritePin(GPIOA, GPIOx_PIN_4, GPIO_PIN_Set);
#endif
#ifdef MCU_Act_As_Slave
	spiCFG.Device_Mode = SPI_Device_Mode_SLAVE;
	spiCFG.IRQ_Enable = SPI_IRQ_Enable_Rx;
	spiCFG.NSS = SPI_NSS_HW_Slave;
	spiCFG.P_IRQ_CallBack = SPI1_IRQ_CallBack;
#endif

	MCAL_SPI_Init(SPI1, &spiCFG);
	MCAL_SPI_GPIO_Pins(SPI1);



	// loop forever
	while(1){

	}

}

