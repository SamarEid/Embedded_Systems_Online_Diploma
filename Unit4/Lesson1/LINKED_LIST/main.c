/*
 * main.c
 *
 *  Created on: Feb 8, 2024
 *      Author: dell
 */

#include "linkedlist.h"
extern int Linked_List_Length;
int main(){

	char temp[50];
	while(1){
		DPRINTF("\n\tSELECT YOUR OPTION");
		DPRINTF("\n1:Add_Student");
		DPRINTF("\n2:Delete_Student");
		DPRINTF("\n3:View_Students");
		DPRINTF("\n4:Delete_All");
		DPRINTF("\n5:Print_Nth_Student");
		DPRINTF("\n6:Print the length of the database ");
		DPRINTF("\n7:Print_Nth_Student form the end ");
		DPRINTF("\n8:Print The middle of the linked list");
		DPRINTF("\n9:Exit");
		DPRINTF("\n--------------------------------------------");
		DPRINTF("\nEnter option number: ");
		gets (temp);
		switch(atoi(temp)){
		case 1:
			AddStudent();
			break;
		case 2:
			DeleteStudent();
			break;
		case 3:
			ViewStudents();
			break;
		case 4:
			DeleteAll();
			break;
		case 5:
			Print_Nth_Student();
			break;
		case 6:
			DPRINTF("The number of nodes in the list is : %d", Linked_List_Length);
			break;
		case 7:
			Print_Nth_Student_From_End();
			break;
		case 8:
			Print_Middle();
			break;
		case 9:
			return 0;
		default :
			DPRINTF("\nINVALID INPUT!!!");
		}
		DPRINTF("\n-------------------------------------------------");
	}

	return 0;
}
