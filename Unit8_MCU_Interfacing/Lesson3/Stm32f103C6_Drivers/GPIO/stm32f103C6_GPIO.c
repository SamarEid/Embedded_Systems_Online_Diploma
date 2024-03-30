/*
 * stm32f103C6_GPIO.c
 *
 *  Created on: Mar 13, 2024
 *      Author: dell
 */

#include "stm32f103x6.h"
#include "stm32f103C6_GPIO.h"


uint16_t Get_CRLH_Position(uint16_t PinNumber){
	switch(PinNumber){
	case GPIOx_PIN_0:
		return 0;
		break;
	case GPIOx_PIN_1:
		return 4;
		break;
	case GPIOx_PIN_2:
		return 8;
		break;
	case GPIOx_PIN_3:
		return 12;
		break;
	case GPIOx_PIN_4:
		return 16;
		break;
	case GPIOx_PIN_5:
		return 20;
		break;
	case GPIOx_PIN_6:
		return 24;
		break;
	case GPIOx_PIN_7:
		return 28;
		break;

	case GPIOx_PIN_8:
		return 0;
		break;
	case GPIOx_PIN_9:
		return 4;
		break;
	case GPIOx_PIN_10:
		return 8;
		break;
	case GPIOx_PIN_11:
		return 12;
		break;
	case GPIOx_PIN_12:
		return 16;
		break;
	case GPIOx_PIN_13:
		return 20;
		break;
	case GPIOx_PIN_14:
		return 24;
		break;
	case GPIOx_PIN_15:
		return 28;
		break;
	}
	return 0;
}

/**===================================================
 *  @Fn -  MCAL_GPIO_Init
 *  @brief - Initialize the GPIOx PINy
 *  @param [in] - GPIOx :
 *  @param [in] -PinConfig:
 *  @retval - none
 *  Note - in stm32f103c6  A,B fully included in LQFP48 Package
 *  		C,D partially included in LQFP48 Package
 *  		E Not included in LQFP48 Package
 **/
void MCAL_GPIO_Init(GPIO_Tyepdef *GPIOx, GPIO_PinConfig_t * PinConfig){
	uint8_t PIN_Config = 0;
	volatile uint32_t* configregester = NULL;
	// check whether pin is low (0-->7) or high (8-->15)
	configregester = (PinConfig->GPIO_PinNumber < GPIOx_PIN_8)? &GPIOx->CRL:&GPIOx->CRH;

	// clear CNF, MODE
	*configregester &= ~(0xf<<Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	// if pin is output
	if((PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD) ||(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP)
			|| (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP))
	{
		PIN_Config = (((PinConfig->GPIO_MODE - 4)<<2) | (PinConfig->GPIO_Output_Speed))& 0x0f;
	}
	// if pin is input
	else{
		// MODE = 00
		if((PinConfig->GPIO_MODE == GPIO_MODE_ANALOG) || (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO))
		{
			PIN_Config = (((PinConfig->GPIO_MODE)<<2) | 0x0)& 0x0f;
		}
		else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT)
		{
			PIN_Config = ((GPIO_MODE_INPUT_FLO<<2) | 0x0)& 0x0f;
		}
		else{
			PIN_Config = ((GPIO_MODE_INPUT_PU<<2) | 0x0)& 0x0f;
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU){
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else{
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}
	*configregester |= PIN_Config<<Get_CRLH_Position(PinConfig->GPIO_PinNumber);
}


/**===================================================
 *  @Fn -MCAL_GPIO_DeInit
 *  @brief - reset all GPIO registers
 *  @param [in] -GPIOx
 *  @retval - none
 *  Note - none
 **/

void MCAL_GPIO_DeInit(GPIO_Tyepdef *GPIOx){
	// if the MCU doesn't have a reset peripheral use the reset value given to each register
	if(GPIOx == GPIOA){
		RCC->APB2RSTR |= 1<<2;
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB){
		RCC->APB2RSTR |= 1<<3;
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC){
		RCC->APB2RSTR |= 1<<4;
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx == GPIOD){
		RCC->APB2RSTR |= 1<<5;
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if(GPIOx == GPIOE){
		RCC->APB2RSTR |= 1<<6;
		RCC->APB2RSTR &= ~(1<<6);
	}
}


/**===================================================
 *  @Fn -MCAL_GPIO_ReadPin
 *  @brief - reads a specific pin
 *  @param [in] -GPIOx
 *  @param [in] -PinNumber
 *  @retval - none
 *  Note - none
 **/
uint16_t MCAL_GPIO_ReadPin(GPIO_Tyepdef *GPIOx, uint16_t PinNumber){
	if((GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_Reset){
		return GPIO_PIN_Set;
	}
	else
		return GPIO_PIN_Reset;
}

/**===================================================
 *  @Fn -MCAL_GPIO_ReadPort
 *  @brief - reads a port
 *  @param [in] -GPIOx
 *  @retval - none
 *  Note - none
 **/
uint16_t MCAL_GPIO_ReadPort(GPIO_Tyepdef *GPIOx){
	return (uint16_t)GPIOx->IDR;
}

/**===================================================
 *  @Fn -MCAL_GPIO_WritePin
 *  @brief - writes on a specific pin
 *  @param [in] -GPIOx
 *  @param [in] -PinNumber
 *  @retval - none
 *  Note - none
 **/
void MCAL_GPIO_WritePin(GPIO_Tyepdef *GPIOx, uint16_t PinNumber, uint16_t Value){
	if(Value != GPIO_PIN_Reset){
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
		GPIOx->BRR = (uint32_t)PinNumber;
}


/**===================================================
 *  @Fn -MCAL_GPIO_WritePort
 *  @brief - writes on a port
 *  @param [in] -GPIOx
 *  @retval - none
 *  Note - none
 **/
void MCAL_GPIO_WritePort(GPIO_Tyepdef *GPIOx,uint16_t Value ){
	GPIOx->ODR = (uint32_t)Value;
}

/**===================================================
 *  @Fn -MCAL_GPIO_TogglePin
 *  @brief - toggles a specific pin
 *  @param [in] -GPIOx
 *  @param [in] -PinNumber
 *  @retval - none
 *  Note - none
 **/
void MCAL_GPIO_TogglePin(GPIO_Tyepdef *GPIOx, uint16_t PinNumber){
	GPIOx->ODR ^= PinNumber;
}

/**===================================================
 *  @Fn -MCAL_GPIO_LockPin(
 *  @brief - used to lock the configuration of the port bits - no longer possible to modify the value of the port bit until the next reset.
 *  @param [in] -GPIOx
 *  @param [in] -PinNumber
 *  @retval - none
 *  Note - none
 **/
uint16_t MCAL_GPIO_LockPin(GPIO_Tyepdef *GPIOx, uint16_t PinNumber){
	/*LCKK[16]: Lock key This bit can be read anytime.
	 *  It can only be modified using the Lock Key Writing Sequence.
	 *   0: Port configuration lock key not active
	 *   1: Port configuration lock key active.
	 *   GPIOx_LCKR register is locked until the next reset.
		Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
		Any error in the lock sequence will abort the lock.*/

	volatile uint32_t tmp = 1<<16;
	tmp |= PinNumber;
//	LOCK key writing sequence:
//			Write 1
	GPIOx->LCKR = tmp;
//			Write 0
	GPIOx->LCKR = PinNumber;
//			Write 1
	GPIOx->LCKR = tmp;
//			Read 0
	tmp = GPIOx->LCKR;
//			Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & 1<<16)){
		return GPIO_PIN_LOCK_Enable;
	}
	else
		return GPIO_PIN_LOCK_Erorr;
}
