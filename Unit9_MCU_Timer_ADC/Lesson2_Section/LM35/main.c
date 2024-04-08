/*
 * Drivers.c
 *
 * Created: 3/24/2024 1:21:02 AM
 * Author : dell
 */ 



#define F_CPU 8000000UL
#include "util/delay.h"
#include "GPIO.h"
#include "ADC.h"
#include "LCD.h"

uint16_t oldVal = 0xFFFF;
uint16_t Value = 0;
uint16_t max;
char x[10];
void ADC_CallBack(void){
	
	ADC_Read(&Value);
	 uint16_t temp = ADCH;	
	if(Value != oldVal){
		LCD_clear_screen();
		LCD_send_string("Temp: ");
		LCD_gotoXY(1,0);
		LCD_display_number(temp);
	}
	oldVal = Value;
	ADC_Start_Conversion();

}
int main(void)
{
	GPIO_Pin_Config(GPIOA,Px0,GPIO_INPUT);
	
	LCD_lcd_init();
	
	ADC_Config_t ADCcfg;
	ADCcfg.Alignment = Left_Adjust;
	ADCcfg.Auto_Trigger_Enable_Disable = Auto_Trigger_Enable;
	ADCcfg.Trigger_Source = Free_Running_Mode;
	ADCcfg.Channel = ADC0;
	ADCcfg.EnableIRQ = Interrupt_Enable;
	ADCcfg.P1_IRQ_CallBack = ADC_CallBack;
	ADCcfg.Prescaller = Prescaller128;
	ADCcfg.Volt_ref = ADC_Voltage_Ref_Internal;
	ADC_Init(&ADCcfg);
	
	ADC_Start_Conversion();
	
	while (1)
	{	
			
	}
}

