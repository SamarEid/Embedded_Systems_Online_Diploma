/*
 * I2C_Slave.c
 *
 * Created: 3/23/2024 11:47:47 PM
 * Author : dell
 */ 

#include <avr/io.h>
#include "I2C.h"
#include "util/delay.h"

int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	I2C_SetAddress(0b11010000);
    while (1) 
    {
		PORTA = I2C_Read(1);
    }
	return 0;
}

