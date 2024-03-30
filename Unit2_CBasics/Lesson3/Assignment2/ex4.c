//
// Created by dell on 9/26/2023.
//
#include "stdio.h"
int main(){
    float x;
    printf("Enter a number: ");
    scanf("%f", &x);
    if (x > 0)
        printf("%g is positive.",x);
    else if (x < 0)
        printf("%g is negative.",x);
    else
        printf("You entered a zero.");
}