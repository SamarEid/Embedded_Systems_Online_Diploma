/*
 * Alarm.c
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */

#include "Alarm.h"

void (*Alarm_State)(void);

void Alarm_init(){
	GPIO_INITIALIZATION();
	//Alarm_State = STATE(Wait);
}
STATE_define(Wait){
	Alarm_State_id = Wait;

	Alarm_State = STATE(Wait);
}
STATE_define(OFF){
	Alarm_State_id = OFF;
	Set_Alarm_actuator(1);
	Alarm_State = STATE(Wait);
}
STATE_define(ON){
	Alarm_State_id = ON;
	Set_Alarm_actuator(0);
	Alarm_State = STATE(Wait);
}


void Start_Alarm(void){
	Alarm_State = STATE(ON);
	Alarm_State();
}

void Stop_Alarm(void){
	Alarm_State = STATE(OFF);
	Alarm_State();
}

