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
void I2C_Read(unsigned char ack){
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack <<TWEA);
	while(!(TWCR & 0x80));
}

void I2C_Write(unsigned char ch){
	TWDR = ch;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & 0x80));
}