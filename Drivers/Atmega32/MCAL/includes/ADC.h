/*
 * ADC.h
 *
 * Created: 4/7/2024 10:02:03 AM
 *  Author: dell
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "Device_Header.h"
#include "Util.h"
#include "avr/interrupt.h"

/* Bit 7:6 – REFS1:0: Reference Selection Bits*/
typedef enum{
	ADC_Voltage_Ref_AREF = (0b00<<6),
	ADC_Voltage_Ref_AVCC = (0b01<<6),
	ADC_Voltage_Ref_Internal = (0b11<<6)
}ADC_Volt_Ref;
/*Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits*/
typedef enum{
	Prescaller2 = (0b001<<0),
	Prescaller4 = (0b010<<0),
	Prescaller8 = (0b011<<0),
	Prescaller16 = (0b100<<0),
	Prescaller32 = (0b101<<0),
	Prescaller64 = (0b110<<0),
	Prescaller128 = (0b111<<0)

}ADC_Prescaler;
/*Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits*/
//Single ended input
typedef enum{
	ADC0 = (0b00000<<0),
	ADC1= (0b00001<<0),
	ADC2= (0b00010<<0),
	ADC3= (0b00011<<0),
	ADC4= (0b00100<<0),
	ADC5= (0b00101<<0),
	ADC6= (0b00110<<0),
	ADC7= (0b00111<<0)
}ADC_Input_Channel;

/*Bit 5 – ADLAR: ADC Left Adjust Result*/
typedef enum{
	Left_Adjust = (1<<5),
	Right_Adjust = (0<<5)
}ADC_Result_Alighment;
/*Bit 5 – ADATE: ADC Auto Trigger Enable*/
typedef enum{
	Auto_Trigger_Enable = (1<<5),
	Auto_Trigger_Disable = (0<<5)
}ADC_Auto_Trigger;
/*Bit 7:5 – ADTS2:0: ADC Auto Trigger Source*/
typedef enum{
	Free_Running_Mode = 0,
	Analog_Comparator = (1<<5),
	External_INT_REQ0 = (0b010<<5),
	Timer0_Compare_Match = (0b110<<5),
	Timer0_OverFlow = (0b001<<5),
	Timer_Compare_MatchB = (0b101<<5),
	Timer1_OverFlow = (0b011<<5),
	Timer1_Capture_Event = (0b111<<5)
}Auto_Trigger_Source;
/*Bit 3 – ADIE: ADC Interrupt Enable*/
typedef enum{
	Interrupt_Enable = (1<<3),
	Interrupt_Disable = (0<<3)
}ADC_Interrupt;

typedef struct{
	ADC_Prescaler Prescaller;
	ADC_Volt_Ref Volt_ref;
	ADC_Input_Channel Channel;
	ADC_Result_Alighment Alignment;
	ADC_Auto_Trigger Auto_Trigger_Enable_Disable;
	Auto_Trigger_Source Trigger_Source;
	ADC_Interrupt EnableIRQ;
	void(*P1_IRQ_CallBack)(void);
}ADC_Config_t;

void ADC_Init(ADC_Config_t* ADC_Config);
void ADC_DeInit(void);
void ADC_Start_Conversion(void);
void ADC_Read(uint16_t *ADC_Val);
void ADC_Switch_Channel(ADC_Input_Channel Channel);

#endif /* ADC_H_ */