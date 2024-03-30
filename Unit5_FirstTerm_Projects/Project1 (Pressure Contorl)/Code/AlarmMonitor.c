/*
 * AlarmMonitor.c
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */

#include "AlarmMonitor.h"

void (*Alarm_Monitor_State)(void);

STATE_define(AlarmOFF){
	Alarm_Monitor_State_id = AlarmOFF;
	// state action
	Stop_Alarm();
	// state transition
	Alarm_Monitor_State = STATE(AlarmOFF);
}
STATE_define(AlarmON){
	Alarm_Monitor_State_id = AlarmON;
	// state action
	Start_Alarm();
	Delay(60000);
	Stop_Alarm();
	// state transiotion
	Alarm_Monitor_State = STATE(AlarmWaiting);
}
STATE_define(AlarmWaiting){
	Alarm_Monitor_State_id = AlarmWaiting;
	Alarm_Monitor_State = STATE(AlarmOFF);
}
void High_Pressure_Detection(void){
	Alarm_Monitor_State = STATE(AlarmON);
}
