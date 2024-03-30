/*
 * Drivers.c
 *
 * Created: 3/24/2024 1:21:02 AM
 * Author : dell
 */ 

#define F_CPU 8000000UL
#include "util/delay.h"
#include "USART.h"
//#include "GPIO.h"
//#include "SPI.h"
#include "LCD.h"

char s[100];

void IRQ_CallBack(void){
	USART_Receive_String(s);
	LCD_gotoXY(0,0);
	LCD_send_string(s); 
}

int main(void)
{
	/*
	struct USART_Config cfg;
	cfg.Char_Size = USART_8_Bit_Char;
	cfg.IRQ_Enable = Disable_INT;
	cfg.Parity_Mode = USART_No_Parity;
	cfg.Receive = USART_Receive_Enable;
	cfg.Transmit = USART_Transmit_Enable;
	cfg.Speed_Mode = USART_Normal_Speed;
	cfg.StopBit = USART_1_StopBit;
	cfg.Synch_Mode = USART_Asynch;
	USART_Init(cfg);
	LCD_lcd_init();
	LCD_send_string("Usart_Interrupt");
	_delay_ms(100);
	LCD_clear_screen();
	USART_Transmit_String("hello");
	*/

	struct USART_Config usartCFG;
	usartCFG.Char_Size = USART_8_Bit_Char;
	usartCFG.Parity_Mode = USART_No_Parity;
	usartCFG.Receive = USART_Receive_Enable;
	usartCFG.Transmit = USART_Transmit_Enable;
	usartCFG.Speed_Mode = USART_Normal_Speed;
	usartCFG.Synch_Mode = USART_Asynch;
	usartCFG.StopBit = USART_1_StopBit;
	usartCFG.IRQ_Enable = Enable_INT_TX_RX;
	usartCFG.P_IRQ_CallBack = IRQ_CallBack;
	USART_Init(usartCFG);
	LCD_lcd_init();
	LCD_send_string("Usart_Interrupt");
	_delay_ms(100);
	LCD_clear_screen();
	
	char i = 'a';
	
	while (1)
	{
		LCD_gotoXY(1,0);	
		LCD_send_character(i++);
		_delay_ms(1000);
		LCD_clear_screen();
	
	}
}

