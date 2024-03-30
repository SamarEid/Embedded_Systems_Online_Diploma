/*
 * main.c
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */
#include "driver.h"
#include "PressureSensor.h"
#include "Alarm.h"
#include "AlarmMonitor.h"
#include "HighPressureDetection.h"

void Init(void);

int main(){
	Init();
	while (1){
		PSensor_states();
		High_pressure();
		Alarm_Monitor_State();
		Alarm_State();
	}
}

void Init(void){
	PS_init();
	Alarm_init();

	PSensor_states = STATE(Reading);
	High_pressure = STATE(PressureDetection);
	Alarm_Monitor_State = STATE(AlarmOFF);
	Alarm_State = STATE(Wait);
}

