/*
 * fifo.h
 *
 *  Created on: Feb 7, 2024
 *      Author: dell
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdint.h"

// select element type (uint8_t, uint26_t, uint32_t, ..)
#define element_type uint8_t
// create buffer 1
#define width 5
element_type uart_buffer[width];

// FIFO data types
typedef struct{
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_Buf_t;

typedef enum{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_null
}FIFO_Buf_status;

// APIs
FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf, uint32_t length);
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo, element_type* item);
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo, element_type* item);
FIFO_Buf_status FIFO_Is_FULL (FIFO_Buf_t* fifo);
void FIFO_print(FIFO_Buf_t* fifo);



#endif /* FIFO_H_ */
