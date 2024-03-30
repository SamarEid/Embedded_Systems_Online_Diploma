/*
 * USART.h
 *
 * Created: 3/25/2024 3:00:13 AM
 *  Author: dell
 */ 


#ifndef USART_H_
#define USART_H_

//----------Includes-------------
#include "Device_Header.h"

//---------Register-bits-Macros--------
// UCSRA
#define MPCM	0
#define U2X		1
#define PE		2
#define DOR		3
#define FE		4
#define UDRE	5
#define TXC		6
#define RXC		7
//---------
// UCSRB
#define TXB8	0
#define RXB8	1
#define UCSZ2	2
#define TXEN	3
#define RXEN	4
#define UDRIE	5
#define TXCIE	6
#define RXCIE	7
//---------
// UCSRC
#define UCPOL	0
#define UCSZ0	1
#define UCSZ1	2
#define USBS	3
#define UPM0	4
#define UPM1	5
#define UMSEL	6
#define URSEL	7
//-----------

#define USART_Baud		1200
#define USART_Fosc		1000000

//---------------------------------------
//---------Configurations-----------
enum USART_Synch_Mode{
	USART_Asynch = (0<<UMSEL),
	USART_Synch = (1<<UMSEL)
};
enum USART_Speed_Mode{
	USART_Normal_Speed,
	USART_Double_Speed = (1<<U2X)
};
enum USART_Transmit{
	USART_Transmit_Disable = (0<<TXEN),
	USART_Transmit_Enable = (1<<TXEN)
};
enum USART_Receive{
	USART_Receive_Disable = (0<<RXEN),
	USART_Receive_Enable = (1<<RXEN)
};
enum USART_Char_Size{
	USART_5_Bit_Char = (0b00<<UCSZ0),
	USART_6_Bit_Char = (0b01<<UCSZ0), 
	USART_7_Bit_Char = (0b10<<UCSZ0),
	USART_8_Bit_Char = (0b11<<UCSZ0),
	USART_9_Bit_Char = (0b111<<UCSZ0) 
};
enum USART_Parity_Mode{
	USART_No_Parity = (0b00<<UPM0),
	USART_Even_Parity = (0b10<<UPM0) ,
	USART_Odd_Parity = (0b11<<UPM0) 
};
enum USART_StopBit{
	USART_1_StopBit = (0<<USBS),
	USART_2_StopBit = (1<<USBS)
};
enum USART_IRQ_Enable{
	Disable_INT = (0<<TXCIE | 0 <<RXCIE),
	Enable_INT_TX  = (1<<TXCIE),
	Enable_INT_RX  = (1<<RXCIE),
	Enable_INT_TX_RX = (1<<TXCIE | 1<<RXCIE)
};

struct USART_Config{
	enum USART_Synch_Mode Synch_Mode;
	enum USART_Speed_Mode Speed_Mode;
	enum USART_Receive Receive;
	enum USART_Transmit Transmit;
	enum USART_Char_Size Char_Size;
	enum USART_Parity_Mode Parity_Mode;
	enum USART_StopBit StopBit;
	enum USART_IRQ_Enable IRQ_Enable;
	void (*P_IRQ_CallBack)(void);
	};

//----------APIs------------
//Initialization
void USART_Init(struct USART_Config Config);
void USART_Transmit_Character(unsigned char data);
unsigned char USART_Receive_Character(void);
void USART_Transmit_String(char* data);
void USART_Receive_String(char* str);


#endif /* USART_H_ */