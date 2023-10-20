//
// Created by dell on 10/20/2023.
//
#include "stdio.h"
struct complex{
    float real;
    float img;
}num1,num2, sum;

struct complex add(struct complex x, struct complex y){
    sum.real = x.real+y.real;
    sum.img = x.img+y.img;
    return sum;
}

int main(){
    printf("For 1st complex number: \nEnter real and imaginary respectively: ");
    scanf("%f", &num1.real);
    scanf("%f", &num1.img);

    printf("\nFor 2nd complex number: \nEnter real and imaginary respectively: ");
    scanf("%f", &num2.real);
    scanf("%f", &num2.img);
    add(num1,num2);
    printf("Sum = %0.1f + %0.1fi", sum.real, sum.img);

}