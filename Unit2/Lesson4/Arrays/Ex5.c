//
// Created by dell on 10/1/2023.
//
#include "stdio.h"
int main(){
        int n;
        printf("Enter No. of elements: ");
        scanf("%d", &n);
        int a[n];
        for (int i = 0; i < n; i++){
                scanf("%d", &a[i]);
            }
        int x;
        printf("Enter the elements to be searched: ");
        scanf("%d", &x);
        int i;
        for ( i = 0; i < n; ++i) {
                if (a[i] == x){
                        printf("Number found at the location = %d", i+1);
                        break;
                    }
            }
        if (i == n)
                printf("Number Not Found!!");
    }