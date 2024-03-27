//
// Created by dell on 10/20/2023.
//
#include "stdio.h"
#include "string.h"
struct Students_info{
    int roll;
    char name[100];
    int marks;
};

int main(){
    struct Students_info studentsInfo[10];
    int i;
    printf("Enter information: \n");
    for(i=0; i < 10; ++i){
        char firstname[100];
        printf("For roll number %d", i+1);
        printf("\nEnter name: ");
        scanf("%s", firstname);
        strcpy(studentsInfo[i].name,firstname);
        printf("Enter marks: ");
        scanf("%d", &studentsInfo[i].marks);
        studentsInfo[i].roll = i+1;
    }
    printf("\nDisplaying information of students: \n");
    for(i = 0; i < 10; ++i){
        printf("---Information for roll number: %d\n", studentsInfo[i].roll);
        printf("Name: %s\n", studentsInfo[i].name);
        printf("Marks: %d\n", studentsInfo[i].marks);
    }
}