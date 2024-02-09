/*
 * main.c
 *
 *  Created on: Feb 7, 2024
 *      Author: dell
 */

#include "fifo.h"

void main(){
	int i , temp=0;
	FIFO_Buf_t FIFO_UART;
	if(FIFO_init(&FIFO_UART ,uart_buffer ,5) == FIFO_no_error)
		printf("FIFO init ----Done\n");

	for(i = 0; i < 7; i++){
		printf("FIFO enqueue (%x) \n", i);
		if(FIFO_enqueue(&FIFO_UART, i) == FIFO_no_error)
			printf("\t fifo enqueue ----Done\n");
		else
			printf("\t fifo enqueue ----Faild\n");
	}
	FIFO_print(&FIFO_UART);

	if (FIFO_dequeue(&FIFO_UART, &temp) == FIFO_no_error )
		printf("fifo dequeue %x ----Done\n", temp);
	if (FIFO_dequeue(&FIFO_UART, &temp) == FIFO_no_error )
			printf("fifo dequeue %x ----Done\n", temp);

	FIFO_print(&FIFO_UART);

}
