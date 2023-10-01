//
// Created by dell on 10/1/2023.
//
#include "stdio.h"
int main(){
        int r,c;
        printf("Enter the number of rows and columns: ");
        scanf("%d", &r);
        scanf("%d", &c);
        printf("Enter elements of matrix: \n");
        int a[r][c];
        for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                        printf("Enter element a%d%d: ", i+1, j+1);
                        scanf("%d", &a[i][j]);
                    }
            }
        printf("Entered Matrix: \n");
        for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                        printf("%d  ", a[i][j]);
                    }
                printf("\n");
            }


                        printf("\nTranspose of Matrix: \n");
        for (int i = 0; i < c; ++i) {
                for (int j = 0; j < r; ++j) {
                        printf("%d  ", a[j][i]);
                    }
                printf("\n");
            }
    }