//
// Created by dell on 9/26/2023.
//
#include "stdio.h"
int main(){
    char x;
    float a,b;
    printf("Enter operator either + or - or * or / : ");
    scanf("%c", &x);
    printf("Enter tow operands: ");
    scanf("%f %f", &a, &b);

    switch (x) {
        case '+':
            printf("%g", a+b);
            break;
        case '-':
            printf("%g", a-b);
            break;
        case '*':
            printf("%g", a*b);
            break;
        case '/':
            printf("%g", a/b);
            break;
        default:
            printf("Invalid input!!");
            break;
    }
}