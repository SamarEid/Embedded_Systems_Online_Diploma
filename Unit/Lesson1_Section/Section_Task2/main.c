/*
 * Section_Task2.c
 *
 * Created: 3/11/2024 4:19:36 AM
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
	DDRD = 0b11111110;
    /* Replace with your application code */
	int i = 5;
    while (1) 
    {
		if(ReadBit(PIND,0)==1){
			if(i == 8)
				i = 5;
			SetBit(PORTD,i);
			i++;
			wait(1000);
			while(ReadBit(PIND,0)==1);
		}
		
    }
}

