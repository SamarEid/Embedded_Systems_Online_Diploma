/*
 * SPI.h
 *
 * Created: 3/25/2024 10:14:37 AM
 *  Author: dell
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "Device_Header.h"

#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

// SPCR
#define SPR0	0
#define SPR1	1
#define CPHA	2
#define CPOL	3
#define MSTR	4
#define DORD	5
#define SPE		6
#define SPIE	7

// SPSR
#define SPI2X	0
#define WCOL	6
#define SPIF	7

// SPDR
#define LSB		0
#define MSB		7

enum SPI_Mode{
	SPI_Slave = 0 ,
	SPI_Master = 1
	};
enum SPI_Prescalar{
	SPI_Fosc4 = 0b00,
	SPI_Fosc16 = 0b01,
	SPI_Fosc64 = 0b10,
	SPI_Fosc128 = 0b11
};
enum SPI_Enable{
	SPI_Enable_ON = 1,
	SPI_Enable_OFF = 0
};

enum SPI_Double_Speed{
	SPI_Double_Speed_OFF ,
	SPI_Double_Speed_ON 
};
enum SPI_Operating_Level{
	SPI_Idle_Low ,
	SPI_Idle_High 
};
enum SPI_Sampling_Edge{
	SPI_Rising = 1,
	SPI_Falling = 0
};
enum SPI_Data_Order{
	SPI_LSB_First = 1,
	SPI_MSB_First = 0
};
struct SPI_Config{
	enum SPI_Mode Mode;
	enum SPI_Prescalar Prescalar;
	enum SPI_Enable Enable;
	enum SPI_Operating_Level Operating_Level;
	enum SPI_Double_Speed Double_Speed;
	enum SPI_Sampling_Edge Sampling_Edge;
	enum SPI_Data_Order Data_Order;
	};

void SPI_Init(struct SPI_Config Config);
unsigned char SPI_Transmit_Receive(unsigned char data);
unsigned char SPI_Check_For_Collision(void);
#endif /* SPI_H_ */