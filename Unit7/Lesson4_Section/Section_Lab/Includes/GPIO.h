/*
 * GPIO.h
 *
 * Created: 3/16/2024 6:23:32 AM
 *  Author: dell
 */ 


#ifndef GPIO_H_
#define GPIO_H_

//Includes
#include "MemoryMap.h"

//
#define PIN_0		(uint8_t)0x01
#define PIN_1		(uint8_t)0x02
#define PIN_2		(uint8_t)0x04
#define PIN_3		(uint8_t)0x08
#define PIN_4		(uint8_t)0x10
#define PIN_5		(uint8_t)0x20
#define PIN_6		(uint8_t)0x40
#define PIN_7		(uint8_t)0x80

#define INPUT		0
#define OUTPUT		1

//APIs
uint8_t GPIO_Port_Read(uint8_t Portx);
void GPIO_Port_Write(uint8_t Portx, uint8_t Val);
void GPIO_Port_Direction(uint8_t DDRx, uint8_t State);
void GPIO_Pin_Direction(uint8_t DDRx, uint8_t State, uint8_t Pin);



#endif /* GPIO_H_ */