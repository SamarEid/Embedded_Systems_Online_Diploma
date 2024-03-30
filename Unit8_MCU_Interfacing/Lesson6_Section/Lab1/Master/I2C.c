/*
 * I2C.c
 *
 * Created: 3/23/2024 11:48:23 PM
 *  Author: dell
 */ 
#include "I2C.h"
#define F_CPU 8000000UL

#define prescaler 1
void I2C_Init(unsigned long SCL_Clock){
	TWBR = (unsigned char)(((F_CPU/ SCL_Clock)-16)/(2*prescaler));
	if(prescaler == 0)
		TWSR = 0;
	else if(prescaler == 4)
		TWSR = 1;
	else if(prescaler == 16)
		TWSR = 2;
	else if(prescaler == 64)
		TWSR = 3;
}
void I2C_Start(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	while(!(TWCR & (1<<7)));
	while(TWSR != 0x08);
}
void I2C_Write(unsigned char ch){
	TWDR = ch;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & 0x80));
}
void I2C_Stop(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}