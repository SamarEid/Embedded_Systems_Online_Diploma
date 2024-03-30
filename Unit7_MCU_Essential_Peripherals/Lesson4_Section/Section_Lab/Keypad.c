/*
 * Keypad.c
 *
 * Created: 3/13/2024 1:51:51 AM
 *  Author: dell
 */ 
#include "Keypad.h"

int keypad_Row[] = {R0,R1,R2,R3};
int keypad_Col[] = {C0,C1,C2,C3};

void Keypad_init(){
	KeypadDDR &= ~((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
	KeypadDDR |= (1<<C0 | 1<<C1 | 1<<C2 | 1<<C3);
	KeypadPort = 0xFF;
}
char Keypad_getKey(){
	int i,j;
	for(i = 0; i < 4; i++){
		KeypadPort |= (1<<keypad_Col[0] | 1<<keypad_Col[1] | 1<<keypad_Col[2] | 1<<keypad_Col[3]);
		KeypadPort &= ~(1<<keypad_Col[i]);
		for (j = 0; j < 4; j++)
		{
			if (!(KeypadPin & (1<<keypad_Row[j])))
			{
				while(!(KeypadPin & (1<<keypad_Row[j])));
				switch(i){
					case(0):
						if(j==0) return '7';
						else if (j == 1) return '4';
						else if (j == 2) return '1';
						else if (j == 3) return '?';
						break;
					case(1):
						if(j==0) return '8';
						else if (j == 1) return '5';
						else if (j == 2) return '2';
						else if (j == 3) return '0';
						break;
					case(2):
						if(j==0) return '9';
						else if (j == 1) return '6';
						else if (j == 2) return '3';
						else if (j == 3) return '=';
						break;
					case(3):
						if(j==0) return '/';
						else if (j == 1) return '*';
						else if (j == 2) return '-';
						else if (j == 3) return '+';
						break;	
				}
			}
		}
	}
	return 'N';
}