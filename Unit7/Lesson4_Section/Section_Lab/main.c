/*
 * Section4.c
 *
 * Created: 3/16/2024 6:09:08 AM
 * Author : dell
 */ 
#include "lcd.h"
#include "keypad.h"
#include "GPIO.h"

int main(void)
{
	LCD_INIT();
	LCD_WRITE_STRING("Learn-In-Depth");
    /* Replace with your application code */
    while (1) 
    {
    }
}

