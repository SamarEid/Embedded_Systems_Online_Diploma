/*
 * GPIO.h
 *
 * Created: 3/24/2024 1:48:07 AM
 *  Author: dell
 */ 


#ifndef GPIO_H_
#define GPIO_H_





//-----------Includes------------
#include "Device_Header.h"


//-----------Macro Configuration references------------

// @ref GPIO_PINS_define
#define Px0			0
#define Px1			1
#define Px2			2
#define Px3			3
#define Px4			4
#define Px5			5
#define Px6			6
#define Px7			7
//----------------------------

//@ref GPIO_MODE_define
/*Table 20. Port Pin Configurations
	0: Input Tri-State(Hi-Z)
	1: Output
	2: Input Pull-up
*/
#define GPIO_INPUT			0
#define GPIO_OUTPUT			1
#define GPIO_PullUp_INPUT	2
//----------------------------------

/*@ref GPIO_PIN_State*/
#define GPIO_PIN_Set			1
#define GPIO_PIN_Reset			0

/*@ref GPIO_Port_State*/
// if you want any thing in between write it in binary when implementing the function (e.g. 0b10101010)
#define GPIO_Port_Set			0xFF
#define GPIO_Port_Reset			0x00
//----------------------------------

//-----------APIs------------

//PIN
void GPIO_Pin_Config(GPIO_Typdef* GPIOx, uint8_t pinNumber, uint8_t pinDir);
void GPIO_Pin_Write(GPIO_Typdef* GPIOx, uint8_t pinNumber, uint8_t val);
void GPIO_Pin_Toggle(GPIO_Typdef* GPIOx, uint8_t pinNumber);
uint8_t GPIO_Pin_Read(GPIO_Typdef* GPIOx, uint8_t pinNumber);

//Port
void GPIO_Port_Config(GPIO_Typdef* GPIOx,  uint8_t portDir);
void GPIO_Port_Write(GPIO_Typdef* GPIOx,  uint8_t val);
uint8_t GPIO_Port_Read(GPIO_Typdef* GPIOx);



#endif /* GPIO_H_ */