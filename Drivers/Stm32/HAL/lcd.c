/*
 * lcd.c
 *
 * Created: 16/3/2021 6:32:00 PM
 *  Author: dell
 */ 

#include "lcd.h"
GPIO_PinConfig_t PinCFG;

void wait(uint32_t x){
	uint32_t i,j;
	for(i = 0; i <x; i++)
		for(j = 0; j < 255; j++);
}

void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_lcd_kick(){
	//LCD_CTRL |= (1 << EN_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_Set);
	wait(50);
	//LCD_CTRL &= ~(1 << EN_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_Reset);

}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

void LCD_INIT(){
	wait(20);

	//EN_Switch, RS_Switch, RW_Switch input HighZ floating input
	PinCFG.GPIO_PinNumber = EN_SWITCH;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = RS_SWITCH;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = RW_SWITCH;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	wait(15);
	// DATA pins output push-pull
	PinCFG.GPIO_PinNumber = GPIOx_PIN_0;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_1;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_2;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_3;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_4;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_5;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_6;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_7;
	PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	LCD_clear_screen();
//#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
//#endif
//#ifdef FOUR_BIT_MODE
//LCD_WRITE_COMMAND(0x02);		/* send for 4 bit initialization of LCD  */
//LCD_WRITE_COMMAND(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
//LCD_WRITE_COMMAND(0x0c);              /* Display on cursor off*/
//LCD_WRITE_COMMAND(0x06);              /* Increment cursor (shift cursor to right)*/
//LCD_WRITE_COMMAND(0x01);
//LCD_WRITE_COMMAND(0x02);
//LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
//#endif
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_check_lcd_isbusy(){
	//DataDir_LCD_PORT &= ~(0xFF<<DATA_shift);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_0;
	PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_1;
	PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_2;
	PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_3;
	PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_4;
	PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_5;
	PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_6;
	PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);

	PinCFG.GPIO_PinNumber = GPIOx_PIN_7;
	PinCFG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCFG);


	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_Set);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_Reset);

//	LCD_CTRL |= (1 << RW_SWITCH);
//	LCD_CTRL &= ~(1 << RS_SWITCH);
	LCD_lcd_kick();
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_Reset);

	//LCD_CTRL &= ~(1 << RW_SWITCH);

}


void LCD_WRITE_COMMAND(unsigned char command){
//#ifdef EIGHT_BIT_MODE
//	LCD_check_lcd_isbusy();
	//LCD_PORT = command;
	//LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	MCAL_GPIO_WritePort(LCD_CTRL, command);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_Reset);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_Reset);

	wait(1);
	LCD_lcd_kick();
//#endif
//#ifdef FOUR_BIT_MODE
//	LCD_check_lcd_isbusy();
//	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
//	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
//	LCD_lcd_kick ();
//	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
//	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
//	LCD_lcd_kick();
//#endif
}

void LCD_WRITE_CHAR(unsigned char character){
//#ifdef EIGHT_BIT_MODE
//	LCD_check_lcd_isbusy();
//	LCD_PORT = character;
//	LCD_CTRL &= ~(1 << RW_SWITCH);
//	LCD_CTRL |= (1 << RS_SWITCH);
	MCAL_GPIO_WritePort(LCD_CTRL, character);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_Reset);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_Set);

	wait(1);
	LCD_lcd_kick();
//#endif
//#ifdef FOUR_BIT_MODE
//	//LCD_check_lcd_isbusy();
//	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
//	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
//	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
//	LCD_lcd_kick();
//	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
//	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
//	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
//	LCD_lcd_kick ();
//#endif
}

void LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}
