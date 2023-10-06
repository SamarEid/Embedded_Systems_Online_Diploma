//
// Created by dell on 10/7/2023.
//
#include "stdio.h"

int powers(int base, int power)
{
    if (power == 0)
        return 1;
    return base*powers(base,power-1);
}

int main(){
    int base, power;
    printf("Enter base number: ");
    scanf("%d", &base);
    printf("Enter power number(positive integer): ");
    scanf("%d", &power);
    printf("%d^%d = %d", base, power,powers(base,power));
}