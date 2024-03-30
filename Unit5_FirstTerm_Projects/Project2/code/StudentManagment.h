/*
 * StudentManagment.h
 *
 *  Created on: Feb 25, 2024
 *      Author: dell
 */

#ifndef STUDENTMANAGMENT_H_
#define STUDENTMANAGMENT_H_

#define DPRINTF(...)	{fflush(stdout); \
		fflush(stdin); \
		printf(__VA_ARGS__); \
		fflush(stdout); \
		fflush(stdin);}

#include "fifo.h"

struct sinfo{
	char fName[50];
	char lName[50];
	int roll;
	float GPA;
	int cid[10];
}st[55];

void setup();
void add_student_from_file();
void add_student_manually();
void find_by_roll();
void find_by_fName();
void find_course_id();
void total_student();
void delete_student();
void update_student();
void show_students();

#endif /* STUDENTMANAGMENT_H_ */
