/*
 * GPIO.c
 *
 * Created: 3/16/2024 6:13:43 AM
 *  Author: dell
 */ 

#include "GPIO.h"

uint8_t GPIO_Port_Read(uint8_t Portx){
	return (uint8_t)Portx;
}
void GPIO_Port_Write(uint8_t Portx, uint8_t Val){
	Portx = Val;
}
void GPIO_Port_Direction(uint8_t DDRx, uint8_t State){
	if (State == OUTPUT)
	{
		DDRx = (uint8_t)0xff;
	}
	else{
		DDRx = (uint8_t)0x0;
	}
}
void GPIO_Pin_Direction(uint8_t DDRx, uint8_t State, uint8_t Pin){
	if (State == INPUT)
	{
		DDRx |= Pin;
	}
	else{
		DDRx &= ~(Pin);
	}
}