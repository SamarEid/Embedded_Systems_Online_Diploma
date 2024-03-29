/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

typedef volatile unsigned int vuint32_t;
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

// register address
// GPIOA
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

// GPIOB
#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)

// RCC
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)


void Clock_init(){
	RCC_APB2ENR |= 1<<2; // enable clock GPIOA
	RCC_APB2ENR |= 1<<3; // enable clock GPIOB
}

void GPIO_init(){
	GPIOA_CRL = 0;
	GPIOA_CRH = 0;
	GPIOA_ODR = 0;

	// PA1--> floating input
	GPIOA_CRL &= ~(0b11<<4);  // input mode
	GPIOA_CRL |= (0b01<<6);   // CNF

	// PB1 --> output push pull
	GPIOB_CRL |= (0b01<<4);
	GPIOB_CRL &= ~(0b11<<6);

	// PA13 --> floating input
	GPIOA_CRH &= ~(0b11<<20);  // input mode
	GPIOA_CRH |= (0b01<<22);   // CNF

	// PB13 --> push pull output
	GPIOB_CRH |= (0b01<<20);
	GPIOB_CRH &= ~(0b11<<22);
}

void wait(uint32_t x){
	uint32_t i,j;
	for(i = 0; i <x; i++)
		for(j = 0; j < 255; j++);
}

int main(void)
{
    Clock_init();
    GPIO_init();
    while(1){
    	if(((GPIOA_IDR &(1<<1))>>1) == 0){
    		GPIOB_ODR ^= 1<<1;
    		while(((GPIOA_IDR &(1<<1))>>1) == 0);
    	}
    	if(((GPIOA_IDR &(1<<13))>>13) == 1){
    		GPIOB_ODR ^= 1<<13;
    	}
    	wait(1);
    }
}
