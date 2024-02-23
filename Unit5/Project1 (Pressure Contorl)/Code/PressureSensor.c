/*
 * PressureSensor.c
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */

#include "PressureSensor.h"

int Pval = 0;

void (*PSensor_states)(void);

void PS_init(void){
	GPIO_INITIALIZATION();
	//PSensor_states = STATE(Reading);
}

STATE_define(Reading){
	// state
	PSensor_States_id = Reading;
	// state action
	Pval = getPressureVal();
	Set_Pressure_Val(Pval);
	Delay(6000);
	// state transition
	PSensor_states = STATE(Waiting);

}
STATE_define(Waiting){
	// state
	PSensor_States_id = Waiting;
	// state transition
	PSensor_states = STATE(Reading);
}
