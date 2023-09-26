//
// Created by dell on 9/26/2023.
//
#include "stdio.h"
int main(){
    char x;
    printf("Enter a character: ");
    scanf("%c", &x);
    int z = x;
    if ((z >= 97 && z <= 122) || (z >= 65 && z <= 90))
        printf("%c is an alphabet", x);
    else
        printf("%C is not an alphabet", x);
}