/*
 * main.c
 *
 *  Created on: Feb 7, 2024
 *      Author: dell
 */


#include "lifo.h"

unsigned int buffer1[5];

void main(){
	LIFO_Buf_t uart_lifo , I2C_lifo;
	//static allocation
	LIFO_init(&uart_lifo, buffer1 , 5);
	// dynamic allocation
	unsigned int* buffer2 =(unsigned int*) malloc(5* sizeof(unsigned int ));
	LIFO_init(&I2C_lifo, buffer2 , 5);

	int i, temp = 0;
	for(i = 0; i < 5 ; i++){
		if (LIFO_Add_item(&uart_lifo, i)== LIFO_no_error )
		printf("UAET_LIFO add: %d \n", i);
	}
	for(i = 0; i < 5 ; i++){
			if (LIFO_Get_item(&uart_lifo, &temp) == LIFO_no_error)
				printf("UAET_LIFO add: %d \n", temp);
		}

}

