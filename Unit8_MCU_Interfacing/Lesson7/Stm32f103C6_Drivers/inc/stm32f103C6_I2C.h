/*
 * stm32f103C6_I2C.h
 *
 *  Created on: Apr 3, 2024
 *      Author: dell
 */

#ifndef INC_STM32F103C6_I2C_H_
#define INC_STM32F103C6_I2C_H_

//includes
#include "stm32f103x6.h"
#include "stm32f103C6_GPIO.h"
#include "stm32f103C6_RCC.h"

//----------------------------
//User type definitions (structures)
//----------------------------
struct S_I2C_Device_Address{
	uint16_t Enable_Dual_ADD;  // 1:Enable  0:Disable
	uint16_t Primary_Slave_Address;
	uint16_t Secondary_Slave_Address;
	uint32_t I2C_Addressing_Slave_Mode; //@ref I2C_Addressing_Slave_Mode_define
};

typedef enum{
	I2C_EV_Stop,
	I2C_Error_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_Data_REQ,
	I2C_EV_Data_RCV
}Slave_State;

typedef enum{
	With_Stop,
	Without_Stop
}Stop_Condition;

typedef enum{
	Start,
	repeated_start
}Repeated_Start;

typedef enum{
	Disable = 0,
	Enable = 1
}Funcional_State;
typedef enum{
	Reset = 0,
	Set = 1
}FlagStatus;

#define I2C_MASTER_BYTE_TRANSMITTING	(uint32_t)(0x00070080) /*TRA, Busy, MSL, TXE*/
typedef enum{
	I2C_Flag_Busy = 0,
	EV5,
	EV6,
	EV8,
	EV8_1,
	EV7,
	MASTER_BYTE_TRANSMITTING = (uint32_t)(0x00070080)

}Status;
typedef enum{
	Transmitter = 0,
	Receiver = 1
}I2C_Dir;


typedef struct{
	uint32_t	I2C_CLK_Speed;		//Specify the clock frequency
	// must be set according to @ref I2C_Clk_define

	uint32_t	Stretch_Mode;		//Enable/Disable stretching
	//must be set according to @ref I2C_StretchMode_define
	uint32_t	I2C_Mode;			//Specify I2C Mode
	//must be set according to @ref I2C_Mode_Define

	struct S_I2C_Device_Address I2C_Device_Address;

	uint32_t	I2C_ACK_Contorl;	// Enable/Disable Ack
	// @ref I2C_ACK_Define

	uint32_t	General_Call_Address_Detection;	//@ref General_Call_define

	void(* P_Slave_Event_CallBack)(Slave_State state)	;
	uint32_t	Master_Mode;
}I2C_Config;

//----------------------------
//Macros Configuration References
//----------------------------

// @ref I2C_MASTER_MODE_DEFINE
/* I2C_CCR
 * Bit 15 F/S: I2C master mode selection
 * 0: Sm mode I2C
 * 1: Fm mode I2C
 */
#define I2C_MASTER_MODE_SM						(uint32_t)(0)
#define I2C_MASTER_MODE_FM						(uint32_t)(1<<15)

/*@ref I2C_Clk_define*/
//Standard mode up to 100 KHZ
//Fast mode up to 400 KHZ
#define I2C_Clk_SM_50K			(50000U)
#define I2C_Clk_SM_100K			(100000U)
#define I2C_Clk_FM_200K			(200000U)// Fast Mode not supported
#define I2C_Clk_FM_400K			(400000U)// Fast Mode not supported

/*@ref I2C_StretchMode_define*/
/*Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until it is reset by software.
0: Clock stretching enabled
1: Clock stretching disabled*/
#define I2C_StretchMode_Enable		(0x00000000U)
#define I2C_StretchMode_Disable		I2C_CR1_NOSTRETCH

/*@ref I2C_Mode_Define */
/*Bit 1 SMBUS: SMBus mode
 * 0: I2C mode
 * 1: SMBus mode*/
#define I2C_Mode_I2C				0
#define I2C_Mode_SMBus				I2C_CR1_SMBUS

/*@ref I2C_Addressing_Slave_Mode_define */
/*Bit 15 ADDMODE Addressing mode (slave mode)
0: 7-bit slave address (10-bit address not acknowledged)
1: 10-bit slave address (7-bit address not acknowledged)*/
#define I2C_Addressing_Slave_Mode_7Bit		(uint16_t)0<<15
#define I2C_Addressing_Slave_Mode_10Bit		(uint16_t)1<<15

/*@ref I2C_ACK_Define*/
/*Bit 10 ACK: Acknowledge enable
This bit is set and cleared by software and cleared by hardware when PE=0.
0: No acknowledge returned
1: Acknowledge returned after a byte is received (matched address or data)*/
#define I2C_ACK_Enable							I2C_CR1_ACK
#define I2C_ACK_Disable							(0x00000000U)

/*@ref General_Call_define*/
/*Bit 6 ENGC: General call enable
0: General call disabled. Address 00h is NACKed.
1: General call enabled. Address 00h is ACKed*/
#define General_Call_Enable					I2C_CR1_ENGC
#define General_Call_Disable				(0x00000000U)

//-------------------------------------------------------------
//----------APIs Supported By "MCAL USART DRIVER"--------------
//-------------------------------------------------------------
void MCAL_I2C_Init(I2C_typedef* I2Cx, I2C_Config* i2cConfig);
void MCAL_I2C_DeInit(I2C_typedef* I2Cx);

void MCAL_I2C_GPIO_Set_Pins(I2C_typedef* I2Cx);

//Master Polling Mechanism
void MCAL_I2C_Master_TX(I2C_typedef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t datalen, Stop_Condition stop, Repeated_Start start);
void MCAL_I2C_Master_RX(I2C_typedef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t datalen, Stop_Condition stop, Repeated_Start start);

//Slave Interrupt Mechanism
void MCAL_I2C_SlaveSendData(I2C_typedef* I2Cx, uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_typedef* I2Cx);

//Generic APIs
void I2C_GeneratStart(I2C_typedef* I2Cx,Funcional_State NewState, Repeated_Start start);
FlagStatus I2C_GetFlagStatus(I2C_typedef* I2Cx, Status flag);
void I2C_SendAddress(I2C_typedef* I2Cx, uint16_t Address, I2C_Dir direction);
void I2C_GenerateStop(I2C_typedef* I2Cx,Funcional_State NewState);
void I2C_ACK_Config(I2C_typedef* I2Cx, Funcional_State NewState);

#endif /* INC_STM32F103C6_I2C_H_ */
