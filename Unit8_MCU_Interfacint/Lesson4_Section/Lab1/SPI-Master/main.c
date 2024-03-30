/*
 * SPI_Master.c
 *
 * Created: 3/23/2024 5:47:44 AM
 * Author : dell
 */ 

#define F_CPU 1000000UL
#include "SPI.h"
#include "util/delay.h"



int main(void)
{
	short  ch = 0;
	DDRA = 0xFF;
	SPI_Master_Init();
	while(1){
		for(ch = 0; ch <= 9; ch++){
			_delay_ms(1000);
			PORTA = SPI_Master_Transmit(ch);
		}
	}
	return 0;
}

