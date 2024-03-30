//
// Created by dell on 10/31/2023.
//
#include "stdio.h"

int main(){
    char alpha[26];
    int x = 65;
    for (int i =0 ; i < 26; i++){
        alpha[i] = (char ) x;
        x++;
    }
    char* p_alpha = alpha;
    for(int i =0 ; i < 26; i++){
        printf("%c ", *p_alpha++);
    }
}