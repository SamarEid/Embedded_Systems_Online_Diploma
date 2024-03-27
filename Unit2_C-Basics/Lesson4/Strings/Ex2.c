//
// Created by dell on 10/1/2023.
//
#include "stdio.h"
int main(){
    char string[100];
    printf("Enter a string: ");
    gets(string);
    int i ;
    for (i = 0; string[i] != '\0'; i++);
    printf("Length of string is : %d", i);
}