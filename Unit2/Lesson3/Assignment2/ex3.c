//
// Created by dell on 9/26/2023.
//
#include "stdio.h"
int main(){
    float a,b,c;
    printf ("Enter three numbers: ");
    scanf("%f %f %f", &a, &b, &c);
    printf ("largest number = ");
    if (a > b){
        if (a > c)
            printf("%g", a);
        else
            printf("%g", c);
    }
    else if (b > a){
        if (b > c)
            printf("%g", b);
        else
            printf("%g", c);
    }
}