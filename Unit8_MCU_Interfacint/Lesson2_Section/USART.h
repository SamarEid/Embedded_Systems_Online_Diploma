/*
 * USART.h
 *
 * Created: 3/23/2024 12:42:12 AM
 *  Author: dell
 */ 


#ifndef USART_H_
#define USART_H_

#include "avr/io.h"
#include "stdio.h"
#include "stdint.h"

void USART_Init(void);
void USART_Send_Char(uint8_t data);
uint8_t USAERT_Rec_Char(void);
void USART_Send_String(char* data);
void USART_Rec_String(char* str);


#endif /* USART_H_ */