/*
 * USART.c
 *
 * Created: 3/25/2024 3:00:25 AM
 *  Author: dell
 */ 
#include "USART.h"
#include "avr/interrupt.h"

void (*gp_CallBack)(void);
struct USART_Config global_USART_Config ;

void USART_Init(struct USART_Config Config){
	//1. Set baud rate
	unsigned long UBRR;
	global_USART_Config = Config ;
	if(Config.Synch_Mode == USART_Asynch){
		if(Config.Speed_Mode == USART_Normal_Speed)
			UBRR = (unsigned long)((USART_Fosc/(16*USART_Baud)) -1) ;
		else if (Config.Speed_Mode == USART_Double_Speed){
			UBRR = (unsigned long)((USART_Fosc/(8*USART_Baud)) -1) ;
			UCSRA |= (1<<U2X);
		}
	}
	else if(Config.Synch_Mode == USART_Synch)
			UBRR = (unsigned long)((USART_Fosc/(2*USART_Baud)) -1) ;

	UBRRH = (unsigned char) (UBRR >> 8);
	UBRRL = (unsigned char) UBRR;

	//2. Set frame format
	UCSRC = (1<<URSEL); // Accessing UCSRC
	// set parity bit - synch mode - stop bit - char size 
	UCSRC |= Config.Parity_Mode | Config.Synch_Mode | Config.StopBit | Config.Char_Size ;
	if (Config.Char_Size == USART_9_Bit_Char){
		UCSRB |= 1<<UCSZ2;
	}
	// enable/disable interrupt
	UCSRB |= Config.IRQ_Enable;
	if(Config.IRQ_Enable == Disable_INT){
		Clr_Bit(SREG,7);
		gp_CallBack = (void*)0x0;
	}
	else{
		Set_Bit(SREG,7);
		gp_CallBack = Config.P_IRQ_CallBack;
	}
	//3. Enable transmitter or receiver
	UCSRB |= Config.Transmit | Config.Receive;
}

void USART_Transmit_Character(unsigned char data){
	while(!(UCSRA & (1<<UDRE)));
	if(global_USART_Config.Char_Size == USART_9_Bit_Char)
		UCSRB |= ((data>>8) & 1);
	UDR = data;
}
unsigned char USART_Receive_Character(void){
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}
void USART_Transmit_String(char* data){
	uint8_t i = 0;
	while(data[i] != NULL)
	USART_Transmit_Character(data[i++]);
	USART_Transmit_Character('\r');
}
void USART_Receive_String(char *str){
	*str = USART_Receive_Character();
	while(*str != '\r'){
		str++;
		*str = USART_Receive_Character();
	}
	*str = NULL;
}
ISR(USART_RXC_vect)
{
	gp_CallBack();
}

ISR(USART_TXC_vect)
{
	gp_CallBack();
}
