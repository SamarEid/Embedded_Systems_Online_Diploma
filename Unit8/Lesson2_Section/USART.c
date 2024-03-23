/*
 * USART.c
 *
 * Created: 3/23/2024 12:41:59 AM
 *  Author: dell
 */ 
#include "USART.h"

void USART_Init(void){
	// Set baud rate 
	UBRRL = 51;
	
	UCSRA &= ~(1<<1); //Bit 1 – U2X: Double the USART Transmission Speed
					/*This bit only has effect for the asynchronous operation.
					 Write this bit to zero when using synchronous operation.
					Writing this bit to one will reduce the divisor of the baud rate divider
					 from 16 to 8 effectively doubling the transfer rate for asynchronous
					  communication.*/
	
	// Set frame format
	UCSRC |= (0b00<<4); //Bit 5:4 – UPM1:0: Parity Mode
						//0 0 Parity Mode Disabled
	UCSRC |= 0<<3;   //Bit 3 – USBS: Stop Bit Select
					//0 1 Stop Bit(s) 1-bit
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<< URSEL) ; //Bit 2:1 – UCSZ1:0: Character Size				
					 //1 1 8-bit
	UCSRB |= 0<<UCSZ2;  //Bit 2 – UCSZ2: Character Size		
	
		 
	// Enable the transmitter and receiver
	UCSRB |= 1<<RXEN;	//Bit 4 – RXEN: Receiver Enable 
					//Writing this bit to one enables the USART Receiver.
	UCSRB |= 1<<TXEN;  //Bit 3 – TXEN: Transmitter Enable
					//Writing this bit to one enables the USART Transmitter
}
void USART_Send_Char(uint8_t data){
	//Bit 5 – UDRE: USART Data Register Empty
	//If UDRE is one, the buffer is empty, and therefore ready to be written.
	while(!(UCSRA &(1<<UDRE)));
	UDR = data;
}
uint8_t USAERT_Rec_Char(void){
	//Bit 7 – RXC: USART Receive Complete
	//This flag bit is set when there are unread data in the receive buffer
	while(!(UCSRA &(1<<RXC)));
	return UDR;
}
void USART_Send_String(char* data){
	uint8_t i = 0;
	while(data[i] != NULL)
		USART_Send_Char(data[i++]);
	USART_Send_Char('\r');
}
void USART_Rec_String(char *str){
	*str = USAERT_Rec_Char();
	while(*str != '\r'){
		str++;	
		*str = USAERT_Rec_Char();
	}
	*str = NULL;
}