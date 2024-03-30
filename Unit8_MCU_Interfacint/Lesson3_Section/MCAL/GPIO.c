/*
 * GPIO.c
 *
 * Created: 3/24/2024 1:48:16 AM
 *  Author: dell
 */ 

#include "GPIO.h"

//-----------APIs------------

//PIN
void GPIO_Pin_Config(GPIO_Typdef* GPIOx, uint8_t pinNumber, uint8_t pinDir){
	if(pinDir == GPIO_OUTPUT){
		Set_Bit(GPIOx->DDR,pinNumber);
	}
	else if(pinDir == GPIO_INPUT){
		Clr_Bit(GPIOx->DDR,pinNumber);
		Clr_Bit(GPIOx->PORT,pinNumber);
	}
	else if (pinDir == GPIO_PullUp_INPUT)
	{
		Clr_Bit(GPIOx->DDR,pinNumber);
		Set_Bit(GPIOx->PORT,pinNumber);
	}
}
void GPIO_Pin_Write(GPIO_Typdef* GPIOx, uint8_t pinNumber, uint8_t val){
	if(val == GPIO_PIN_Set)
		Set_Bit(GPIOx->PORT,pinNumber);
	else
		Clr_Bit(GPIOx->PORT,pinNumber);
}
void GPIO_Pin_Toggle(GPIO_Typdef* GPIOx, uint8_t pinNumber){
	Toggle_Bit(GPIOx->PORT,pinNumber);
}
uint8_t GPIO_Pin_Read(GPIO_Typdef* GPIOx, uint8_t pinNumber){
	return (uint8_t)Read_Bit(GPIOx->PIN,pinNumber);
}
//Port
void GPIO_Port_Config(GPIO_Typdef* GPIOx,  uint8_t portDir){
	if(portDir == GPIO_OUTPUT)
		GPIOx->DDR = 0xFF;
	else if(portDir == GPIO_INPUT){
		GPIOx->DDR = 0x00;
		GPIOx->PORT = 0x00;
	}
	else if(portDir == GPIO_PullUp_INPUT){
		GPIOx->DDR = 0x00;
		GPIOx->PORT = 0xFF;
	}
}
void GPIO_Port_Write(GPIO_Typdef* GPIOx,  uint8_t val){
	GPIOx->PIN = val;
}
uint8_t GPIO_Port_Read(GPIO_Typdef* GPIOx){
	return GPIOx->PIN;
}
