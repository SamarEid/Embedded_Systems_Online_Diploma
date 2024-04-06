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


int main(void)
{
	Timer0_Config_t timerCFG;
	timerCFG.T_Mode = FastPWM_Non_Inverted;
	timerCFG.clk = CLK_Prescaler_8;
	timerCFG.OCM_INT = disable_OCMI;
	timerCFG.OVF_INT = disable_OVFI;
	timerCFG.P_COMP_IRQ_CallBack = NULL;
	TIMER0_Init(&timerCFG);
	
	while (1)
	{	
		Timer0_Duty_Cycle(100);
	}
}

