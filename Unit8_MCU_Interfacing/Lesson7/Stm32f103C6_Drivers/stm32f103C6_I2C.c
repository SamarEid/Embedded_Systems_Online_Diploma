/*
 * stm32f103C6_I2C.c
 *
 *  Created on: Apr 3, 2024
 *      Author: dell
 */


//includes
#include "stm32f103C6_I2C.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
I2C_Config global_I2C_Config[2] = {NULL,NULL};

/*
 * =======================================================================================
 * 							Generic MACROS
 * =======================================================================================
 */
#define I2C1_Index			0
#define I2C2_Index			1

/*
 * =======================================================================================
 * 							APIs
 * =======================================================================================
 */

/**===================================================
 *  @Fn - MCAL_I2C_Init
 *  @brief - Initialize the I2C
 *  @param [in] - I2Cx : Specify which I2C to initialize
 *  @param [in] - i2cConfig: the configuration to which the I2C should be configured
 *  @retval - none
 *  Note - Supports I2C mode only (Doesn't support SMBus)
 *  		- Only supports Standard mode (SM) and doesn't Support Fast mode (FM)
 **/
void MCAL_I2C_Init(I2C_typedef* I2Cx, I2C_Config* i2cConfig){
	uint16_t tmpreg = 0, freqrange = 0;
	uint32_t pClk1 = 8000000;
	uint16_t result = 0;
	// Enable RCC Clock
	if(I2Cx == I2C1){
		global_I2C_Config[I2C1_Index] = *i2cConfig;
		RCC_I2C1_CLK_EN();
	}
	else if (I2Cx == I2C2){
		global_I2C_Config[I2C2_Index] = *i2cConfig;
		RCC_I2C2_CLK_EN();
	}
	//check mode
	if(i2cConfig->I2C_Mode == I2C_Mode_I2C){
		//--------INIT Timing-----------
		//Get the i2cx cr2 value
		tmpreg = I2Cx->CR2;
		//Clear frequency FREQ[0:5]bits
		tmpreg &= ~(I2C_CR2_FREQ_Msk);
		//Get pClk1 frequency value
		pClk1 = MCAL_RCC_GETPCLK1Freq();
		//Set frequency based on  pclk1 value
		freqrange = (uint16_t)(pClk1/1000000);
		tmpreg |= freqrange;
		I2Cx->CR2 = tmpreg;

		//Configure the clock control registers (I2C_CCR)
		// Disable the selected I2C peripheral to configure time
		I2Cx->CR1 &= ~(I2C_CR1_PE);
		tmpreg = 0;
		//Configure speed in standard mode
		if((i2cConfig->I2C_CLK_Speed == I2C_Clk_SM_50K) ||(i2cConfig->I2C_CLK_Speed == I2C_Clk_SM_100K ))
		{
			//Stanard mode speed calculation
			result = (uint16_t)(pClk1/(i2cConfig->I2C_CLK_Speed <<1));
			tmpreg |= result;
			I2Cx->CCR = tmpreg;

			//Configure rise time
			I2Cx->TRISE = freqrange + 1;
		}
		else{
			//  Fast-Mode Not supported
		}

		//------------CR1 Configuration----------------
		tmpreg = I2Cx->CR1;
		tmpreg |= (uint16_t)(i2cConfig->Stretch_Mode | i2cConfig->I2C_ACK_Contorl | i2cConfig->I2C_Mode | i2cConfig->General_Call_Address_Detection);
		I2Cx->CR1 = tmpreg;

		tmpreg = 0;
		//-----------OAR1 & OAR2 Configuration
		if(i2cConfig->I2C_Device_Address.Enable_Dual_ADD == 1){
			tmpreg = I2C_OAR2_ENDUAL;
			tmpreg |= i2cConfig->I2C_Device_Address.Secondary_Slave_Address << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR2 = tmpreg;

		}
		tmpreg = 0;
		tmpreg |= i2cConfig->I2C_Device_Address.Primary_Slave_Address << 1;
		tmpreg |= i2cConfig->I2C_Device_Address.I2C_Addressing_Slave_Mode;
		I2Cx->OAR1 = tmpreg;

	}
	else{
		//SMBus Not Supported
	}

	//Interrupt Mode (Slave Mode) // Check callback pointer != Null
	if(i2cConfig->P_Slave_Event_CallBack != NULL){
		//Enable IRQ
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN);
		I2Cx->CR2 |= (I2C_CR2_ITERREN);
		I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
		if(I2Cx == I2C1){
			NVIC_IRQ31_I2C1_EV_Enable;
			NVIC_IRQ32_I2C1_ER_Enable;
		}
		else if(I2Cx == I2C2){
			NVIC_IRQ33_I2C2_EV_Enable;
			NVIC_IRQ34_I2C2_ER_Enable;
		}
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}
	//Enable the selected i2c peripheral
	I2Cx->CR1 |= I2C_CR1_PE;



}


/**===================================================
 *  @Fn - MCAL_I2C_DeInit
 *  @brief - reset all I2C registers
 *  @param [in] -I2Cx: which I2C to reset
 *  @retval - none
 *  Note - none
 **/
void MCAL_I2C_DeInit(I2C_typedef* I2Cx){
	if(I2Cx == I2C1){
		NVIC_IRQ31_I2C1_EV_Disable;
		NVIC_IRQ32_I2C1_ER_Disable;
		RCC_I2C1_RESET();

	}
	else if(I2Cx == I2C2){
		NVIC_IRQ33_I2CR_EV_Disable;
		NVIC_IRQ34_I2C2_ER_Disable;
		RCC_I2C2_RESET();
	}
}

/**===================================================
 *  @Fn - MCAL_I2C_GPIO_Set_Pins
 *  @brief - Configure the GPIO pins for I2C
 *  @param [in] -I2Cx: which I2C to set gpio pins for
 *  @retval - none
 *  Note - none
 **/
void MCAL_I2C_GPIO_Set_Pins(I2C_typedef* I2Cx){
	GPIO_PinConfig_t i2cPinCfg;
	if(I2Cx == I2C1){
		//PB6	SCK i2c1
		//PB7	Data i2c1
		i2cPinCfg.GPIO_PinNumber = GPIOx_PIN_6;
		i2cPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		i2cPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOB, &i2cPinCfg);

		i2cPinCfg.GPIO_PinNumber = GPIOx_PIN_7;
		i2cPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		i2cPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOB, &i2cPinCfg);
	}
	else if(I2Cx == I2C2){
		//PB10	SCK i2c2
		//PB11	Data i2c2
		i2cPinCfg.GPIO_PinNumber = GPIOx_PIN_10;
		i2cPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		i2cPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOB, &i2cPinCfg);

		i2cPinCfg.GPIO_PinNumber = GPIOx_PIN_11;
		i2cPinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		i2cPinCfg.GPIO_Output_Speed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOB, &i2cPinCfg);
	}
}

//--------------------------MASTER POLLING MECHANISM----------------------------------------

/**===================================================
 *  @Fn -  MCAL_I2C_Master_TX
 *  @brief - Master Transmitting data
 *  @param [in] - I2Cx: The I2C that is used
 *  @param [in] - devAddr: The address of the Slave that the master is transmitting to
 *  @param [in] - dataOut: The data being transmitted
 *  @param [in] - datalen: The length of the data being transmitted
 *  @param [in] - stop: generate stop bit (if it's supported)
 *  @param [in] - start: Generate start bit (repeated or not)
 *  @retval - none
 *  Note -
 **/
void MCAL_I2C_Master_TX(I2C_typedef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t datalen, Stop_Condition stop, Repeated_Start start){
	int i = 0;
	//todo Support timeout (Configure timer working for a specific duration)
	//1.Set start bit
	I2C_GeneratStart(I2Cx, Enable, start);

	//2.Wait for EV5
	while(!I2C_GetFlagStatus(I2Cx, EV5));

	//3.Send Address
	I2C_SendAddress(I2Cx, devAddr, Transmitter);

	//4.Wait for EV6
	while(!I2C_GetFlagStatus(I2Cx, EV6));

	//5. check (Busy, MSL, TXE, TRA)flag
	while(!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING));

	for(i = 0; i < datalen; i++){
		I2Cx->DR = dataOut[i];
		while(!I2C_GetFlagStatus(I2Cx, EV8));
	}
	//6. send Stop Condition
	if(stop == With_Stop){
		I2C_GenerateStop(I2Cx, Enable);
	}

}

/**===================================================
 *  @Fn -  MCAL_I2C_Master_RX
 *  @brief - Master Receiving data
 *  @param [in] - I2Cx: The I2C that is used
 *  @param [in] - devAddr: The address of the Slave that the master receives data from
 *  @param [in] - dataOut: The data being Received
 *  @param [in] - datalen: The length of the data being Received
 *  @param [in] - stop: generate stop bit (if it's supported)
 *  @param [in] - start: Generate start bit (repeated or not)
 *  @retval - none
 *  Note -
 **/
void MCAL_I2C_Master_RX(I2C_typedef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t datalen, Stop_Condition stop, Repeated_Start start){
	uint8_t index = (I2Cx==I2C1)? I2C1_Index:I2C2_Index;
	int i = 0;
	//1.Set start bit
	I2C_GeneratStart(I2Cx, Enable, start);

	//2.Wait for EV5
	while(!I2C_GetFlagStatus(I2Cx, EV5));

	//3.Send Address
	I2C_SendAddress(I2Cx, devAddr, Receiver);

	//4.Wait for EV6
	while(!I2C_GetFlagStatus(I2Cx, EV6));

	I2C_ACK_Config(I2Cx, Enable);
	if(datalen){
		for(i = datalen; i > 1; i--){
			while(!I2C_GetFlagStatus(I2Cx, EV7));
			*dataOut = I2Cx->DR;
			dataOut++;
		}
		I2C_ACK_Config(I2Cx, Disable);
	}

	if(stop == With_Stop){
		I2C_GenerateStop(I2Cx, Enable);
	}
	if(global_I2C_Config[index].I2C_ACK_Contorl == I2C_ACK_Enable){
		I2C_ACK_Config(I2Cx, Enable);
	}

}


//--------------------------SLAVE INTERRUPT MECHANISM----------------------------------------

/**===================================================
 *  @Fn - MCAL_I2C_SlaveSendData
 *  @brief - Slave Sending data
 *  @param [in] - I2Cx: the I2C being used
 *  @param [in] - data: the data being sent
 *  @retval - none
 *  Note - none
 **/
void MCAL_I2C_SlaveSendData(I2C_typedef* I2Cx, uint8_t data){
	I2Cx->DR = data;
}

/**===================================================
 *  @Fn - MCAL_I2C_SlaveReceiveData
 *  @brief - Slave Sending data
 *  @param [in] - I2Cx: the I2C being used
 *  @retval - (uint8_t)I2Cx->DR : the data being received
 *  Note - none
 **/
uint8_t MCAL_I2C_SlaveReceiveData(I2C_typedef* I2Cx){
	return (uint8_t)I2Cx->DR;
}


//--------------------------IRQ HANDLER----------------------------------------

void I2C1_EV_IRQHandler(void){
	void I2C1_EV_IRQHandler(void)
	{
		//vuint32_t Dummy_Read = 0; // Volatile for compiler optimization

		/* Interrupt handling for both master and slave mode of the device */
		uint32_t Temp_1, Temp_2, Temp_3;

		Temp_1 = (I2C1->CR2 & (I2C_CR2_ITEVTEN));	// Event interrupt enable
		Temp_2 = (I2C1->CR2 & (I2C_CR2_ITBUFEN));	// Buffer interrupt enable
		Temp_3 = (I2C1->SR1 & (I2C_SR1_STOPF));		// Stop detection (slave mode)

		/* Handle Stop Condition Event */
		if(Temp_1 && Temp_3)
		{
			/* STOPF Cleared by software reading the SR1 register followed by a write in the CR1 register,
			 * i have already read SR1 in Temp_3
			 * then next statement i write to CR1
			 */
			I2C1->CR1 |= 0x0000;
			global_I2C_Config[I2C1_Index].P_Slave_Event_CallBack(I2C_EV_Stop);
		}

		/* =============================================================================== */

		/* Handle Received address matched. */
		Temp_3 = (I2C1->SR1 & (I2C_SR1_ADDR));		//ADDR
		if(Temp_1 && Temp_3)
		{
			/* clear ADDR flag
			 * In slave mode, it is recommended to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set.
			 */
			//Dummy_Read  = I2C1->SR1;
			//Dummy_Read  = I2C1->SR2;

			/* Check master mode or slave mode */
			if(I2C1->SR2 & (I2C_SR2_MSL))
			{
				/* Master mode (Using polling mechanism not interrupt) */
			}
			else
			{
				/* Slave mode */
				global_I2C_Config[I2C1_Index].P_Slave_Event_CallBack(I2C_EV_ADDR_Matched);
			}

		}

		/* =============================================================================== */

		/* Handle TxE: Data register empty (Master request data from slave)--> slave_transmitter */
		Temp_3 = (I2C1->SR1 & (I2C_SR1_TXE));		// TXE
		if(Temp_1 && Temp_2 && Temp_3)				// In case TXE=1, ITEVTEN=1, ITBUFEN=1
		{
			/* Check master mode or slave mode */
			if(I2C1->SR2 & (I2C_SR2_MSL))
			{
				/* Master mode (Using polling mechanism not interrupt) */
			}
			else
			{
				/* Slave mode */
				/* Check if slave in transmit mode */
				if(I2C1->SR2 & (I2C_SR2_TRA))		//TRA: Transmitter/receiver: 1: Data bytes transmitted
				{
					global_I2C_Config[I2C1_Index].P_Slave_Event_CallBack(I2C_EV_Data_REQ);
				}
			}
		}

		/* =============================================================================== */

		/* Handle RxNE: Data register not empty (slave receive data)-->slave_Receiver */
		Temp_3 = (I2C1->SR1 & (I2C_SR1_RXNE));		// RXNE
		if(Temp_1 && Temp_2 && Temp_3)				// In case RXNE=1, ITEVTEN=1, ITBUFEN=1
		{
			/* Check master mode or slave mode */
			if(I2C1->SR2 & (I2C_SR2_MSL))
			{
				/* Master mode (Using polling mechanism not interrupt) */
			}
			else
			{
				/* Slave mode */
				if(!(I2C1->SR2 & (I2C_SR2_TRA)))		//TRA: Transmitter/receiver: 0: Data bytes received
				{
					global_I2C_Config[I2C1_Index].P_Slave_Event_CallBack(I2C_EV_Data_RCV);
				}
			}
		}
	}
}
void I2C1_ER_IRQHandler(void){

}

void I2C2_EV_IRQHandler(void){

}
void I2C2_ER_IRQHandler(void){

}


/*
 * =======================================================================================
 * 							Generic APIs
 * =======================================================================================
 */


/**===================================================
 *  @Fn - I2C_GeneratStart
 *  @brief - Generates a start bit
 *  @param [in] - I2Cx: specify which I2C is being used
 *  @param [in] - NewState: whether to enable or disable
 *  @param [in] - start: whether it's a repeated start or not
 *  @retval - none
 *  Note - none
 **/
void I2C_GeneratStart(I2C_typedef* I2Cx,Funcional_State NewState, Repeated_Start start){
	// Check Repeated start or start
	if(start != repeated_start){
		//Check if bus is idle
		while(I2C_GetFlagStatus(I2Cx, I2C_Flag_Busy));
	}
	if(NewState != Disable){
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else{
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}
}


/**===================================================
 *  @Fn -I2C_GetFlagStatus
 *  @brief - toggles a specific pin
 *  @param [in] - I2Cx: specify which I2C is being used
 *  @param [in] - flag: the flag that the function checks its status
 *  @retval - FlagStatus: whether it's set or reset
 *  Note - none
 **/
FlagStatus I2C_GetFlagStatus(I2C_typedef* I2Cx, Status flag){
	//volatile uint32_t dummyRead;
	FlagStatus bitStatus = Reset;
	uint32_t flag1 = 0, flag2 =0, lastevent = 0;
	switch(flag){
	case I2C_Flag_Busy:
	{
		if((I2Cx->SR2) & (I2C_Flag_Busy))
			bitStatus = Set;
		else
			bitStatus = Reset;
	}
	break;
	case EV5:
	{
		if((I2Cx->SR1)& (I2C_SR1_SB))
			bitStatus = Set;
		else
			bitStatus = Reset;
	}
	break;
	case EV6:
	{
		if((I2Cx->SR1) & I2C_SR1_ADDR){
			bitStatus = Set;
		}
		else
			bitStatus = Reset;
	}
	break;
	case MASTER_BYTE_TRANSMITTING:
	{
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2 << 16;
		lastevent = ((flag1 | flag2) & ((uint32_t)0x00FFFFFF));

		if((lastevent & flag) == flag)
			bitStatus = Set;
		else
			bitStatus = Reset;
	}
	break;
	case EV8_1:
	case EV8:
	{
		if(I2Cx->SR1 & I2C_SR1_TXE)
			bitStatus = Set;
		else
			bitStatus = Reset;
	}
	break;
	case EV7:
	{
		if(I2Cx->SR1 & I2C_SR1_RXNE)
			bitStatus = Set;
		else
			bitStatus = Reset;
	}
	break;

	}


	return bitStatus;
}
/**===================================================
 *  @Fn - I2C_SendAddress
 *  @brief - Send the slave address
 *  @param [in] - I2Cx: specify which I2C is being used
 *  @param [in] -  Address: The address of the slave
 *  @param [in] -  direction: The direction of the data (Specify whether the master is transmitter or Receiver)
 *  @retval - none
 *  Note - none
 **/
void I2C_SendAddress(I2C_typedef* I2Cx, uint16_t Address, I2C_Dir direction){
	Address = (Address<<1);
	if(direction != Transmitter){
		// set Address bit0 for read
		Address |= 1<<0;
	}
	else{
		// Reset Address bit0 for write
		Address &= ~(1<<0);
	}
	//send the address
	I2Cx->DR = Address;

}

/**===================================================
 *  @Fn - I2C_GenerateStop
 *  @brief - Generates a stop bit
 *  @param [in] - I2Cx: specify which I2C is being used
 *  @param [in] - NewState: whether to enable or disable
 *  @retval - none
 *  Note - none
 **/
void I2C_GenerateStop(I2C_typedef* I2Cx,Funcional_State NewState){
	if(NewState != Disable)
		I2Cx->CR1 |= I2C_CR1_STOP;
	else
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
}

/**===================================================
 *  @Fn - I2C_ACK_Config
 *  @brief - Configures the Acknowledgment
 *  @param [in] - I2Cx: specify which I2C is being used
 *  @param [in] - NewState: whether to enable or disable
 *  @retval - none
 *  Note - none
 **/
void I2C_ACK_Config(I2C_typedef* I2Cx, Funcional_State NewState){
	if(NewState == Enable)
		I2Cx->CR1 |= I2C_CR1_ACK;
	else
		I2Cx->CR1 &= ~(I2C_CR1_ACK);

}
/**===================================================
 *  @Fn - Slave_States
 *  @brief - Configures the states of the slave
 *  @param [in] - I2Cx: specify which I2C is being used
 *  @param [in] - State: The state of slave
 *  @retval - none
 *  Note - none
 **/
