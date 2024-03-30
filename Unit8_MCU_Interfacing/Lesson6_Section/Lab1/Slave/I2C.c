/*
 * I2C.c
 *
 * Created: 3/24/2024 12:05:29 AM
 *  Author: dell
 */ 

#include "I2C.h"

void I2C_SetAddress(unsigned char address){
	TWAR = address;
}
unsigned char I2C_Read(unsigned char ack){
	unsigned char x = 0;
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack <<TWEA);
	while(!(TWCR & (1<<7)));
	while(TWSR != 0x60) x = TWSR;
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack <<TWEA);
	while(!(TWCR & (1<<7)));
	while(TWSR != 0x80) x = TWSR;
	
	return TWDR;
}