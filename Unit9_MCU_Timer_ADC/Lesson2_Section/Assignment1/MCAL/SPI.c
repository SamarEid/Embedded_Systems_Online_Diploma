/*
 * SPI.c
 *
 * Created: 3/25/2024 10:14:47 AM
 *  Author: dell
 */ 
#include "SPI.h"
#include "GPIO.h"
#include "avr/interrupt.h"

SPI_Config* global_SPI_Config;
void (*gp_SPI_ISR)(void);
/**===================================================
 *  @Fn - SPI_Init
 *  @brief - Initialize the SPI
 *  @param [in] - Config: a struct that contains the SPI configuration
 *  @retval - none
 *  Note -
 **/
void SPI_Init(SPI_Config* Config){
	global_SPI_Config = Config;
	// Mode Select Master-Slave
	if(Config->Mode == SPI_Master)
		Set_Bit(SPCR,MSTR);
	else
		Clr_Bit(SPCR,MSTR);
	// Enable SPI
	if(Config->Enable == SPI_Enable_ON)
		Set_Bit(SPCR,SPE);
	else
		Clr_Bit(SPCR,SPE);
	// Data Order
	if(Config->Data_Order == SPI_LSB_First)
		Set_Bit(SPCR,DORD);
	else 
		Clr_Bit(SPCR,DORD);
	// Clock Polarity
	if(Config->Operating_Level == SPI_Idle_Low)
		Set_Bit(SPCR,CPOL);
	else
		Clr_Bit(SPCR,CPOL);
	// Clock Phase
	if(Config->Sampling_Edge == SPI_Rising){
		if(Config->Operating_Level == SPI_Idle_High)
		SPCR |= (1<< CPHA);
		else
		SPCR |= (0<< CPHA);
	}
	else if(Config->Sampling_Edge == SPI_Falling){
		if(Config->Operating_Level == SPI_Idle_Low)
		SPCR |= (1<< CPHA);
		else
		SPCR |= (0<< CPHA);
	}
	// Clock Rate
	SPCR = SPCR | Config->Prescalar;
	SPSR |= Config->Double_Speed;
	
	// Interrupt Enable
	if(Config->INT_Enable == SPI_INT_ON){
		SPCR |= 1<<SPE;
		SREG |= 1<<7;
	}
	else
		SPCR &= ~(1<< SPE);
	
	
	//Set GPIO Pins
	// PB4  ss
	// PB5  MOSI
	// PB6  MISO
	// PB7  SCK
	if(Config->Mode == SPI_Master){
		GPIO_Pin_Config(GPIOB,Px4,GPIO_PIN_Set);
		GPIO_Pin_Config(GPIOB,Px5,GPIO_PIN_Set);
		GPIO_Pin_Config(GPIOB,Px6,GPIO_PIN_Reset);
		GPIO_Pin_Config(GPIOB,Px7,GPIO_PIN_Set);
	}
	else{
		GPIO_Pin_Config(GPIOB,Px4,GPIO_PIN_Reset);
		GPIO_Pin_Config(GPIOB,Px5,GPIO_PIN_Reset);
		GPIO_Pin_Config(GPIOB,Px6,GPIO_PIN_Set);
		GPIO_Pin_Config(GPIOB,Px7,GPIO_PIN_Reset);
	}
}


/**===================================================
 *  @Fn -  SPI_Transmit_Receive
 *  @brief - Send or Receive data
 *  @param [in] - data: The data to be transmitted or received
 *  @retval - The data register
 *  Note -
 **/
unsigned char SPI_Transmit_Receive(unsigned char data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
/**===================================================
 *  @Fn -  PI_Check_For_Collision
 *  @brief - Checks for collisions
 *  @param [in] - None
 *  @retval - The value of the collision flag
 *  Note -
 **/
unsigned char SPI_Check_For_Collision(void){
	return Read_Bit(SPSR,WCOL);
}


 ISR(SPI_STC_vect)
 {
	 global_SPI_Config->P_IRQ_CallBack();
 }