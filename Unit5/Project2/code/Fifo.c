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

	*(fifo->head) = *item;
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
	int i, j;
	if(fifo->count == 0){
		DPRINTF("fifo is empty\n");
	}
	else{
		temp = fifo->tail;
		DPRINTF("\n--------------------------\n");
		for(i = 0; i < fifo->count; i++){
			DPRINTF("Student's first name %s\n",temp->fName);
			DPRINTF("Student's last name %s\n", temp->lName);
			DPRINTF("Student's roll number %d\n", temp->roll);
			DPRINTF("Student's GPA %0.2f\n", temp->GPA);
			for(j = 0; j < 5; j++){
				DPRINTF("Course %d ID: %d\n", j+1, temp->cid[j]);
			}
			DPRINTF("-------------------------\n")
			temp++;
		}
		DPRINTF("--------------------------\n");
	}
}

element_type* FIFO_find_roll_number(FIFO_Buf_t* fifo, int roll){
	element_type* p = fifo->tail;
	for(int i =0 ; i < fifo->count; i++){
		if(p->roll == roll){
			return p;
		}
		else{
			p++;
		}
	}
	return NULL;
}
element_type* FIFO_find_first_name(FIFO_Buf_t* fifo, char* fname){
	element_type* p = fifo->tail;
	for (int i =0 ; i < fifo->count; i++){
		if(strcmp(p->fName, fname)==0){
			return p;
		}
		else{
			p++;
		}
	}
	return NULL;
}
void FIFO_find_course_id(FIFO_Buf_t* fifo, int cid){
	element_type* p = fifo->tail;
	int flag = 0;
	for(int i = 0; i < fifo->count; i++){
		for(int j = 0; j < 5; j++){
			if(p->cid[j] == cid){
				DPRINTF("The student's details are: \n");
				DPRINTF("The first name: %s\n", p->fName);
				DPRINTF("The last name: %s\n", p->lName);
				DPRINTF("The student's GPA: %0.2f\n", p->GPA);
				DPRINTF("The student's roll: %d\n", p->roll);
				DPRINTF("----------------------------------\n");
				flag = 1;
			}
		}
		p++;
	}
	if(flag == 0){
		DPRINTF("[ERROR] Course id %d is not found\n", cid);
		DPRINTF("----------------------------------------\n");
	}
}
void FIFO_delete(FIFO_Buf_t* fifo, element_type* item){
	int roll = item->roll;
	element_type* p = item;
	while(p != fifo->head){
		p++;
		*item = *p;
		item = p;
	}

	DPRINTF("[INFO] Roll number %d is removed successfully\n", roll);
	fifo->head--;
	fifo->count--;
}
