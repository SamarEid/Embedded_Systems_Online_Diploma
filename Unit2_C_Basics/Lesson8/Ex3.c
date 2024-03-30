//
// Created by dell on 10/31/2023.
//
#include "stdio.h"
#include "string.h"
int main(){
    char string[100];
    gets(string);
    int x = strlen(string);
    char* p_string = string+x;
    for(int i = 0; i <= x; i++)
        printf("%c", *p_string--);
}