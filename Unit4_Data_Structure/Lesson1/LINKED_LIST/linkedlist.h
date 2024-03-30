/*
 * linkedlist.h
 *
 *  Created on: Feb 8, 2024
 *      Author: dell
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

#define DPRINTF(...)	{fflush(stdout); \
		fflush(stdin); \
		printf(__VA_ARGS__); \
		fflush(stdout); \
		fflush(stdin);}


struct StudentData {
	int id;
	char name[50];
	float height;
};
// linked list nodes
struct NextStudent{
	struct StudentData Student;
	struct NextStudent* PNextStudent;
};

void AddStudent();
void DeleteStudent();
void ViewStudents();
void DeleteAll();
void Print_Nth_Student();
void Print_Nth_Student_From_End ();
void Print_Middle();

#endif /* LINKEDLIST_H_ */
