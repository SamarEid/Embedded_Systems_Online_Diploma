//
// Created by dell on 9/26/2023.
//
#include "stdio.h"
int main(){
    int x;
    printf("Enter an integer: ");
    scanf("%d", &x);
    if (x < 0)
        printf("Error!!! Factorial of negative number doesn't exist.");
    else if (x == 0)
        printf("%d", 0);
    else{
        long long product = 1;
        while(x > 0){
            product = product * x;
            x--;
        }
        printf("Facotrial = %d", product);
    }
}