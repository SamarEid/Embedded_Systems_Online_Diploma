/*
 * SPI.c
 *
 * Created: 3/23/2024 6:11:22 AM
 * Author : dell
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include "util/delay.h"

#define SS 4
#define MOSI 5
#define SCK 7

void execute(unsigned char cmd, unsigned char data){
	PORTB &= ~(1<<SS);
	SPDR = cmd;
	while(!(SPSR & (1<<SPIF)));
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<SS);
}

int main(void)
{
    unsigned char counter = 0;
	unsigned char index_display = 1;
	DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);
	SPCR = (1<< SPE) | (1<< MSTR) | (1<<SPR0);
	execute(0x09,0xFF);
	execute(0x0B,0x07);
	execute(0x0A,0x0F);
	execute(0x0C,0x01);
    while (1) 
    {
		for(index_display = 1; index_display < 9; index_display++){
			execute(index_display,counter++);
		}
		_delay_ms(1000);
		
    }
	return 0;
}

