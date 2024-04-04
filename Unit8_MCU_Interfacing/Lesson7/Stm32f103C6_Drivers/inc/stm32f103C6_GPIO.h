/*
 * stm32f103C6_GPIO.h
 *
 *  Created on: Mar 13, 2024
 *      Author: dell
 */

#ifndef INC_STM32F103C6_GPIO_H_
#define INC_STM32F103C6_GPIO_H_

//----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"

//----------------------------
//User type definitions (structures)
//----------------------------
typedef struct{
	uint16_t GPIO_PinNumber;		//Specifies GPIO pin to be configured
								//This parameter must be according to values of @ref GPIO_PINS_define

	uint16_t GPIO_MODE;			//Specifies the operating mode for selected pin
								//this parameter can be a value of @ref GPIO_MODE_define

	uint16_t GPIO_Output_Speed;	//Specifies the speed for the selected pins
								//This parameter can be a value of  @ref GPIO_SPEED_define
}GPIO_PinConfig_t;


//----------------------------
//Macros Configuration References
//----------------------------

/*@ref GPIO_PINS_define */
#define GPIOx_PIN_0					(uint16_t)0x0001
#define GPIOx_PIN_1					(uint16_t)0x0002
#define GPIOx_PIN_2					(uint16_t)0x0004
#define GPIOx_PIN_3					(uint16_t)0x0008
#define GPIOx_PIN_4					(uint16_t)0x0010
#define GPIOx_PIN_5					(uint16_t)0x0020
#define GPIOx_PIN_6					(uint16_t)0x0040
#define GPIOx_PIN_7					(uint16_t)0x0080
#define GPIOx_PIN_8					(uint16_t)0x0100
#define GPIOx_PIN_9					(uint16_t)0x0200
#define GPIOx_PIN_10				(uint16_t)0x0400
#define GPIOx_PIN_11				(uint16_t)0x0800
#define GPIOx_PIN_12				(uint16_t)0x1000
#define GPIOx_PIN_13				(uint16_t)0x2000
#define GPIOx_PIN_14				(uint16_t)0x4000
#define GPIOx_PIN_15				(uint16_t)0x8000
#define GPIOx_PIN_ALL				(uint16_t)0xFFFF // port
#define GPIOx_PIN_MASK				(uint16_t)0x0000ffff

/*@ref GPIO_MODE_define
 * In input mode (MODE[1:0]=00):
 *  0: Analog mode
 *  1: Floating input (reset state)
 *  1: Input with pull-up
 *  3: Input with pull-down
 *  In output mode (MODE[1:0] > 00):
 *  4: General purpose output push-pull
 *  5: General purpose output Open-drain
 *  6: Alternate function output Push-pull
 *  7: Alternate function output Open-drain
 *  8: Alternate function Input
 * */
#define GPIO_MODE_ANALOG			0x00000000u	//Analog input
#define GPIO_MODE_INPUT_FLO			0x00000001u //floating input
#define GPIO_MODE_INPUT_PU			0x00000002u //input pull-up
#define GPIO_MODE_INPUT_PD			0x00000003u	//input pull-down
#define GPIO_MODE_OUTPUT_PP			0x00000004u //general purpose output push-pull
#define GPIO_MODE_OUTPUT_OD			0x00000005u //general purpose output open-drain
#define GPIO_MODE_OUTPUT_AF_PP		0x00000006u //Alternate output push-pull
#define GPIO_MODE_OUTPUT_AF_OD		0x00000007u //Alternate output open-drain
#define GPIO_MODE_AF_INPUT			0x00000008u //Alternate input


/*@ref GPIO_SPEED_define
 * 01: Output mode, max speed 10 MHz. // 1
 * 10: Output mode, max speed 2 MHz.  // 2
 * 11: Output mode, max speed 50 MHz. // 3
 * */
#define GPIO_SPEED_10			0x0000001u
#define GPIO_SPEED_2			0x0000002u
#define GPIO_SPEED_50			0x0000003u

/*@ref GPIO_PIN_State*/
#define GPIO_PIN_Set			1
#define GPIO_PIN_Reset			0


/*@ref GPIO_PIN_Lock*/
#define GPIO_PIN_LOCK_Enable	1
#define GPIO_PIN_LOCK_Erorr		0

/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

// initialize and deinitialize
void MCAL_GPIO_Init(GPIO_Tyepdef *GPIOx, GPIO_PinConfig_t * PinConfig);
void MCAL_GPIO_DeInit(GPIO_Tyepdef *GPIOx);

// Reaad
uint16_t MCAL_GPIO_ReadPin(GPIO_Tyepdef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_Tyepdef *GPIOx);

// Write
void MCAL_GPIO_WritePin(GPIO_Tyepdef *GPIOx, uint16_t PinNumber, uint16_t Value);
void MCAL_GPIO_WritePort(GPIO_Tyepdef *GPIOx,uint16_t Value );

// Toggle
void MCAL_GPIO_TogglePin(GPIO_Tyepdef *GPIOx, uint16_t PinNumber);

// Lock pin
uint16_t MCAL_GPIO_LockPin(GPIO_Tyepdef *GPIOx, uint16_t PinNumber);


#endif /* INC_STM32F103C6_GPIO_H_ */
