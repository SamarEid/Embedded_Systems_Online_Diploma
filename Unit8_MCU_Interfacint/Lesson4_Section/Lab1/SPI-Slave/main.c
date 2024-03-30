/*
 * SPI_Slave.c
 *
 * Created: 3/23/2024 5:53:44 AM
 * Author : dell
 */ 

#define F_CPU 1000000UL
#include "SPI.h"
#include "util/delay.h"



int main(void)
{
	short x = 9;
	DDRA = 0xFF;
	SPI_Slave_Init();
	while(1){
		for(x = 9; x >= 0; x--){
			PORTA = SPI_Slave_Receive(x);
		}
	}
	return 0;
}


