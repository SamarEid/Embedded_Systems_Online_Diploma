/*
 * SPI.c
 *
 * Created: 3/23/2024 6:01:15 AM
 *  Author: dell
 */ 
#include "SPI.h"

#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

void SPI_Slave_Init(void){
	DDRB |=(1<< MISO);
	DDRB &= ~(1<< MOSI) & ~(1<<SCK) & ~(1<<SS);
	SPCR = (1<<SPE);
}

unsigned char SPI_Slave_Receive(unsigned char data){
	SPDR = data;
	while(!(SPSR& (1<<SPIF)));
	return SPDR;
}