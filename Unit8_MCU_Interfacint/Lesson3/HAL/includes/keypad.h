/*
 * keypad.h
 *
 * Created: 16/3/2021 6:32:00 PM
 *  Author: dell
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 8000000UL

#include "stm32f103x6.h"
#include "stm32f103C6_GPIO.h"


#define R0 GPIOx_PIN_0
#define R1 GPIOx_PIN_1
#define R2 GPIOx_PIN_3
#define R3 GPIOx_PIN_4
#define C0 GPIOx_PIN_5
#define C1 GPIOx_PIN_6
#define C2 GPIOx_PIN_7
#define C3 GPIOx_PIN_8

#define KEYPAD_PORT GPIOB


void Keypad_init();
char Keypad_getkey();

#endif /* KEYPAD_H_ */


