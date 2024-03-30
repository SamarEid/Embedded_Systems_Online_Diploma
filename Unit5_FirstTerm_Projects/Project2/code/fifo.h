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
#include "string.h"
#include "stdlib.h"
#include "StudentManagment.h"
// select element type (uint8_t, uint26_t, uint32_t, ..)
#define element_type struct sinfo
// create buffer 1
#define width 55


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
element_type* FIFO_find_roll_number(FIFO_Buf_t* fifo, int roll);
element_type* FIFO_find_first_name(FIFO_Buf_t* fifo, char* fname);
void FIFO_find_course_id(FIFO_Buf_t* fifo, int cid);
void FIFO_delete(FIFO_Buf_t* fifo, element_type* item);


#endif /* FIFO_H_ */
