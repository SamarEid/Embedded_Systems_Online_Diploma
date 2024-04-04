/*
 * I2C_E2PROM.h
 *
 *  Created on: Apr 4, 2024
 *      Author: dell
 */

#ifndef INCLUDES_I2C_E2PROM_H_
#define INCLUDES_I2C_E2PROM_H_

//----------Includes-----------
#include "stm32f103C6_I2C.h"

//E2PROM is an I2C Slave
//Idle Mode: device is in high-impedance state and waits for data.
//Master Transmitter Mode: the device transmits data to a slave receiver
//Master Receiver Mode: The device receives data from a slave transmitter

#define	EEPROM_Slave_Address	0x2A

//--------------APIs--------------------
void EEPROM_Init(void);
unsigned char EEPROM_Write_Nbytes(uint32_t Memory_Add, uint8_t* bytes, uint8_t Data_Length);
unsigned char EEPROM_Read_bytes(uint32_t Address, uint8_t* dataOut, uint8_t dataLen);


#endif /* INCLUDES_I2C_E2PROM_H_ */
