/*
 * HighPressureDetection.c
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */
#include "HighPressureDetection.h"

int Pressureval = 0;
int threshold = 20;

void (*High_pressure)(void);

void Set_Pressure_Val(int Pval){
	Pressureval = Pval;
}

STATE_define(PressureDetection){
	High_Pressure_State_id = PressureDetection;

	if(Pressureval > threshold){
		High_Pressure_Detection();
	}

	High_pressure = STATE(PressureDetection);
}


