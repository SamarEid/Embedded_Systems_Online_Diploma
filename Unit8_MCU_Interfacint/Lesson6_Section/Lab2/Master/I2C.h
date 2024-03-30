/*
 * I2C.h
 *
 * Created: 3/23/2024 11:48:35 PM
 *  Author: dell
 */ 


#ifndef I2C_H_
#define I2C_H_
#include "avr/io.h"
#include "stdio.h"
#include "stdint.h"

void I2C_Init(unsigned long SCL_Clock);
void I2C_Start(void);
void I2C_Write(unsigned char ch);
unsigned char I2C_Read(unsigned char ack);
void I2C_Stop(void);





#endif /* I2C_H_ */