/*
 * GPIO_Atmega_lab.c
 *
 * Created: 3/10/2024 5:09:59 PM
 * Author : dell
 */ 

#include "MemoryMap.h"
#include "Util.h"


#define F_CPU 80000000UL

// static unsigned char SegmentNumber[] = {0x3F,0x06,0x5B,0x4f,0x66,0x60,0x7D,0x07,0x7F,0x6F}


void wait(unsigned int milliseconds) {
	for (unsigned int i = 0; i < milliseconds; i++) {
		for (unsigned int j = 0; j < 1000; j++) {
			asm("nop"); // Execute no-operation instructions for a delay
		}
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRD = 0xff;
	PORTD = 0;
    while (1) 
    {
		SetBit(PORTD,5);
		wait(1000);
		ClrBit(PORTD,5);
		SetBit(PORTD,6);
		wait(1000);
		ClrBit(PORTD,6);
		SetBit(PORTD,7);
		wait(1000);
		ClrBit(PORTD,7);
		SetBit(PORTD,4);
		wait(1000);
		ClrBit(PORTD,4);
    }
}

