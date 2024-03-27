# include "stdio.h"

struct Student_info{
    char name[100];
    int roll;
    float mark;
};

int main(){
    struct Student_info student;
    printf("Enter Students information: \n");
    printf("Enter name: ");
    gets(student.name);
    printf("Enter roll number: ");
    scanf("%d", &student.roll);
    printf("Enter marks: ");
    scanf("%f", &student.mark);

    printf("\nDisplaying Information\nname: %s\nRoll: %d\nMarks: %0.2f", student.name, student.roll, student.mark);



}