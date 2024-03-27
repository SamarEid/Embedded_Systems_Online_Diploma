//
// Created by dell on 10/31/2023.
//
#include "stdio.h"

struct employee{
    char *name;
    int id;
} employee1;


int main(){
    employee1.name = "Alex";
    employee1.id = 1002;
    struct employee* p1 = &employee1;

    struct employee (*a[]) = {p1};
    struct employee (*(*ptr)[1]) = &a;
    for (int i = 0; i < 1; ++i) {
        printf("Employee Name: %s\n"
               "Employee ID: %d\n", (**ptr+i)->name, (**ptr+i)->id );
    }

}