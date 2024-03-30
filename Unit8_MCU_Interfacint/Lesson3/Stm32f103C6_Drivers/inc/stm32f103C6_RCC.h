/*
 * stm32f103C6_RCC.h
 *
 *  Created on: Mar 27, 2024
 *      Author: dell
 */

#ifndef INC_STM32F103C6_RCC_H_
#define INC_STM32F103C6_RCC_H_

//includes
#include "stm32f103x6.h"
#include "stm32f103C6_GPIO.h"

//MACROS
#define HSI_RC_Clock		(uint32_t)8000000
#define HSE_Clock			(uint32_t)16000000

uint32_t MCAL_RCC_GETSYS_CLK1Freq(void);
uint32_t MCAL_RCC_GETHCLKFreq(void);
uint32_t MCAL_RCC_GETPCLK1Freq(void);
uint32_t MCAL_RCC_GETPCLK2Freq(void);



#endif /* INC_STM32F103C6_RCC_H_ */
