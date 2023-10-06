//
// Created by dell on 10/7/2023.
//
#include "stdio.h"

int factorial(int x){
    if (x == 1)
        return 1;
    return x* factorial(x-1);
}

int main(){
    int x;
    printf("Enter a positive integer: ");
    scanf("%d", &x);
    printf("Factorial of %d = %d", x , factorial(x));
}