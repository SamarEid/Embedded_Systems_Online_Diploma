/*
 * Drivers.c
 *
 * Created: 3/24/2024 1:21:02 AM
 * Author : dell
 */ 

#define F_CPU 8000000UL
#include "util/delay.h"
#include "GPIO.h"
#include "Timer0.h"

extern uint8_t OVF_Number;

void TOI_CallBack(){
	PORTA = ~ PORTA;
}

int main(void)
{
	GPIO_Port_Config(GPIOA,GPIO_OUTPUT);
		sei();

	Timer0_Config_t timerCFG;
	timerCFG.T_Mode = CTC;
	timerCFG.clk = CLK_Prescaler_8;
	timerCFG.OCM_INT = enable_OCMI;
	timerCFG.OVF_INT = disable_OVFI;
	timerCFG.P_COMP_IRQ_CallBack = TOI_CallBack;
	TIMER0_Init(&timerCFG);
	TIMER0_Set_Compare_Val(0xF0);
	
	while (1)
	{	
		
	}
}

