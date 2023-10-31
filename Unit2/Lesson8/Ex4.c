//
// Created by dell on 10/31/2023.
//
#include "stdio.h"

int main(){
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter the elements of the array: \n");
    for (int i =0 ; i < n; i++){
        printf("Element -%d: ", i+1);
        scanf("%d", &a[i]);
    }

    printf("the elements of array in reverse order: \n");
    int* ptr = a+n-1;
    for (int i = n-1; i >=0 ; i--) {
        printf("Element -%d: %d\n"
               "", i+1, *ptr--);
    }
}