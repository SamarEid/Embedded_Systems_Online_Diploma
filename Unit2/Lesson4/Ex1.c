#include "stdio.h"

int main(){
        float a[2][2];
        float b[2][2];
        printf("Enter the elements of 1st matrix: \n");
        for (int  i = 0;  i < 2; ++ i) {
                for (int j = 0; j < 2; ++j) {
                        float x;
                        printf("Enter a%d%d: ",i+1, j+1);
                        scanf("%f",&x);
                        a[i][j] = x;
                    }
            }
        printf("Enter the elements of 2nd matrix: \n");
        for (int  i = 0;  i < 2; ++ i) {
                for (int j = 0; j < 2; ++j) {
                        float x;
                        printf("Enter b%d%d: ",i+1, j+1);
                        scanf("%f",&x);
                        b[i][j] = x;
                    }
            }
        float sum[2][2];
        printf("Sum Of Matrix: \n");

                for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                        sum[i][j] = a[i][j]+b[i][j];
                        printf("%.1f  ", sum[i][j]);
                    }
                printf("\n");
            }

            }