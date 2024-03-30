/*
 * Calculator.c
 *
 * Created: 3/13/2024 1:50:21 AM
 * Author : dell
 */ 

#include <avr/io.h>
#include "Keypad/Keypad.h"
#include "LCD/LCD.h"

#define F_CPU 800000UL

int main(void)
{
	LCD_lcd_init();
	Keypad_init();
	unsigned char key_pressed;
	unsigned char a[7] = {0}, b[7] = {0}, op = 0;
	int i = 0, j= 0;
	double result = 0;
    /* Replace with your application code */
    while (1) 
    {
		
		key_pressed = Keypad_getKey();
		switch(key_pressed){
			case('N'):
				continue;
			case('?'):
				LCD_clear_screen();
				op = 0, i= 0, j = 0;
				for(int i = 0; i < 9; i++)
					a[i] =0, b[i] = 0;
				continue;
			default:
				if(key_pressed <= '9' && key_pressed >= '0'){
					LCD_send_character(key_pressed);
					if(op == 0){
						a[i++] = key_pressed;
					}
					else{
						b[j++] = key_pressed;
					}
				}
				else if(key_pressed == '='){
					LCD_send_character(key_pressed);
					LCD_gotoXY(1,0);
					switch(op){
						case'+': 
							result = atoi(a)+atoi(b);
							break;
						case'-':
							result = atoi(a)-atoi(b);
							break;
						case'*':
							result = atoi(a)*atoi(b);
							break;
						case'/':
							result = atoi(a)/atoi(b);
							break;				
					}
					LCD_display_number(result);
					_delay_ms(1500);
					LCD_clear_screen();
					op = 0, i= 0, j = 0;
					for(int i = 0; i < 9; i++)
						a[i] =0, b[i] = 0;
				}
				else{
					LCD_send_character(key_pressed);
					op = key_pressed;
					
				}
		}
    }
}

