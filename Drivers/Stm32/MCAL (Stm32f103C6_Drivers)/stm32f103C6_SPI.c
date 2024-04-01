/*
 * stm32f103C6_SPI.c
 *
 *  Created on: Apr 1, 2024
 *      Author: dell
 */

//includes
#include "stm32f103C6_SPI.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
SPI_Config_t *global_SPI_Config[2] = { NULL, NULL };
/*
 * =======================================================================================
 * 							Generic MACROS
 * =======================================================================================
 */
#define SPI1_Index		0
#define SPI2_Index		0

#define SPI_SR_TXE		(uint8_t)(0x02) // transmit buffer empty
#define SPI_SR_RXNE		(uint8_t)(0x02) // Receive buffer not empty

/*
 * =======================================================================================
 * 							APIs
 * =======================================================================================
 */

//Initialization and Deinitialization
/**===================================================
 *  @Fn - MCAL_SPI_Init
 *  @brief - Initialize the SPI according to the specified configurations
 *  @param [in] - SPIx :
 *  @param [in] - SPI_Config:
 *  @retval - none
 *  Note - Supports SPI Full-Duplex Master/Slave only & NSS HW/SW
 *  		- In case of master you have to configure pin and drive it
 **/
void MCAL_SPI_Init(SPI_typedef *SPIx, SPI_Config_t *SPI_Config) {

	// Safety for registers
	uint16_t tmpreg_CR1 = 0;
	uint16_t tmpreg_CR2 = 0;

	// Enable Clock
	if (SPIx == SPI1) {
		global_SPI_Config[SPI1_Index] = SPI_Config;
		RCC_SPI1_CLK_EN();
	} else if (SPIx == SPI2) {
		global_SPI_Config[SPI2_Index] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}
	// Enable SPI
	/*Bit 6 SPE: SPI enable
	 0: Peripheral disabled
	 1: Peripheral enabled*/
	tmpreg_CR1 |= 1 << 6;
	// Configure baud rate- clock phase - clock polarity - data size -
	// device mode - communication mode - frame format
	tmpreg_CR1 |= SPI_Config->Baud_Rate | SPI_Config->Clk_Phase
			| SPI_Config->Clk_Polarity | SPI_Config->Data_Size
			| SPI_Config->Device_Mode | SPI_Config->Communication_Mode
			| SPI_Config->Frame_Format;

	// Confiugre NSS
	if (SPI_Config->NSS == SPI_NSS_HW_Master_SS_Output_Disable
			|| SPI_Config->NSS == SPI_NSS_HW_Master_SS_Output_Enable)
		tmpreg_CR2 |= SPI_Config->NSS;
	else
		tmpreg_CR1 |= SPI_Config->NSS;
	// IRQ
	if (SPI_Config->IRQ_Enable != SPI_IRQ_Disable) {
		tmpreg_CR2 |= SPI_Config->IRQ_Enable;
		if (SPIx == SPI1)
			NVIC_IRQ35_SPI1_Enable;
		else if (SPIx == SPI2)
			NVIC_IRQ36_SPI2_Enable;
	}

	SPIx->CR1 = tmpreg_CR1;
	SPIx->CR2 = tmpreg_CR2;
}

/**===================================================
 *  @Fn - MCAL_SPI_DeInit
 *  @brief - DeInitialize the SPI
 *  @param [in] - SPIx :
 *  @retval - none
 *  Note -
 **/
void MCAL_SPI_DeInit(SPI_typedef *SPIx) {
	if (SPIx == SPI1) {
		RCC_SPI1_RESET();
		NVIC_IRQ35_SPI1_Disable;
	} else if (SPIx == SPI2) {
		RCC_SPI2_RESET();
		NVIC_IRQ36_SPI2_Disable;
	}
}

/**===================================================
 *  @Fn - MCAL_SPI_GPIO_Pins
 *  @brief - Configure the SPI Pins
 *  @param [in] - SPIx :
 *  @retval - none
 *  Note -
 **/
void MCAL_SPI_GPIO_Pins(SPI_typedef *SPIx) {
	GPIO_PinConfig_t spiPinCfg;

	if (SPIx == SPI1) {
		// SCK	PA5
		// MOSI PA7
		// MISO PA6
		// NSS PA4
		if (global_SPI_Config[SPI1_Index]->Device_Mode == SPI_Device_Mode_MASTER) {
			// SCK
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_5;
			spiPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			spiPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			//MOSI - Full-Duplex
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_7;
			spiPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			spiPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			//todo to support half duplex and simplex

			//MISO - Full-Duplex
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_6;
			spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			//todo to support half duplex and simplex

			//NSS
			if (global_SPI_Config[SPI1_Index]->NSS
					== SPI_NSS_HW_Master_SS_Output_Enable) {
				spiPinCfg.GPIO_PinNumber = GPIOx_PIN_4;
				spiPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				spiPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
				MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			} else if (global_SPI_Config[SPI1_Index]->NSS
					== SPI_NSS_HW_Master_SS_Output_Disable) {
				spiPinCfg.GPIO_PinNumber = GPIOx_PIN_4;
				spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			}
		}
		if (global_SPI_Config[SPI1_Index]->Device_Mode == SPI_Device_Mode_SLAVE) {
			// SCK
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_5;
			spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			//MOSI - Full-Duplex
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_7;
			spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			//todo to support half duplex and simplex

			//MISO - Full-Duplex
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_6;
			spiPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			spiPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			//todo to support half duplex and simplex

			//NSS
			if (global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_HW_Slave) {
				spiPinCfg.GPIO_PinNumber = GPIOx_PIN_4;
				spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &spiPinCfg);
			}
		}
	} else if (SPIx == SPI2) {
		// SCK	PB13
		// MOSI PB15
		// MISO PB14
		// NSS  PB12
		if (global_SPI_Config[SPI2_Index]->Device_Mode == SPI_Device_Mode_MASTER) {
			// SCK
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_13;
			spiPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			spiPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			//MOSI - Full-Duplex
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_15;
			spiPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			spiPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			//todo to support half duplex and simplex

			//MISO - Full-Duplex
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_14;
			spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			//todo to support half duplex and simplex

			//NSS
			if (global_SPI_Config[SPI2_Index]->NSS
					== SPI_NSS_HW_Master_SS_Output_Enable) {
				spiPinCfg.GPIO_PinNumber = GPIOx_PIN_12;
				spiPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				spiPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
				MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			} else if (global_SPI_Config[SPI2_Index]->NSS
					== SPI_NSS_HW_Master_SS_Output_Disable) {
				spiPinCfg.GPIO_PinNumber = GPIOx_PIN_12;
				spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			}
		}
		if (global_SPI_Config[SPI2_Index]->Device_Mode == SPI_Device_Mode_SLAVE) {
			// SCK
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_13;
			spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			//MOSI - Full-Duplex
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_15;
			spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			//todo to support half duplex and simplex

			//MISO - Full-Duplex
			spiPinCfg.GPIO_PinNumber = GPIOx_PIN_14;
			spiPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			spiPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			//todo to support half duplex and simplex

			//NSS
			if (global_SPI_Config[SPI2_Index]->NSS == SPI_NSS_HW_Slave) {
				spiPinCfg.GPIO_PinNumber = GPIOx_PIN_12;
				spiPinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &spiPinCfg);
			}
		}
	}
}
// Send-Receive in half-duplex or simplex
void MCAL_SPI_Send_Data(SPI_typedef *SPIx, uint16_t *pTxBuffer,
		enum Polling PollingEn) {
//todo receive only or transmit only
	if (PollingEn == Pollingenable)
		while (!(SPIx->SR & SPI_SR_TXE ))
			;
	SPIx->DR = *pTxBuffer;
}
void MCAL_SPI_Receive_Data(SPI_typedef *SPIx, uint16_t *pTxBuffer,
		enum Polling PollingEn) {
	if (PollingEn == Pollingenable)
		while (!(SPIx->SR & SPI_SR_RXNE ))
			;
	*pTxBuffer = SPIx->DR;
}
//Send-Receive in full-duplex
void MCAL_SPI_Tx_Rx(SPI_typedef *SPIx, uint16_t *pTxBuffer,
		enum Polling PollingEn) {
	if (PollingEn == Pollingenable)
		while (!(SPIx->SR & SPI_SR_TXE ))
			;
	SPIx->DR = *pTxBuffer;

	if (PollingEn == Pollingenable)
		while (!(SPIx->SR & SPI_SR_RXNE ))
			;
	*pTxBuffer = SPIx->DR;

}

/*
 * =======================================================================================
 * 							IRQ
 * =======================================================================================
 */
void SPI1_IRQHandler() {
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI1->SR & (1 << 1)) >> 1);
	irq_src.RXNE = ((SPI1->SR & (1 << 0)) >> 0);
	irq_src.ERRI = ((SPI1->SR & (1 << 4)) >> 4);

	global_SPI_Config[SPI1_Index]->P_IRQ_CallBack(irq_src);
}
void SPI2_IRQHandler() {
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI2->SR & (1 << 1)) >> 1);
	irq_src.RXNE = ((SPI2->SR & (1 << 0)) >> 0);
	irq_src.ERRI = ((SPI2->SR & (1 << 4)) >> 4);
	global_SPI_Config[SPI2_Index]->P_IRQ_CallBack(irq_src);
}
