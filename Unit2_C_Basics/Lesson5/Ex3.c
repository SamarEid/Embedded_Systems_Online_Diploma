//
// Created by dell on 10/7/2023.
//
#include "stdio.h"
#include "string.h"

void reverse(char sentence[], int x){
    if (x == 0)
        return;
    printf("%c", sentence[x-1]);
    reverse(sentence, x-1);
}

int main(){
    char sentence[100];
    printf("Enter a sentence: ");
    gets(sentence);
    int x = strlen(sentence);
    reverse(sentence,x);
}