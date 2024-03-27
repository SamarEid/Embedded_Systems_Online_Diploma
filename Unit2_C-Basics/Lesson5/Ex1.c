#include "stdio.h"
#include <stdbool.h>

bool isprime(int x){
    if (x == 2)
        return true;
    if (x < 2)
        return false;
    for (int i = 2; i*i < x; i++){
        if (x %i == 0)
            return false;
    }
    return true;
}

void prime(int a, int b){
    for (int i = a; i <= b ; ++i) {
        if (isprime(i))
            printf("%d ", i);
    }
}

int main(){
    int a,b;
    printf("Enter two numbers(intervals): ");
    scanf("%d", &a);
    scanf("%d", &b);
    printf("Prime numbers between %d and %d are: ",a,b);
    prime(a,b);
}