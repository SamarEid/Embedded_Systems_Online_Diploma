#include "stdio.h"
int main(){
    char x;
    printf("Enter an alphabet: ");
    scanf("%c", &x);
    if (x == 'a' || x == 'i' || x == 'o' || x == 'e' || x == 'u'
     || x == 'A' || x == 'I' || x == 'O' || x == 'E' || x == 'U')
        printf("%c is a vowel", x);
    else
        printf("%c is a constant", x);
}