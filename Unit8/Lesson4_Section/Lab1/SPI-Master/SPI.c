/*
 * SPI.c
 *
 * Created: 3/23/2024 5:59:25 AM
 *  Author: dell
 */ 
#include "SPI.h"
#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

void SPI_Master_Init(void){
	DDRB |=(1<< MOSI) | (1<<SCK) | (1<< SS);
	DDRB &= ~(1<< MISO);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

unsigned char SPI_Master_Transmit(unsigned char data){
	SPDR = data;
	while(!(SPSR& (1<<SPIF)));
	return SPDR;
}