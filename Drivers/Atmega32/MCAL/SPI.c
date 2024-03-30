/*
 * SPI.c
 *
 * Created: 3/25/2024 10:14:47 AM
 *  Author: dell
 */ 
#include "SPI.h"

struct SPI_Config global_SPI_Config;
/**===================================================
 *  @Fn - SPI_Init
 *  @brief - Initialize the SPI
 *  @param [in] - Config: a struct that contains the SPI configuration
 *  @retval - none
 *  Note -
 **/
void SPI_Init(struct SPI_Config Config){
	global_SPI_Config = Config;
	// Mode Select Master-Slave
	if(global_SPI_Config.Mode == SPI_Master)
		Set_Bit(SPCR,MSTR);
	else
		Clr_Bit(SPCR,MSTR);
	// Enable SPI
	if(global_SPI_Config.Enable == SPI_Enable_ON)
		Set_Bit(SPCR,SPE);
	else
		Clr_Bit(SPCR,SPE);
	// Data Order
	if(global_SPI_Config.Data_Order == SPI_LSB_First)
		Set_Bit(SPCR,DORD);
	else 
		Clr_Bit(SPCR,DORD);
	// Clock Polarity
	if(global_SPI_Config.Operating_Level == SPI_Idle_Low)
		Set_Bit(SPCR,CPOL);
	else
		Clr_Bit(SPCR,CPOL);
	// Clock Phase
	if(global_SPI_Config.Sampling_Edge == SPI_Rising){
		if(global_SPI_Config.Operating_Level == SPI_Idle_High)
		SPCR |= (1<< CPHA);
		else
		SPCR |= (0<< CPHA);
	}
	else if(global_SPI_Config.Sampling_Edge == SPI_Falling){
		if(global_SPI_Config.Operating_Level == SPI_Idle_Low)
		SPCR |= (1<< CPHA);
		else
		SPCR |= (0<< CPHA);
	}
	// Clock Rate
	SPCR = SPCR | global_SPI_Config.Prescalar;
	SPSR |= global_SPI_Config.Double_Speed;
	
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