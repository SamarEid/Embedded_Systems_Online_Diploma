/*
 * LCD.h
 *
 * Created: 3/13/2024 1:51:25 AM
 *  Author: dell
 */ 


#ifndef LCD_H_
#define LCD_H_

//#include "avr/io.h"
#include "util/delay.h"
#include "Device_Header.h"

#define LCD_Port				PORTA
#define DDR_LCD_Port			DDRA
#define Data_shift				4		//	0:8bit data mode | 4:4bit data mode
#define LCD_Control				PORTB
#define DDR_LCD_Control			DDRB
#define EN_Switch				3
#define RW						2
#define RS_Switch				1

//-----LCD Mode----------------------
//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

#define LCD_REGISTER_SELECT_PIN						(0)
#define LCD_READ_WRITE_PIN							(1)
#define LCD_ENABLE_PIN								(2)
#define LCD_REGISTER_SELECT_ENABLE					(1)
#define LCD_REGISTER_SELECT_DISABLE					(0)
#define READ_FROM_LCD								(1)
#define WRITE_TO_LCD								(0)
#define LCD_ENABLE									(1)
#define LCD_DISABLE									(0)
#define LCD_FIRTST_LINE								(0)
#define LCD_SECOND_LINE								(1)

//-------LCD Commands---------------
#define LCD_FUNCTION_8BIT_2LINES					(0x38)
#define LCD_FUNCTION_4BIT_2LINES					(0x28)
#define LCD_MOVE_DISP_RIGHT							(0x1C)
#define LCD_MOVE_DISP_LEFT							(0x18)
#define LCD_MOVE_CURSOR_LEFT						(0x10)
#define LCD_MOVE_CURSOR_RIGHT						(0x14)
#define LCD_DISP_OFF								(0x08)
#define LCD_DISP_ON_CURSOR							(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK					(0x0F)
#define LCD_DISP_ON_BLINK							(0x0D)
#define LCD_DISP_ON									(0x0C)
#define LCD_ENTRY_DEC								(0x04)
#define LCD_ENTRY_DEC_SHIFT							(0x05)
#define LCD_ENTRY_INC								(0x06)
#define LCD_ENTRY_INC_SHIFT							(0x07)
#define LCD_BEGIN_AT_FIRST_RAW						(0x80)
#define LCD_BEGIN_AT_SECOND_RAW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)


//----------APIs--------------------
void LCD_check_lcd_isbusy(void);
void LCD_lcd_kick(void);
void LCD_send_command(unsigned char command);
void LCD_send_character(unsigned char character);
void LCD_send_string(char* string);
void LCD_lcd_init(void);
void LCD_clear_screen();
void LCD_gotoXY(unsigned char line, unsigned char position);
void LCD_display_number(int number);
void LCD_display_real_number(double number);

#endif /* LCD_H_ */