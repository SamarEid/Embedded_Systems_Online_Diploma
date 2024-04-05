/*
 * Drivers.c
 *
 * Created: 3/24/2024 1:21:02 AM
 * Author : dell
 */ 

#define F_CPU 8000000UL
#include "util/delay.h"
#include "avr/io.h"
#include "GPIO.h"

#define LED  GPIOC

void WDOG_OFF(){
	WDTCR = (1<<WDE) | (1<<WDTOE)	;
	WDTCR = 0x00;
}
void WDOG_ON(){
	WDTCR |= (1<<WDE) | (1<<WDP0)| (1<<WDP1)| (1<<WDP2);
}
int main(void)
{
	GPIO_Pin_Config(LED,Px0,GPIO_OUTPUT);
	GPIO_Pin_Write(LED,Px0,GPIO_PIN_Set);
	_delay_ms(200);
	while (1)
	{	
		WDOG_ON();
		_delay_ms(100);
		GPIO_Pin_Toggle(LED,Px0);
		_delay_ms(3000);
		WDOG_OFF();
	}
}

