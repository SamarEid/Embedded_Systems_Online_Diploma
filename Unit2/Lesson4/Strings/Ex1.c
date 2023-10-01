#include "stdio.h"
#include "string.h"
int main(){
    char string[100];
    printf("Enter a string: ");
    gets(string);
    char ch;
    printf("Enter a character to find frequency: ");
    scanf("%c", &ch);
    int count = 0;
    for (int i = 0; i < strlen(string); i++){
        if (string[i] == ch)
            count++;
    }
    printf("Frequency of %c = %d",  ch ,count);
}