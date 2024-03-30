/*
 * stm32f103C6_RCC.c
 *
 *  Created on: Mar 27, 2024
 *      Author: dell
 */


//includes
#include "stm32f103C6_RCC.h"

/*Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16*/
const uint8_t APBFrescTable[8U] = {0,0,0,0,1,2,3,4}; // shift right == divide by 2

/*Bits 7:4 HPRE[3:0]: AHB prescaler
Set and cleared by software to control AHB clock division factor.
0xxx: SYSCLK not divided
1000: SYSCLK divided by 2
1001: SYSCLK divided by 4
1010: SYSCLK divided by 8
1011: SYSCLK divided by 16
1100: SYSCLK divided by 64
1101: SYSCLK divided by 128
1110: SYSCLK divided by 256
1111: SYSCLK divided by 512*/
const uint8_t AHBFresTable[16U] = {0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};

uint32_t MCAL_RCC_GETSYS_CLK1Freq(void){
	//Bits 3:2 SWS[1:0]: System clock switch status
/*	Set and cleared by hardware to indicate which clock source is used as system clock.
	00: HSI oscillator used as system clock
	01: HSE oscillator used as system clock
	10: PLL used as system clock
	11: Not applicable*/
	switch((RCC->CFGR >> 2) & 0b11){
	case 0:
		return HSI_RC_Clock;
		break;
	case 1:
		//needs to be calculated // HSE user needs to specify it
		return HSE_Clock;
		break;
	case 2:
		//needs to be calculated PLLCLK and PLLUML & PLL source MUX
		return 16000000;
		break;
	}
}
uint32_t MCAL_RCC_GETHCLKFreq(void){
	//Bits 7:4 HPRE[3:0]: AHB prescaler
	 return (MCAL_RCC_GETSYS_CLK1Freq() >> AHBFresTable[((RCC->CFGR >> 4) & 0xF)]);

}
uint32_t MCAL_RCC_GETPCLK1Freq(void){
	//Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
	 return (MCAL_RCC_GETHCLKFreq() >> APBFrescTable[((RCC->CFGR >> 8) & 0b111)]);
}
uint32_t MCAL_RCC_GETPCLK2Freq(void){
	//Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	 return (MCAL_RCC_GETHCLKFreq() >> APBFrescTable[((RCC->CFGR >> 11) & 0b111)]);
}
