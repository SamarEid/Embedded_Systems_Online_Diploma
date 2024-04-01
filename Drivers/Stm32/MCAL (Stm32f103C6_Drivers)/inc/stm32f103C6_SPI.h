/*
 * stm32f103C6_SPI.h
 *
 *  Created on: Apr 1, 2024
 *      Author: dell
 */

#ifndef INC_STM32F103C6_SPI_H_
#define INC_STM32F103C6_SPI_H_

//includes
#include "stm32f103x6.h"
#include "stm32f103C6_GPIO.h"
//---------------------------------------


struct S_IRQ_SRC{
	uint8_t TXE:1;
	uint8_t RXNE:1;
	uint8_t ERRI:1;
	uint8_t Reserved:5;

};
//----------------------------
//User type definitions (structures)
//----------------------------
typedef struct{
	uint16_t Device_Mode;		//Specify the device mode Master/Slave
								//This parameter must be set according to the values of @ref SPI_Device_Mode_define

	uint16_t Data_Size;			//Specify the size of the data 8-bit/16-bit
								//This parameter must be set according to the values of @ref SPI_Data_Size_define

	uint16_t Frame_Format;		//Specify How data is shifted out MSB-first/LSB-first
								//This parameter must be set according to the values of @ref SPI_Frame_Format_define

	uint16_t Communication_Mode; //Specify The communication mode Full-duplex/Half-duplex/Simplex
								//This parameter must be set according to the values of @ref SPI_Communication_Mode_define

	uint16_t Baud_Rate;			//Control the frequency
								//This parameter must be set according to the values of @ref SPI_Baud_Rate_define
								//Take care: you have to configure RCC to enter the correct clock to APB2>>SPI1----APB1>>SPI2

	uint16_t Clk_Polarity;		//Specify the polarity
								//This parameter must be set according to the values of @ref SPI_CLK_Polarity_define

	uint16_t Clk_Phase;			//Specify the clock phase
								//This parameter must be set according to the values of @ref SPI_CLK_Phase_define

	uint16_t NSS;				//Specify whether the NSS signal is managed by HW or SW
								//This parameter must be set according to the values of@ref SPI_NSS_define

	uint16_t IRQ_Enable;			//Enable/Disable Interrupt
								//This parameter must be set according to the values of@ref SPI_IRQ_Enable_define

	void(*P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);	// Set the Function() which will be called once the IRQ happen
}SPI_Config_t;

//----------------------------
//Macros Configuration References
//----------------------------

/*@ref SPI_Device_Mode_define*/
//CR1
/*Bit 2 MSTR: Master selection
0: Slave configuration
1: Master configuration*/
#define SPI_Device_Mode_MASTER  			(uint16_t)(1<<2)
#define SPI_Device_Mode_SLAVE  				(uint16_t)(0<<2)

/*@ref SPI_Data_Size_define*/
//CR1
/*
Bit 11 DFF: Data frame format
0: 8-bit data frame format is selected for transmission/reception
1: 16-bit data frame format is selected for transmission/reception
*/
#define SPI_Data_Size_8						(uint16_t)(0<<11)
#define SPI_Data_Size_16					(uint16_t)(1<<11)

/*@ref SPI_Frame_Format_define*/
//CR1
/*Bit 7 LSBFIRST: Frame format
0: MSB transmitted first
1: LSB transmitted first*/
#define SPI_Frame_Format_LSB_First			(uint16_t)(1<<7)
#define SPI_Frame_Format_MSB_First			(uint16_t)(0<<7)


/*@ref SPI_Communication_Mode_define*/
//CR1
/*
Bit 15 BIDIMODE: Bidirectional data mode enable
0: 2-line unidirectional data mode selected
1: 1-line bidirectional data mode selected
*/
/*Bit 10 RXONLY: Receive only
This bit combined with the BIDImode bit selects the direction of transfer in 2-line unidirectional mode.
This bit is also useful in a multislave system in which this particular slave is not accessed, the output from the accessed slave is not corrupted.
0: Full duplex (Transmit and receive)
1: Output disabled (Receive-only mode)*/
/*Bit 14 BIDIOE: Output enable in bidirectional mode
This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode
0: Output disabled (receive-only mode)
1: Output enabled (transmit-only mode)*/
#define SPI_Communication_Mode_2Line			(uint16_t)(0<<10 | 0<<15)
#define SPI_Communication_Mode_1Line_RxOnly		(uint16_t)(1<<10 | 0<<15)
#define SPI_Communication_Mode_1Line_Tx			(uint16_t)(1<<14 | 1<<15)
#define SPI_Communication_Mode_1Line_Rx			(uint16_t)(0<<14 | 1<<15)


/*@ref SPI_Baud_Rate_define*/
/*Bits 5:3 BR[2:0]: Baud rate control
000: fPCLK/2
001: fPCLK/4
010: fPCLK/8
011: fPCLK/16
100: fPCLK/32
101: fPCLK/64
110: fPCLK/128
111: fPCLK/256*/
#define SPI_fPCLK_Over2			(uint16_t)(0b000<<3)
#define SPI_fPCLK_Over4			(uint16_t)(0b001<<3)
#define SPI_fPCLK_Over8			(uint16_t)(0b010<<3)
#define SPI_fPCLK_Over16		(uint16_t)(0b011<<3)
#define SPI_fPCLK_Over32		(uint16_t)(0b100<<3)
#define SPI_fPCLK_Over64		(uint16_t)(0b101<<3)
#define SPI_fPCLK_Over128		(uint16_t)(0b110<<3)
#define SPI_fPCLK_Over256		(uint16_t)(0b111<<3)


/*@ref SPI_CLK_Polarity_define*/
/*Bit1 CPOL: Clock polarity
0: CK to 0 when idle
1: CK to 1 when idle*/
#define SPI_CLK_Polarity_0_Idle					(uint16_t)(0<<1)
#define SPI_CLK_Polarity_1_Idle					(uint16_t)(1<<1)

/*@ref SPI_CLK_Phase_define*/
/*Bit 0 CPHA: Clock phase
0: The first clock transition is the first data capture edge
1: The second clock transition is the first data capture edge*/
#define SPI_CLK_Phase_First					(uint16_t)(0<<0)
#define SPI_CLK_Phase_Second				(uint16_t)(1<<0)

/*@ref SPI_NSS_define*/
//CR1
/*Bit 9 SSM: Software slave management
When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
0: Software slave management disabled
1: Software slave management enabled*/
/*Bit 8 SSI: Internal slave select*/
//CR2
/*Bit 2 SSOE: SS output enable
0: SS output is disabled in master mode and the cell can work in multimaster configuration
1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work in a multimaster environment.*/
//HW
#define SPI_NSS_HW_Slave					(uint16_t)(0<<9)
#define SPI_NSS_HW_Master_SS_Output_Enable	(uint16_t)(1<<2) // CR2
#define SPI_NSS_HW_Master_SS_Output_Disable	(uint16_t)(0<<2) //CR2
//SW (Slave or Master)
#define SPI_NSS_SW_Set						(uint16_t)(1<<9 | 1<<8)
#define SPI_NSS_SW_Reset					(uint16_t)(1<<9 | 0<<8)

/*@ref SPI_IRQ_Enable_define*/
/*CR2
Bit 7 TXEIE: Tx buffer empty interrupt enable
0: TXE interrupt masked
1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
Bit 6 RXNEIE: RX buffer not empty interrupt enable
0: RXNE interrupt masked
1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is set.
*/
/*
Bit 5 ERRIE: Error interrupt enable
This bit controls the generation of an interrupt when an error condition occurs (CRCERR, OVR, MODF in SPI mode and UDR, OVR in I2S mode).
		0: Error interrupt is masked
		1: Error interrupt is enabled
*/
#define SPI_IRQ_Enable_Tx					(uint16_t)(1<<7)
#define SPI_IRQ_Enable_Rx					(uint16_t)(1<<6)
#define SPI_IRQ_Enable_Error				(uint16_t)(1<<5)
#define SPI_IRQ_Disable						(uint16_t)(0<<7 | 0<<6 | 0<<5)


enum Polling{
	Pollingdisable,
	Pollingenable
};
//-------------------------------------------------------------
//----------APIs Supported By "MCAL USART DRIVER"--------------
//-------------------------------------------------------------
//Initialization and Deinitialization
void MCAL_SPI_Init(SPI_typedef* SPIx,SPI_Config_t* SPI_Config);
void MCAL_SPI_DeInit(SPI_typedef* SPIx);

void MCAL_SPI_GPIO_Pins(SPI_typedef* SPIx);
// Send-Receive in half-duplex or simplex
void MCAL_SPI_Send_Data(SPI_typedef* SPIx, uint16_t *pTxBuffer, enum Polling PollingEn);
void MCAL_SPI_Receive_Data(SPI_typedef* SPIx, uint16_t *pTxBuffer, enum Polling PollingEn);
//Send-Receive in full-duplex
void MCAL_SPI_Tx_Rx(SPI_typedef* SPIx, uint16_t *pTxBuffer, enum Polling PollingEn);


#endif /* INC_STM32F103C6_SPI_H_ */
