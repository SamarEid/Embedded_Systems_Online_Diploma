//
// Created by dell on 9/26/2023.
//
#include "stdio.h"
int main() {
    float a, b;
    printf("Enter value of a: ");
    scanf("%f", &a);
    printf("Enter value of b: ");
    scanf("%f", &b);
    float sum = a+b;
    b = a;
    a = sum - a;
    printf("After swapping, value of a = %g",a );
    printf("\nAfter swapping, value of b = %g",b );
}
