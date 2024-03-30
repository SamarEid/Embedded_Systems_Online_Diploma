/*
 * I2C.c
 *
 * Created: 3/23/2024 11:47:03 PM
 * Author : dell
 */ 
#include <avr/io.h>
#include "I2C.h"
#include "util/delay.h"
int main(void)
{
    /* Replace with your application code */
	unsigned char ch = 0;
	I2C_Init(0x48);
    while (1) 
    {
		_delay_ms(500);
		I2C_Start();
		I2C_Write(0b11010000+0);
		while(TWSR != 0x18);
		I2C_Write(ch++);
		while(TWSR != 0x28);
		I2C_Stop();
    }
	return 0;
}

