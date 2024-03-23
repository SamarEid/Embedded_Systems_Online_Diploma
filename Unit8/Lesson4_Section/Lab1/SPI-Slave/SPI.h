/*
 * SPI.h
 *
 * Created: 3/23/2024 6:01:26 AM
 *  Author: dell
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "avr/io.h"

void SPI_Slave_Init(void);
unsigned char SPI_Slave_Receive(unsigned char data);



#endif /* SPI_H_ */