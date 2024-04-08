/*
 * ADC.c
 *
 * Created: 4/7/2024 10:02:13 AM
 *  Author: dell
 */ 
#include "ADC.h"

ADC_Config_t global_ADC_Confing;
void (*g_CallBack)(void);

void ADC_Init(ADC_Config_t* ADC_Config){
	global_ADC_Confing = *ADC_Config;
	// Set (Reference voltage- Channel - Result Alignment)
	ADMUX |= ADC_Config->Alignment | ADC_Config->Volt_ref | ADC_Config->Channel;
	// Auto Trigger
	ADCSRA |= ADC_Config->Auto_Trigger_Enable_Disable;
	if(ADC_Config->Auto_Trigger_Enable_Disable == Auto_Trigger_Enable){
		SFIOR |= ADC_Config->Trigger_Source;
	}
	// Interrupt Enable
	ADCSRA |= ADC_Config->EnableIRQ;
	if(ADC_Config->EnableIRQ == Interrupt_Enable){
		Set_Bit(SREG,7);
		g_CallBack = ADC_Config->P1_IRQ_CallBack;
	}
	else{
		Clr_Bit(SREG,7);
		g_CallBack = (void*)0x0;
	}
	//Enable ADC
	/*Bit 7 – ADEN: ADC Enable*/
	Set_Bit(ADCSRA,7);
}
void ADC_DeInit(void){
	ADMUX = 0x00;
	ADCSRA = 0x00;
	SFIOR = 0x00;
}
void ADC_Start_Conversion(void){
	//Auto Trigger
	if(global_ADC_Confing.Auto_Trigger_Enable_Disable == Auto_Trigger_Enable && !Read_Bit(ADCSRA,5)){
		Set_Bit(ADCSRA,5);
	}
	/*Bit 6 – ADSC: ADC Start Conversion*/
	Set_Bit(ADCSRA,6);
}
void ADC_Read(uint16_t *ADC_Val){
	//ADC_Start_Conversion();
	//Bit 4 – ADIF: ADC Interrupt Flag
	while(!Read_Bit(ADCSRA,4));
	*ADC_Val = ADCL;
	*ADC_Val |= (ADCH<<8);
	//Set_Bit(ADCSRA,4);
}


ISR(ADC_vect){
	g_CallBack();
}
