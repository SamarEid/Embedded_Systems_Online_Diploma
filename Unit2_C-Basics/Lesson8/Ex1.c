#include "stdio.h"

int main(){
    int m = 29;
    printf("Address of m: %x \nValue of m: %d\n", &m,m);

    printf("\n");
    printf("Now ab is assigned with the address of m.\n");
    int* ab = &m;
    printf("Address of pointer ab: %x \n"
           "Content of pointer ab: %d\n",ab,*ab);

    printf("\n");
    printf("The value of m assigned 34 now\n");
    m = 34;
    printf("Address of pointer ab: %x\n"
           "Content fo pointer ab: %d\n", ab, *ab);

    printf("\n");
    printf("The pointer variable ab is assigned with the value 7 now\n");
    *ab = 7;
    printf("Address of pointer ab: %x\n"
           "Content fo pointer ab: %d\n", ab, *ab);


    return 0;

}