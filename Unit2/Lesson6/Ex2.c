//
// Created by dell on 10/20/2023.
//
#include "stdio.h"
struct distance{
    int feet;
    float inch;
} gd1, gd2;
int main(){
    printf("Enter information for first distance: \n");
    printf("Enter feet: ");
    scanf("%d", &gd1.feet);
    printf("Enter inch: ");
    scanf("%f", &gd1.inch);
    printf("\n");
    printf("Enter information for second distance: \n");
    printf("Enter feet: ");
    scanf("%d", &gd2.feet);
    printf("Enter inch: ");
    scanf("%f", &gd2.inch);
    int sumfeet = gd1.feet+gd2.feet;
    float suminch = gd2.inch+gd1.inch;

    while (suminch >= 12){
        sumfeet++;
        suminch-=12;
    }
    printf("\nSum of distances = %d' - %0.1f\"", sumfeet, suminch);
}