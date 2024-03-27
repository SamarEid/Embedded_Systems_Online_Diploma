//
// Created by dell on 9/26/2023.
//
#include "stdio.h"
int main(){
    int x;
    printf("Enter an integer: ");
    scanf("%d", &x);
    printf("Sum = %d", (x*(x+1))/2);
}