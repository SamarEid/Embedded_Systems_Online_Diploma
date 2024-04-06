/*
 * Timer0.h
 *
 * Created: 4/6/2024 2:02:39 AM
 *  Author: dell
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

//------Includes---------
#include "Device_Header.h"
#include "Util.h"
#include "avr/interrupt.h"

//------Register bits -------
//TCCR0
#define CS00	0
#define CS01	1
#define CS02	2
#define WGM01	3
#define COM00	4
#define COM01	5
#define WGM00	6
#define FOC0	7

//TIMSK
#define TOIE0	0
#define OCIE0	1

//TIFR
#define TOV0	0
#define OCF0	1

//Table 38. Waveform Generation Mode Bit Description
typedef enum{
	Normal = (0<<WGM00) | (0<<WGM01),
	CTC = (0<<WGM00) | (1<<WGM01),
	PWM = (1<<WGM00) | (0<<WGM01),
	FastPWM = (1<<WGM00) | (1<<WGM01)
}Timer0_Mode;

typedef enum{
	NO_CLK = (0<<CS00) | (0<<CS01) | (0<<CS02),
	CLK_No_Prescaling = (1<<CS00),
	CLK_Prescaler_8 = (1<<CS01),
	CLK_Prescaler_64 = (1<<CS00)|(1<<CS01),
	CLK_Prescaler_256 = (1<<CS02),
	CLK_Prescaler_1024 = (1<<CS00) | (1<<CS02),
	EXT_CLK_Falling_Edge = (1<<CS01)|(1<<CS02),
	EXT_CLK_Rising_Edge = (1<<CS00) |(1<<CS01) | (1<<CS02)
}Timer0_Clock;

typedef enum{
	enable_OCMI = (1<<OCIE0),
	disable_OCMI = 0X00
}Timer0_OCMI;
typedef enum{
	enable_OVFI = (1<<TOIE0),
	disable_OVFI = 0X00
}Timer0_TOVFI;
typedef struct{
	Timer0_Mode		T_Mode;
	Timer0_Clock	clk;
	Timer0_OCMI		OCM_INT;
	Timer0_TOVFI	OVF_INT;
	void (*P_OVF_IRQ_CallBack)(void);
	void (*P_COMP_IRQ_CallBack)(void);
}Timer0_Config_t;


//-----------APIs------------
void TIMER0_Init(Timer0_Config_t* timerConfig);
void TIMER0_Stop(void);

void TIMER0_Set_Compare_Val(uint8_t Val);

void TIMER0_Set_Counter_Val(uint8_t Val);
void TIMER0_Get_Counter_Val(uint8_t* TicksNumber);

void TIMER0_Set_OverFlow_Val(uint8_t Val);
void TIMER0_Get_OverFlow_Val(uint8_t* Val);



#endif /* TIMER0_H_ */