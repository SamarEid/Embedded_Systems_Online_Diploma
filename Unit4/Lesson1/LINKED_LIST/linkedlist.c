/*
 * linkedlist.c
 *
 *  Created on: Feb 8, 2024
 *      Author: dell
 */

#include "linkedlist.h"

struct NextStudent* gPFirstStudent = NULL ;
int Linked_List_Length = 0;

void AddStudent(){
	struct NextStudent* pLastStudent;
	struct NextStudent* pNewStudent;

	if(gPFirstStudent == NULL){ // if the record is empty
		// create the first record
		pNewStudent = (struct NextStudent*)malloc(sizeof(struct StudentData));
		// assign gpfirststudent to it
		gPFirstStudent = pNewStudent;
	}
	else{
		// reach the last student
		pLastStudent = gPFirstStudent;
		while(pLastStudent->PNextStudent)
			pLastStudent = pLastStudent->PNextStudent;

		// create a new record
		pNewStudent = (struct NextStudent* ) malloc(sizeof(struct StudentData));
		pLastStudent->PNextStudent = pNewStudent;
	}
	// fill the new record
	char temp[50];
	DPRINTF("\nEnter the student's ID: ");
	gets(temp);
	pNewStudent->Student.id = atoi(temp);

	DPRINTF("\nEnter the student's full name: ");
	gets(pNewStudent->Student.name);

	DPRINTF("\nEnter Height: ");
	gets(temp);
	pNewStudent->Student.height = atof(temp);

	Linked_List_Length++;  // increment the length of the list
	// set the next record to null
	pNewStudent->PNextStudent = NULL;
}
void DeleteStudent(){
	char temp[50];
	int  id_to_be_deleted;
	DPRINTF("\nEnter Student's ID to be deleted: ");
	gets(temp);
	id_to_be_deleted = atoi(temp);

	if(gPFirstStudent){ // the list is not empty
		struct NextStudent* pPreviousStudent = NULL;
		struct NextStudent* pSelectedStudent = gPFirstStudent;
		int flag = 0;
		while(pSelectedStudent){
			if(pSelectedStudent->Student.id == id_to_be_deleted){
				flag = 1;
				if(pPreviousStudent){ // the student to be deleted is not the first on the list
					pPreviousStudent->PNextStudent = pSelectedStudent->PNextStudent;
				}
				else{
					gPFirstStudent = pSelectedStudent->PNextStudent;
				}
				free(pSelectedStudent);
				Linked_List_Length--; // decrement the length of the list
			}
			pPreviousStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->PNextStudent;
		}
		if (flag == 0)
			DPRINTF("\nID not found in the data base ");
	}
	else{
		DPRINTF("\nData base is empty!! ");
	}
}

void ViewStudents(){
	int count = 1;
	struct NextStudent* pCurrentStudent = gPFirstStudent;
	if(gPFirstStudent == NULL)
		DPRINTF("\nThe list is empty!! ");
	while(pCurrentStudent){
		DPRINTF("\nRecord number: %d ", count);
		DPRINTF("\nID: %d ", pCurrentStudent->Student.id);
		DPRINTF("\nName: %s ", pCurrentStudent->Student.name);
		DPRINTF("\nHeight: %f ", pCurrentStudent->Student.height);
		DPRINTF("\n-----------------------------");
		count++;
		pCurrentStudent = pCurrentStudent->PNextStudent;
	}
}

void DeleteAll(){
	struct NextStudent* pCurrentStudent = gPFirstStudent;
	if(gPFirstStudent == NULL)
		DPRINTF("\nEmpty list!! ");
	while(pCurrentStudent){
		struct NextStudent* pTempStudent = pCurrentStudent;
		pCurrentStudent = pCurrentStudent->PNextStudent;
		free(pTempStudent);
	}
	Linked_List_Length = 0;  // set the list length to zero
	gPFirstStudent = NULL;
}

void Print_Nth_Student(){
	char temp[6];
	DPRINTF("\nEnter the number of the Student you want: (Zero-Index)");
	gets(temp);
	int node = atoi(temp);
	int count = 0;
	struct NextStudent* pCurrentStudent = gPFirstStudent;
	if(gPFirstStudent == NULL)
		DPRINTF("\nThe list is empty!! ");
	int flag = 0;
	while(pCurrentStudent){
		if(count == node){
			flag = 1;
			DPRINTF("\nRecord number: %d ", node+1);
			DPRINTF("\nID: %d ", pCurrentStudent->Student.id);
			DPRINTF("\nName: %s ", pCurrentStudent->Student.name);
			DPRINTF("\nHeight: %f ", pCurrentStudent->Student.height);
			DPRINTF("\n-----------------------------");
		}
			count++;
			pCurrentStudent = pCurrentStudent->PNextStudent;

	}
	if(flag == 0)
		DPRINTF("\nList doesn't have node %d", node);
}

void Print_Nth_Student_From_End (){
	char temp[6];
	DPRINTF("\nEnter the node you want form the end: (Zero-Index)");
	gets(temp);
	int node = atoi(temp);
	node = Linked_List_Length - node-1 ;
	int count = 0;
		struct NextStudent* pCurrentStudent = gPFirstStudent;
		if(gPFirstStudent == NULL)
			DPRINTF("\nThe list is empty!! ");
		int flag = 0;
		while(pCurrentStudent){
			if(count == node){
				flag = 1;
				DPRINTF("\nRecord number: %d ", node+1);
				DPRINTF("\nID: %d ", pCurrentStudent->Student.id);
				DPRINTF("\nName: %s ", pCurrentStudent->Student.name);
				DPRINTF("\nHeight: %f ", pCurrentStudent->Student.height);
				DPRINTF("\n-----------------------------");
			}
				count++;
				pCurrentStudent = pCurrentStudent->PNextStudent;

		}
		if(flag == 0)
			DPRINTF("\nList doesn't have node %d", node);
}

void Print_Middle(){
	int count = 0;
	struct NextStudent* ref_ptr = gPFirstStudent;
	struct NextStudent* mid_ptr = gPFirstStudent;
	if (gPFirstStudent == NULL){
		DPRINTF("\nThe List is empty!!");
	}
	else{
		while(ref_ptr){
			ref_ptr = ref_ptr->PNextStudent;
			if (ref_ptr == NULL)
				break;
			ref_ptr = ref_ptr->PNextStudent;
			mid_ptr = mid_ptr->PNextStudent;
			count++;
		}
		DPRINTF("\nRecord number: %d ", count+1);
		DPRINTF("\nID: %d ", mid_ptr->Student.id);
		DPRINTF("\nName: %s ", mid_ptr->Student.name);
		DPRINTF("\nHeight: %f ", mid_ptr->Student.height);
		DPRINTF("\n-----------------------------");

	}

}




