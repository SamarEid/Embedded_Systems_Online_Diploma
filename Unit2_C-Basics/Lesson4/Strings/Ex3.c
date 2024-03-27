//
// Created by dell on 10/1/2023.
//
#include "stdio.h"
#include "string.h"
int main(){
    char string[100];
    printf("Enter a string: ");
    gets(string);
    int x = strlen(string);
    char reverseString[100];
    for (int i = 0; i < x; ++i) {
        reverseString[i] = string[x-i-1];
    }
    reverseString[x] = '\0';
    printf("Reverse string is : %s", reverseString);
}