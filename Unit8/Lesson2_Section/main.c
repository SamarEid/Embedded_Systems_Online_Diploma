/*
 * USART.c
 *
 * Created: 3/23/2024 12:41:39 AM
 * Author : dell
 */ 

#include "LCD.h"
#include "USART.h"
uint8_t x;
char s[100];
int main(void)
{
    /* Replace with your application code */
	LCD_lcd_init();
	USART_Init();
	LCD_send_string("USART Tx, Rx ");
	USART_Send_Char('S');
	USART_Send_Char('a');
	USART_Send_Char('m');
	USART_Send_Char('a');
	USART_Send_Char('r');
	USART_Send_String("hello");
    while (1) 
    {
			LCD_gotoXY(1,0);
			//x = USAERT_Rec_Char();
			//LCD_send_character(x);
			USART_Rec_String(s);
			LCD_send_string(s);
    }
}

