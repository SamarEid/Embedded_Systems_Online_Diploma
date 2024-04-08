/*
 * Timer0.c
 *
 * Created: 4/6/2024 2:02:53 AM
 *  Author: dell
 */ 
#include "Timer0.h"
#include "GPIO.h"

Timer0_Config_t global_Timer_Config;
uint8_t OVF_Number;

void TIMER0_Init(Timer0_Config_t* timerConfig){
	global_Timer_Config = *timerConfig;
	// Set Timer Mode
	TCCR0 |= timerConfig->T_Mode;
	if(timerConfig->T_Mode == FastPWM_Non_Inverted || timerConfig->T_Mode == FastPWM_Inverted){
		GPIO_Pin_Config(GPIOB,Px3,GPIO_OUTPUT);
	}
	// Set Clock
	TCCR0 |= timerConfig->clk;
	// Enable/Disable Overflow interrupt
	TIMSK |= timerConfig->OVF_INT;
	// Enable/Disable Output Compare Match interrupt
	TIMSK |= timerConfig->OCM_INT;
	if(timerConfig->OCM_INT == enable_OCMI || timerConfig->OVF_INT == enable_OVFI){
		SREG |= 1<<7;
	}
}
void TIMER0_Stop(void){
	TCCR0 |= NO_CLK;
}

void TIMER0_Set_Compare_Val(uint8_t Val){
	OCR0 = Val;
}
void TIMER0_Set_Counter_Val(uint8_t Val){
	TCNT0 = Val;
}
void TIMER0_Get_Counter_Val(uint8_t* TicksNumber){
	*TicksNumber = TCNT0;
}

void TIMER0_Set_OverFlow_Val(uint8_t Val){
	OVF_Number = Val;
}
void TIMER0_Get_OverFlow_Val(uint8_t* Val){
	*Val = OVF_Number;
}

void Timer0_Duty_Cycle(uint8_t Duty_Cycle){
	if(global_Timer_Config.T_Mode == FastPWM_Inverted){
		OCR0 = (uint8_t) (255-Duty_Cycle);
	}
	else if(global_Timer_Config.T_Mode == FastPWM_Non_Inverted){
		OCR0 = Duty_Cycle;
	}
}

//ISR
ISR(TIMER0_OVF_vect){
	OVF_Number++;
	global_Timer_Config.P_OVF_IRQ_CallBack();
}
ISR(TIMER0_COMP_vect){
	global_Timer_Config.P_COMP_IRQ_CallBack();
}