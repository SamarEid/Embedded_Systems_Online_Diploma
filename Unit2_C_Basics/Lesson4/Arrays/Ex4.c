//
// Created by dell on 10/1/2023.
//
#include "stdio.h"
int main(){
    int n;
    printf("Enter No. of elements: ");
    scanf("%d", &n);
    int a[n+1];
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    int x;
    printf("Enter element to be inserted: ");
    scanf("%d", &x);
    int location;
    printf("Enter the location: ");
    scanf("%d", &location);
    for (int i = n; i >= location ; i--) {
        a[i] = a[i-1];
    }
    a[location-1] = x;
    for (int i = 0; i <= n ; ++i) {
        printf("%d " , a[i]);
    }
}