/*
 * SPI.h
 *
 * Created: 3/23/2024 5:59:35 AM
 *  Author: dell
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "avr/io.h"

void SPI_Master_Init(void);
unsigned char SPI_Master_Transmit(unsigned char data);


#endif /* SPI_H_ */