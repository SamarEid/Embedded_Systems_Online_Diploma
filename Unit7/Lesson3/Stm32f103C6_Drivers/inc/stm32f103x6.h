/*
 * stm32f103x6.h
 *
 *  Created on: Mar 13, 2024
 *      Author: dell
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//----------------------------
//Includes
//----------------------------
#include "stdlib.h"
#include <stdint.h>

//----------------------------
//Base addresses for Memories
//----------------------------
#define FLASH_Memory_BASE						0x08000000UL
#define System_Memory_BASE						0x1FFFF000UL
#define SRAM_Memory_BASE						0x20000000UL

#define Peripherals_BASE						0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE		0xE0000000UL

//----------------------------
//Base addresses for AHB Peripherals
//----------------------------

//RCC
#define RCC_BASE								0x40021000UL

//----------------------------
//Base addresses for APB2 Peripherals
//----------------------------

//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE								0x40010800UL
#define GPIOB_BASE								0x40010C00UL
//C,D partially included in LQFP48 Package
#define GPIOC_BASE								0x40011000UL
#define GPIOD_BASE								0x40011400UL
//E Not included in LQFP48 Package
#define GPIOE_BASE								0x40011800UL
//---------

//AFIO
#define AFIO_BASE								0x40010000UL

//EXTI
#define EXTI_BASE								0x40010400UL


//----------------------------
//Base addresses for APB1 Peripherals
//----------------------------


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//RCC
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
}RCC_Tyepdef;

//GPIO
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_Tyepdef;

//AFIO
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	uint32_t RESERVED0; // 0x18
	volatile uint32_t MAPR2;
}AFIO_Tyepdef;


//EXTI
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_Tyepdef;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
//GPIO
#define GPIOA	((GPIO_Tyepdef *)GPIOA_BASE)
#define GPIOB	((GPIO_Tyepdef *)GPIOB_BASE)
#define GPIOC	((GPIO_Tyepdef *)GPIOC_BASE)
#define GPIOD	((GPIO_Tyepdef *)GPIOD_BASE)
#define GPIOE	((GPIO_Tyepdef *)GPIOE_BASE)

//RCC
#define RCC		((RCC_Tyepdef *)RCC_BASE)
//AFIO
#define AFIO	((AFIO_Tyepdef *)AFIO_BASE)
//EXTI
#define EXTI	((EXTI_Tyepdef *)EXTI_BASE)


//-*-*-*-*-*-*-*-*-*-*-*
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//GPIO
#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<6)
//AFIO
#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR |= 1<<0)


//-*-*-*-*-*-*-*-*-*-*-*
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#endif /* INC_STM32F103X6_H_ */
