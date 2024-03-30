/*
 * I2C.h
 *
 * Created: 3/24/2024 12:05:39 AM
 *  Author: dell
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "avr/io.h"
#include "stdio.h"
#include "stdint.h"

void I2C_SetAddress(unsigned char address);
void I2C_Read(unsigned char ack);
void I2C_Write(unsigned char ch);


#endif /* I2C_H_ */