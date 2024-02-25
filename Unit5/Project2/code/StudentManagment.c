/*
 * StudentManagment.c
 *
 *  Created on: Feb 25, 2024
 *      Author: dell
 */
#include "StudentManagment.h"

FIFO_Buf_t Fifo_Students;
void setup(){
	FIFO_init(&Fifo_Students, st, width);
}
void add_student_from_file(){
	DPRINTF("----------------------\n");
	FILE* p;
	p = fopen("Studentinfo", "r");
	if (p == NULL){
		DPRINTF("File can't be opened\n");
	}
	else{
		element_type student;
		while(fscanf(p, "%d %s %s %f %d %d %d %d %d", &student.roll, &student.fName, &student.lName,
				&student.GPA, &student.cid[0], &student.cid[1], &student.cid[2],
				&student.cid[3], &student.cid[4])!= EOF)
			{
			if(FIFO_find_roll_number(&Fifo_Students, student.roll) == 0){
				FIFO_enqueue(&Fifo_Students, &student);
				DPRINTF("[INFO] Roll number %d saved successfully\n", student.roll);
			}
			else{
				DPRINTF("[ERROR] Roll number %d is already taken\n", student.roll);
			}
		}
		total_student();
	}
	fclose(p);

}
void add_student_manually(){
	element_type student;
	DPRINTF("--------------------------\n");
	DPRINTF("Add the student's details\n");
	DPRINTF("--------------------------\n");
	DPRINTF("Enter the roll number: ");
	scanf("%d", &student.roll);
	if(FIFO_find_roll_number(&Fifo_Students, student.roll) == 0){
		DPRINTF("Enter the first name: ");
		scanf("%s", &student.fName);
		DPRINTF("Enter the last name: ");
		scanf("%s", &student.lName);
		DPRINTF("Enter the GPA: ");
		scanf("%f", &student.GPA);
		DPRINTF("Enter the course ID for each course: \n");
		for(int i = 0; i < 5; i++){
			DPRINTF("Course %d id: ", i+1);
			scanf("%d", &student.cid[i]);
		}
		FIFO_enqueue(&Fifo_Students, &student);
		DPRINTF("\n[INFO] Student's details added successfully\n");
		DPRINTF("--------------------------------\n");
	}
	else{
		DPRINTF("Roll number %d is already taken\n", student.roll);
		DPRINTF("---------------------------------\n");
	}
	total_student();

}
void find_by_roll(){
	DPRINTF("\n-----------------------------\n");
	DPRINTF("Enter the roll number of the student: ");
	int roll;
	scanf("%d", &roll);
	element_type* student = FIFO_find_roll_number(&Fifo_Students, roll);
	if (student == NULL){
		DPRINTF("[ERROR] Roll number %d not found", roll);
	}
	else{
		DPRINTF("The student's details are: \n");
		DPRINTF("The first name: %s\n", student->fName);
		DPRINTF("The last name: %s\n", student->lName);
		DPRINTF("The student's GPA: %0.2f\n", student->GPA);
		DPRINTF("Student's courses: \n");
		for (int i =0 ; i < 5; i++){
			DPRINTF("Course %d ID: %d\n", i+1, student->cid[i]);
		}
		DPRINTF("--------------------------------\n");
	}

}
void find_by_fName(){
	DPRINTF("\n----------------------------\n");
	DPRINTF("Enter the first name: ");
	char name[50];
	scanf("%s", name);
	element_type* student = FIFO_find_first_name(&Fifo_Students, name);
	if(student == 0){
		DPRINTF("[ERROR] The first name %s is not found\n", name);
	}
	else{
			DPRINTF("The student's details are: \n");
			DPRINTF("The first name: %s\n", student->fName);
			DPRINTF("The last name: %s\n", student->lName);
			DPRINTF("The student's GPA: %0.2f\n", student->GPA);
			DPRINTF("The student's roll: %d\n", student->roll);
			DPRINTF("Student's courses: \n");
			for (int i =0 ; i < 5; i++){
				DPRINTF("Course %d ID: %d\n", i+1, student->cid[i]);
			}
			DPRINTF("--------------------------------\n");
		}
}
void find_course_id(){
	int course;
	DPRINTF("\n---------------------------\n");
	DPRINTF("Enter the course id: ");
	scanf("%d", &course);
	FIFO_find_course_id(&Fifo_Students, course);
}
void total_student(){
	DPRINTF("\n-----------------------------------\n");
	DPRINTF("[INFO] The total number of students: %d\n", Fifo_Students.count);
	DPRINTF("[INFO] You can add up to %d students\n", Fifo_Students.length);
	DPRINTF("[INFO] You can add %d more students\n", Fifo_Students.length - Fifo_Students.count);
	DPRINTF("\n------------------------------------------------\n");
}
void delete_student(){
	DPRINTF("\n-----------------------------\n");
	DPRINTF("Enter the roll number of the student you want to delete: ");
	int roll;
	scanf("%d", &roll);
	element_type* student = FIFO_find_roll_number(&Fifo_Students, roll);
	if (student == NULL){
		DPRINTF("[ERROR] Roll number %d not found", roll);
	}
	else{
		FIFO_delete(&Fifo_Students, student);
	}
}
void update_student(){
	DPRINTF("\n-------------------------\n");
	DPRINTF("Enter the roll number of the student you want to update: ");
	int roll;
	scanf("%d", &roll);
	element_type* student = FIFO_find_roll_number(&Fifo_Students, roll);
	if (student == NULL){
		DPRINTF("[ERROR] Roll number %d not found", roll);
	}
	else{
		DPRINTF("Enter the value you want to change: \n");
		DPRINTF("1. First name\n");
		DPRINTF("2. Last name\n");
		DPRINTF("3. Roll NO. \n");
		DPRINTF("4. GPA \n");
		DPRINTF("5. Courses\n");
		int choice;
		scanf("%d", &choice);
		switch(choice){
		case 1:
			DPRINTF("Enter the new first name: ");
			scanf("%s", &student->fName);
			break;
		case 2:
			DPRINTF("Enter the new last name: ");
			scanf("%s", &student->lName);
			break;
		case 3:
			DPRINTF("Enter the new roll number: ");
			scanf("%d", &student->roll);
			break;
		case 4:
			DPRINTF("Enter the new GPA: ");
			scanf("%f", &student->GPA);
			break;
		case 5:
			DPRINTF("Enter the course number you want to update: ");
			int course;
			scanf("%d", &course);
			DPRINTF("Enter the new course id: ");
			scanf("%d", &student->cid[course-1]);
			break;
		default:
			DPRINTF("INVALID OPTION!!!!\n");

		}
		DPRINTF("Student's details updated successfully\n");
	}
	DPRINTF("\n----------------------------\n");
}
void show_students(){
	FIFO_print(&Fifo_Students);
}

