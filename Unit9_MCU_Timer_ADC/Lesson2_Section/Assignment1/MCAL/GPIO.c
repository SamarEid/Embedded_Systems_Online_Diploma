/*
 * GPIO.c
 *
 * Created: 3/24/2024 1:48:16 AM
 *  Author: dell
 */ 
//==================================
//======Includes===========
//================================
#include "GPIO.h"

//-----------APIs------------

/**===================================================
 *  @Fn -  GPIO_Pin_Config
 *  @brief - Configure a specific pin 
 *  @param [in] - * GPIOx: To select the GPIO peripheral x could be (A,B,C,D)
 *	@param [in] - pinNumber: the number of the pin
 *	@param [in] - pinDir: the direction of the pin (input-output)
 *  @retval - none
 *  Note -
 **/
void GPIO_Pin_Config(GPIO_Typdef* GPIOx, uint8_t pinNumber, uint8_t pinDir){
	if(pinDir == GPIO_OUTPUT){
		Set_Bit(GPIOx->DDR,pinNumber);
	}
	else if(pinDir == GPIO_INPUT){
		Clr_Bit(GPIOx->DDR,pinNumber);
		Clr_Bit(GPIOx->PORT,pinNumber);
	}
	else if (pinDir == GPIO_PullUp_INPUT)
	{
		Clr_Bit(GPIOx->DDR,pinNumber);
		Set_Bit(GPIOx->PORT,pinNumber);
	}
}
/**===================================================
 *  @Fn -  GPIO_Pin_Write
 *  @brief - Write a value to a specific pin
 *  @param [in] - * GPIOx: To select the GPIO peripheral x could be (A,B,C,D)
 *	@param [in] - pinNumber: the number of the pin
 *	@param [in] - val: the value to be written on the pin
 *  @retval - none
 *  Note -
 **/
void GPIO_Pin_Write(GPIO_Typdef* GPIOx, uint8_t pinNumber, uint8_t val){
	if(val == GPIO_PIN_Set)
		Set_Bit(GPIOx->PORT,pinNumber);
	else
		Clr_Bit(GPIOx->PORT,pinNumber);
}
/**===================================================
 *  @Fn -  GPIO_Pin_Toggle
 *  @brief - Toggle a specific pin
 *  @param [in] - * GPIOx: To select the GPIO peripheral x could be (A,B,C,D)
 *	@param [in] - pinNumber: the number of the pin
 *  @retval - none
 *  Note -
 **/
void GPIO_Pin_Toggle(GPIO_Typdef* GPIOx, uint8_t pinNumber){
	Toggle_Bit(GPIOx->PORT,pinNumber);
}
/**===================================================
 *  @Fn -   GPIO_Pin_Read
 *  @brief - Read a specific pin
 *  @param [in] - * GPIOx: To select the GPIO peripheral x could be (A,B,C,D)
 *	@param [in] - pinNumber: the number of the pin
 *  @retval - The value of the pin
 *  Note -
 **/
uint8_t GPIO_Pin_Read(GPIO_Typdef* GPIOx, uint8_t pinNumber){
	return (uint8_t)Read_Bit(GPIOx->PIN,pinNumber);
}
//Port

/**===================================================
 *  @Fn -  GPIO_Port_Config
 *  @brief - Configure a specific Port 
 *  @param [in] - * GPIOx: To select the GPIO peripheral x could be (A,B,C,D)
 *	@param [in] - portDir: the direction of the port (input-output)
 *  @retval - none
 *  Note -
 **/
void GPIO_Port_Config(GPIO_Typdef* GPIOx,  uint8_t portDir){
	if(portDir == GPIO_OUTPUT)
		GPIOx->DDR = 0xFF;
	else if(portDir == GPIO_INPUT){
		GPIOx->DDR = 0x00;
		GPIOx->PORT = 0x00;
	}
	else if(portDir == GPIO_PullUp_INPUT){
		GPIOx->DDR = 0x00;
		GPIOx->PORT = 0xFF;
	}
}
/**===================================================
 *  @Fn -  GPIO_Port_Write
 *  @brief - Write a value to a specific port
 *  @param [in] - * GPIOx: To select the GPIO peripheral x could be (A,B,C,D)
 *	@param [in] - val: the value to be written on the port
 *  @retval - none
 *  Note -
 **/
void GPIO_Port_Write(GPIO_Typdef* GPIOx,  uint8_t val){
	GPIOx->PIN = val;
}
/**===================================================
 *  @Fn -   GPIO_Port_Read
 *  @brief - Read a specific Port
 *  @param [in] - * GPIOx: To select the GPIO peripheral x could be (A,B,C,D)
 *  @retval - The value of the Port
 *  Note -
 **/
uint8_t GPIO_Port_Read(GPIO_Typdef* GPIOx){
	return GPIOx->PIN;
}
