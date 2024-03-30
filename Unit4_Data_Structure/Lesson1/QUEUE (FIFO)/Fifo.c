/*
 * Fifo.c
 *
 *  Created on: Feb 7, 2024
 *      Author: dell
 */

#include "fifo.h"

FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf, uint32_t length){
	if(buf == NULL)
		return FIFO_null;

	fifo->base = buf;
	fifo->head = fifo->base;
	fifo->tail = fifo->base;
	fifo->count = 0;
	fifo->length = length;
	if(fifo->base && fifo->length)
		return FIFO_no_error;
	else
		return FIFO_null;
}
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo, element_type* item){
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;
	// check if fifo is full
	if (FIFO_Is_FULL(fifo) == FIFO_full)
		return FIFO_full;

	*(fifo->head) = item;
	fifo->count++;

	// circler fifo
	if (fifo->head == (fifo->base + (fifo->length * sizeof(element_type))))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_no_error;

}
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo, element_type* item){
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;
	if(fifo->count == 0)
		return FIFO_empty;

	*item = *(fifo->tail);
	fifo->count--;
	// circler
	if (fifo->tail == (fifo->base + (fifo->length * sizeof(element_type))))
			fifo->tail = fifo->base;
		else
			fifo->tail++;

	return FIFO_no_error;
}
FIFO_Buf_status FIFO_Is_FULL (FIFO_Buf_t* fifo){
	if(!fifo->base || !fifo->head || !fifo->tail)
			return FIFO_null;
	if(fifo->count == fifo->length )
		return FIFO_full;

	return FIFO_no_error;

}
void FIFO_print(FIFO_Buf_t* fifo){
	element_type* temp;
	int i;
	if(fifo->count == 0)
		printf("fifo is empty\n");
	else{
		temp = fifo->tail;
		printf("\n =========fifo_print=========\n");
		for(i = 0; i < fifo->count; i++){
			printf("\t %x \n", *temp);
			temp++;
		}
		printf("--------------------------\n");
	}
}
