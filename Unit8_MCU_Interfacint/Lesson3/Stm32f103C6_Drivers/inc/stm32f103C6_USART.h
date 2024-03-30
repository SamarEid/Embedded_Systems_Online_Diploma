/*
 * stm32f103C6_USART.h
 *
 *  Created on: Mar 27, 2024
 *      Author: dell
 */

#ifndef INC_STM32F103C6_USART_H_
#define INC_STM32F103C6_USART_H_

//includes
#include "stm32f103x6.h"
#include "stm32f103C6_GPIO.h"
#include "stm32f103C6_RCC.h"

//----------------------------
//User type definitions (structures)
//----------------------------
typedef struct{
	uint8_t		USART_Mode;			// Specifies RX/TX Enable/Disable
									// this parameter must be set based on @ref UART_Mode_define

	uint32_t 	USART_BaudRate;		// This member configures the baud rate
									// this parameter must be set based on @ref UART_BaudRate_define

	uint8_t		Payload_Length; 	// Specifies the number of data bits
									// this parameter must be set based on @ref UART_Payload_Length_define

	uint8_t		Parity;				// Specifies the parity mode
									// this parameter must be set based on @ref UART_Parity_define

	uint8_t		StopBit;			// Specifies the number of stop bits
									// @ref UART_StopBit_define

	uint8_t		FlowControl;		// Specifies whether to enable or disable flow control bits
									//@ref UART_FlowControl_define

	uint8_t		IRQ_Enable;			// Enable or Disable interrupt
									//@ref UART_IRQ_Enable_define

	void(*P_IRQ_CallBack)(void);	// Set the Function() which will be called once the IRQ happen

}UART_Config;

//----------------------------
//Macros Configuration References
//----------------------------

/*@ref UART_Mode_define*/

#define UART_Mode_RX						(uint32_t)(1<<2) // Bit 2 RE : Receiver Enable
#define UART_Mode_TX						(uint32_t)(1<<3) // Bit 3 TE : Transmitter Enable
#define UART_Mode_TX_RX						(uint32_t)((1<<2) | (1<<3))
//-------------------------------------------------------------

/*@ref UART_BaudRate_define*/
#define UART_BaudRate_2400					2400
#define UART_BaudRate_9600					9600
#define UART_BaudRate_19200					19200
#define UART_BaudRate_57600					57600
#define UART_BaudRate_115200				115200
#define UART_BaudRate_230400				230400
#define UART_BaudRate_460000				460800
#define UART_BaudRate_921600				921600
#define UART_BaudRate_2250000				2250000
#define UART_BaudRate_4500000				4500000
//-------------------------------------------------------------

/*@ref UART_Payload_Length_define*/
#define UART_Payload_Length_8B				(uint32_t)(0)
#define UART_Payload_Length_9B				(uint32_t)(1<<12)
//-------------------------------------------------------------

/* @ref UART_Parity_define*/
#define UART_Parity_NONE					(uint32_t)(0)
#define UART_Parity_EVEN					(uint32_t)(1<<10)
#define UART_Parity_ODD						(uint32_t)(1<<10 | 1<<9)
//-------------------------------------------------------------

/*@ref UART_StopBit_define*/
#define UART_StopBit_HalfB 					(uint32_t)(1<<12)
#define UART_StopBit_1B						(uint32_t)(0)
#define UART_StopBit_1_HalfB				(uint32_t)(3<<12)
#define UART_StopBit_2B						(uint32_t)(2<<12)
//-------------------------------------------------------------

/*@ref UART_FlowControl_define*/
#define UART_FlowControl_CTS_Enable			(uint32_t)(1<<9)
#define UART_FlowControl_None				(uint32_t)(0)
#define UART_FlowControl_RTS_Enable			(uint32_t)(1<<8)
#define UART_FlowControl_RTS_CTS			(uint32_t)(1<<9 | 1<<8)
//-------------------------------------------------------------

/*@ref UART_IRQ_Enale_define*/
#define UART_IRQ_Enable_NONE				(uint32_t)(0)
#define UART_IRQ_Enable_TXE					(uint32_t)(1<<7)
#define UART_IRQ_Enable_TC					(uint32_t)(1<<6)
#define UART_IRQ_Enable_RXNEIE				(uint32_t)(1<<5)
#define UART_IRQ_Enable_PE					(uint32_t)(1<<8)
//-----------------------------------------------------------------

enum Polling_mechanism{
	disable,
	enable
};
//BaudRate Calculation
//USARTDIV = fclk / (16 * Baudrate)
//USARTDIV_MUL100 =
// uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV  )  * 100
//DIV_Mantissa = Integer Part (USARTDIV  )
//DIV_Fraction = (( USARTDIV_MUL100  - DIV_Mantissa_MUL100  ) * 16 ) / 100

#define USARTDIV(_PCLK_, _BAUD_)							(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_, _BAUD_)					(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )


//-------------------------------------------------------------
//----------APIs Supported By "MCAL USART DRIVER"--------------
//-------------------------------------------------------------

void MCAL_UART_Init(USART_typedef* USARTx, UART_Config* Config);
void MCAL_UART_DeInit(USART_typedef* USARTx);

void MCAL_UART_GPIO_Pins(USART_typedef* USARTx);

void MCAL_UART_SendData(USART_typedef* USARTx, uint16_t *pTxBuffer, enum Polling_mechanism PollingEn);
void MCAL_UART_ReceiveData(USART_typedef* USARTx, uint16_t* pTxBuffer, enum Polling_mechanism PollingEn);

void MCAL_UART_WAIT_TC(USART_typedef* USARTx);


//todo MCAL_USART_LIN_Init()		//LIN
//todo MCAL_USART_Init()			//Synchronous
//todo	MCAL_USART_DMA_Init()		// MultiBuffer Communication
#endif /* INC_STM32F103C6_USART_H_ */
