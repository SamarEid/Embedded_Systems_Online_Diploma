/*
 * main.c
 *
 *  Created on: Feb 25, 2024
 *      Author: dell
 */

#include "StudentManagment.h"


int main(){
	setup();
	DPRINTF("Welcome to the Student Management System\n");
	while(1){
		DPRINTF("Choose The task you want to perform\n");
		DPRINTF("1. Add the student's details Manually\n");
		DPRINTF("2. Add the student's details from text file\n");
		DPRINTF("3. Find the student's details by roll number\n");
		DPRINTF("4. Find the student's details by first name\n");
		DPRINTF("5. Find the student's details by course ID\n");
		DPRINTF("6. Find the total number of students\n");
		DPRINTF("7. Delete the student's details by roll number\n");
		DPRINTF("8. Update the student's details by roll number\n");
		DPRINTF("9. Show all information\n");
		DPRINTF("10. Exit\n");
		DPRINTF("Enter your choice to perform the task: ");

		int choice;
		scanf("%d", &choice);
		switch(choice){
		case 1:
			add_student_manually();
			break;
		case 2:
			add_student_from_file();
			break;
		case 3:
			find_by_roll();
			break;
		case 4:
			find_by_fName();
			break;
		case 5:
			find_course_id();
			break;
		case 6:
			total_student();
			break;
		case 7:
			delete_student();
			break;
		case 8:
			update_student();
			break;
		case 9:
			show_students();
			break;
		case 10:
			return 0;
		default:
			DPRINTF("INVALID OPTION!!!!!!!!!!!!!!\n");
		}
	}
}
