/*
 * Section_Task1.c
 *
 * Created: 3/11/2024 4:11:16 AM
 * Author : dell
 */ 

#include "MemoryMap.h"
#include "Util.h"

void wait(unsigned int milliseconds) {
	for (unsigned int i = 0; i < milliseconds; i++) {
		for (unsigned int j = 0; j < 1000; j++) {
			asm("nop"); // Execute no-operation instructions for a delay
		}
	}
}

int main(void)
{
	DDRD = 0xff;
    /* Replace with your application code */
    while (1) 
    {
		SetBit(PORTD,5);
		wait(1000);
		SetBit(PORTD,6);
		wait(1000);
		SetBit(PORTD,7);
		wait(1000);
		ClrBit(PORTD,7);
		wait(1000);
		ClrBit(PORTD,6);
		wait(1000);
		ClrBit(PORTD,5);
		wait(1000);
    }
}

