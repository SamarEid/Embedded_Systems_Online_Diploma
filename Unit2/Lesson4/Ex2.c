//
// Created by dell on 10/1/2023.
//
#include "stdio.h"
int main(){
        int n;
        printf("Enter the number of data: ");
        scanf("%d", &n);
        float sum = 0.0;
        for (int i = 1; i <= n; i++){
                float x;
                printf("%d. Enter number: ", i);
                scanf("%f", &x);
                sum += x;
            }
        float avg = sum / n;
        printf("Average = %.2f", avg);
    }