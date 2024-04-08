/*
 * Keypad.h
 *
 * Created: 3/13/2024 1:52:17 AM
 *  Author: dell
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "avr/io.h"
#include "util/delay.h"


#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define KeypadPort PORTD
#define KeypadPin PIND
#define KeypadDDR DDRD

void Keypad_init();
char Keypad_getKey();



#endif /* KEYPAD_H_ */