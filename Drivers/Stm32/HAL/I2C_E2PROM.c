/*
 * I2C_E2PROM.c
 *
 *  Created on: Apr 4, 2024
 *      Author: dell
 */

#include "I2C_E2PROM.h"

//--------------APIs--------------------
void EEPROM_Init(void){
	//-----------I2C_Init--------------
	//PB6	SCK i2c1
	//PB7	Data i2c1
	I2C_Config i2cCfg;
	// I2C controller act as master
	i2cCfg.General_Call_Address_Detection = General_Call_Enable;
	i2cCfg.I2C_ACK_Contorl = I2C_ACK_Enable;
	i2cCfg.Master_Mode = I2C_MASTER_MODE_SM;
	i2cCfg.I2C_CLK_Speed = I2C_Clk_SM_100K;
	i2cCfg.I2C_Mode = I2C_Mode_I2C;
	i2cCfg.P_Slave_Event_CallBack = NULL;
	i2cCfg.Stretch_Mode = I2C_StretchMode_Enable;

	MCAL_I2C_Init(I2C1, &i2cCfg);
	MCAL_I2C_GPIO_Set_Pins(I2C1);

}
unsigned char EEPROM_Write_Nbytes(uint32_t Memory_Add, uint8_t* bytes, uint8_t Data_Length){
	uint8_t i =0;
	uint8_t buffer[256] = {0};
	buffer[0] = (uint8_t)(Memory_Add>>8);					// Upper byte memory address
	buffer[1] = (uint8_t)Memory_Add;						// Lower byte memory address
	for(i = 2; i < (Data_Length+2); i++){
		buffer[i] = bytes[i-2];
	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, (Data_Length+2), With_Stop, Start);

	return 0;
}
unsigned char EEPROM_Read_bytes(uint32_t Address, uint8_t* dataOut, uint8_t dataLen){
		uint8_t buffer[2] = {0};
		buffer[0] = (uint8_t)(Address>>8);					// Upper byte memory address
		buffer[1] = (uint8_t)Address;
		MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, 2, Without_Stop, Start);
		MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address,dataOut, dataLen, With_Stop, repeated_start);

		return 0;
}
