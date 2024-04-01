/*
 * stm32f103C6_USART.c
 *
 *  Created on: Mar 27, 2024
 *      Author: dell
 */


//includes
#include "stm32f103C6_USART.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
UART_Config* global_UART_Config[3] = {NULL,NULL,NULL};

/*
 * =======================================================================================
 * 							Generic MACROS
 * =======================================================================================
 */

#define USART1_Index		0
#define USART2_Index		1
#define USART3_Index		2

/*
 * =======================================================================================
 * 							APIs
 * =======================================================================================
 */

/**===================================================
 *  @Fn -  MCAL_UART_Init
 *  @brief - Initialize the UART (Supported feature ASYNCH Only_
 *  @param [in] - UARTx :
 *  @param [in] - Config:
 *  @retval - none
 *  Note -
 **/
void MCAL_UART_Init(USART_typedef* USARTx, UART_Config* Config){

	uint32_t pclk, BRR;
	// Enable the clock for given USART peripheral
	if(USARTx == USART1){
		global_UART_Config[USART1_Index] = Config;
		RCC_USART1_CLK_EN();
	}
	else if(USARTx == USART2){
		global_UART_Config[USART2_Index] = Config;
		RCC_USART2_CLK_EN();
	}
	else if(USARTx == USART3){
		global_UART_Config[USART3_Index] = Config;
		RCC_USART3_CLK_EN();
	}

	// Enable USART Module
	//Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13;
	// Enable TX/RX
	USARTx->CR1 |= Config->USART_Mode;
	// Payload length
	USARTx->CR1 |= Config->Payload_Length;
	// Parity
	USARTx->CR1 |= Config->Parity;
	// stop bits
	USARTx->CR2 |= Config->StopBit;
	//Flow Control
	USARTx->CR3 |= Config->FlowControl;

	// Configure baud rate
	//PCLK1 for USART2,3
	//PCLK2 for USART1
	if(USARTx == USART1){
		pclk = MCAL_RCC_GETPCLK2Freq();
	}
	else{
		pclk = MCAL_RCC_GETPCLK1Freq();
	}

	BRR = UART_BRR_Register(pclk, Config->USART_BaudRate);
	USARTx->BRR = BRR;

	// Interrupt Enable/Disable
	if(Config->IRQ_Enable != UART_IRQ_Enable_NONE){
		USARTx->CR1 |= Config->IRQ_Enable;

		//Enable NVIC for USARTx IRQ
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;
		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable;
		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable;
	}

}
/**===================================================
 *  @Fn -  MCAL_UART_DeInit
 *  @brief - DeInitialize the UART (Supported feature ASYNCH. Only)
 *  @param [in] - UARTx :
 *  @retval - none
 *  Note -Reset the Model By RCC
 **/
void MCAL_UART_DeInit(USART_typedef* USARTx){
	if(USARTx == USART1){
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART2){
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_Disable;
	}
	else if(USARTx == USART3){
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_Disable;
	}
}
/**===================================================
 *  @Fn -  MCAL_UART_GPIO_Pins
 *  @brief -
 *  @param [in] - USARTx :
 *  @retval - none
 *  Note -
 **/
void MCAL_UART_GPIO_Pins(USART_typedef* USARTx){
	GPIO_PinConfig_t PinCFG;
	if(USARTx == USART1){
		// PA9 TX
		PinCFG.GPIO_PinNumber = GPIOx_PIN_9;
		PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOA, &PinCFG);
		// PA10 RX
		PinCFG.GPIO_PinNumber = GPIOx_PIN_10;
		PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		// CTS & RTS
		if(global_UART_Config[USART1_Index]->FlowControl == UART_FlowControl_CTS_Enable || global_UART_Config[USART1_Index]->FlowControl == UART_FlowControl_RTS_CTS){
			//PA11 CTS
			PinCFG.GPIO_PinNumber = GPIOx_PIN_11;
			PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
		if(global_UART_Config[USART1_Index]->FlowControl == UART_FlowControl_RTS_Enable || global_UART_Config[USART1_Index]->FlowControl == UART_FlowControl_RTS_CTS){
			//PA12 CTS
			PinCFG.GPIO_PinNumber = GPIOx_PIN_12;
			PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
	}
	else if(USARTx == USART2){
		// PA2 TX
		PinCFG.GPIO_PinNumber = GPIOx_PIN_2;
		PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		// PA3 RX
		PinCFG.GPIO_PinNumber = GPIOx_PIN_3;
		PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		// CTS & RTS
		if(global_UART_Config[USART2_Index]->FlowControl == UART_FlowControl_CTS_Enable || global_UART_Config[USART2_Index]->FlowControl == UART_FlowControl_RTS_CTS){
			//PA0 CTS
			PinCFG.GPIO_PinNumber = GPIOx_PIN_0;
			PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
		if(global_UART_Config[USART2_Index]->FlowControl == UART_FlowControl_RTS_Enable || global_UART_Config[USART2_Index]->FlowControl == UART_FlowControl_RTS_CTS){
			//PA1 CTS
			PinCFG.GPIO_PinNumber = GPIOx_PIN_1;
			PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
	}
	else if(USARTx == USART3){
		// PA10 TX
		PinCFG.GPIO_PinNumber = GPIOx_PIN_10;
		PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOB, &PinCFG);

		// PA11 RX
		PinCFG.GPIO_PinNumber = GPIOx_PIN_11;
		PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &PinCFG);

		// CTS & RTS
		if(global_UART_Config[USART3_Index]->FlowControl == UART_FlowControl_CTS_Enable || global_UART_Config[USART3_Index]->FlowControl == UART_FlowControl_RTS_CTS){
			//PA13 CTS
			PinCFG.GPIO_PinNumber = GPIOx_PIN_13;
			PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCFG);
		}
		if(global_UART_Config[USART3_Index]->FlowControl == UART_FlowControl_RTS_Enable || global_UART_Config[USART3_Index]->FlowControl == UART_FlowControl_RTS_CTS){
			//PA14 CTS
			PinCFG.GPIO_PinNumber = GPIOx_PIN_14;
			PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOB, &PinCFG);
		}
	}
}
/**===================================================
 *  @Fn -   MCAL_UART_SendData
 *  @brief -
 *  @param [in] - USARTx :
 *  @param [in] - pTxBuffer:
 *  @param [in] -  PollingEn:
 *  @retval - none
 *  Note -
 **/
void MCAL_UART_SendData(USART_typedef* USARTx, uint16_t* pTxBuffer, enum Polling_mechanism PollingEn){
	uint8_t x;
	if(USARTx == USART1)
		x = USART1_Index;
	else if(USARTx == USART2)
		x = USART2_Index;
	else if(USARTx == USART3)
		x = USART3_Index;
	// wait until TXE is set
	if(PollingEn == enable){
		while(!(USARTx->SR & 1<<7));
	}
	//check word length 9-bit or 8-bit
	if(global_UART_Config[x]->Payload_Length == UART_Payload_Length_9B)
		USARTx->DR = (*pTxBuffer & (uint16_t) 0x01FF);
	else
		USARTx->DR = (*pTxBuffer & (uint8_t) 0xFF);
}
/**===================================================
 *  @Fn -   MCAL_UART_ReceiveData
 *  @brief -
 *  @param [in] - USARTx :
 *  @param [in] - pTxBuffer:
 *  @param [in] -  PollingEn:
 *  @retval - none
 *  Note -
 **/
void MCAL_UART_ReceiveData(USART_typedef* USARTx, uint16_t* pTxBuffer, enum Polling_mechanism PollingEn){
	uint8_t x;
	if(USARTx == USART1)
		x = USART1_Index;
	else if(USARTx == USART2)
		x = USART2_Index;
	else if(USARTx == USART3)
		x = USART3_Index;
	// wait until RXNE flag is set
	if(PollingEn == enable)
		while(!(USARTx->SR & 1<<5));
	if(global_UART_Config[x]->Payload_Length == UART_Payload_Length_9B){
		if(global_UART_Config[x]->Parity == UART_Parity_NONE){
			// No parity so all 9 bits are data
			*((uint16_t*)pTxBuffer) = USARTx->DR;
		}
		else{
			*((uint16_t*)pTxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
	}
	else{
		if(global_UART_Config[x]->Parity == UART_Parity_NONE){
			// No parity so all 9 bits are data
			*((uint16_t*)pTxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
		else{
			*((uint16_t*)pTxBuffer) = (USARTx->DR & (uint8_t)0x7F);
		}
	}
}
/**===================================================
 *  @Fn -  MCAL_UART_WAIT_TC
 *  @brief -
 *  @param [in] - USARTx :
 *  @retval - none
 *  Note -
 **/
void MCAL_UART_WAIT_TC(USART_typedef* USARTx){
	while(!(USARTx->SR & 1<<6));
}

//------------ISR
void USART1_IRQHandler(void){
	global_UART_Config[USART1_Index]->P_IRQ_CallBack();
}
void USART2_IRQHandler(void){
	global_UART_Config[USART2_Index]->P_IRQ_CallBack();
}
void USART3_IRQHandler(void){
	global_UART_Config[USART3_Index]->P_IRQ_CallBack();
}
