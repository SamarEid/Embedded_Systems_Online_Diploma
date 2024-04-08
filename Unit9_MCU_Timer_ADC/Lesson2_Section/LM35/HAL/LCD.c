/*
 * LCD.c
 *
 * Created: 3/13/2024 1:51:39 AM
 *  Author: dell
 */ 
#include "LCD.h"


void LCD_lcd_init(void){
	_delay_ms(20);
	
	DDR_LCD_Control |= (1<<EN_Switch | 1<<RW | 1<<RS_Switch);
	LCD_Control &= ~(1<<EN_Switch | 1<<RW | 1<<RS_Switch);
	//DDR_LCD_Port = 0xFF;
	_delay_ms(15);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
	DDR_LCD_Port |= (0xFF<<Data_shift);
	LCD_send_command(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
	DDR_LCD_Port |= (0xF<<Data_shift);
	LCD_send_command(0x02);
	LCD_send_command(LCD_FUNCTION_4BIT_2LINES);
	#endif
	LCD_send_command(LCD_ENTRY_MODE);
	LCD_send_command(LCD_BEGIN_AT_FIRST_RAW);
	LCD_send_command(LCD_DISP_ON_CURSOR_BLINK);
}


void LCD_check_lcd_isbusy(void){
	DDR_LCD_Port &= ~(0xFF<<Data_shift);
	LCD_Control |= (1<<RW);
	LCD_Control &= ~(1<<RS_Switch);
	LCD_lcd_kick();
#ifdef EIGHT_BIT_MODE
	DDR_LCD_Port |= (0xFF<<Data_shift);
#endif
#ifdef FOUR_BIT_MODE
	DDR_LCD_Port |= (0xF0<<Data_shift);
#endif
	
	LCD_Control &= ~(1<<RW);
}
void LCD_lcd_kick(void){
	LCD_Control &= ~(1<<EN_Switch);
	asm volatile ("nop");
	asm volatile ("nop");
	_delay_ms(50);
	LCD_Control|= 1<<EN_Switch;
}
void LCD_send_command(unsigned char command){
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		LCD_Port = command;
		LCD_Control &= ~((1<<RW)|(1<<RS_Switch));
		LCD_lcd_kick();
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_Port = (LCD_Port & 0x0F) | (command &0xF0);
		LCD_Control &= ~((1<<RW)|(1<<RS_Switch));
		LCD_lcd_kick();
		_delay_ms(100);
		LCD_Port = (LCD_Port & 0x0F)| (command<<4);
		LCD_Control &= ~((1<<RW)|(1<<RS_Switch));
		LCD_lcd_kick();
	#endif
}
void LCD_send_character(unsigned char character){
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		LCD_Control |= 1<<RS_Switch;
		LCD_Port = (character << Data_shift);
		LCD_Control |= 1<<RS_Switch;
		LCD_Control &= ~(1<<RW);
		LCD_lcd_kick();
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_Port = (LCD_Port&0x0F)|(character &0xF0);
		LCD_Control |= 1<<RS_Switch;
		LCD_Control &= ~(1<<RW);
		LCD_lcd_kick();
		LCD_Port = (LCD_Port&0x0F)|(character<<4);
		LCD_Control |= 1<<RS_Switch;
		LCD_Control &= ~(1<<RW);
		LCD_lcd_kick();
	#endif
}
void LCD_send_string(char* string){
	int count = 0;
	while(*string > 0){
		count++;
		LCD_send_character(*string++);
		if(count == 16){
			LCD_gotoXY(1,0);
		}
		else if (count == 32){
			LCD_clear_screen();
			LCD_gotoXY(0,0);
			count = 0;
		}
	}
}

void LCD_clear_screen(){
	LCD_send_command(LCD_CLEAR_SCREEN);
}
void LCD_gotoXY(unsigned char line, unsigned char position){
	if(line == 0){
		if(position <16 && position >= 0)
			LCD_send_command(LCD_BEGIN_AT_FIRST_RAW+position);
	}
	else if(line == 1){
		if(position<16 && position>=0){
			LCD_send_command(LCD_BEGIN_AT_SECOND_RAW+position);
		}
	}
}
void LCD_display_number(int number){
	char str[7];
	sprintf(str,"%d",number);
	LCD_send_string(str);
}
void LCD_display_real_number(double number){
	char str[16];
	char *tmpsign = (number<0)? "-":"";
	float tmpval = (number<0)? -number:number;
	int tmpint1= tmpval;
	float tmpfrac = tmpval - tmpint1;
	int tmpint2 = tmpfrac * 10000;
	sprintf(str, "%s%d.%0.4d", tmpsign, tmpint1, tmpint2);
	LCD_send_string(str);
}