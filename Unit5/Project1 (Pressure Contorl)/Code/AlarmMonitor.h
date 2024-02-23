/*
 * AlarmMonitor.h
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */

#ifndef ALARMMONITOR_H_
#define ALARMMONITOR_H_

#include "States.h"

enum{
	AlarmOFF,
	AlarmON,
	AlarmWaiting
}Alarm_Monitor_State_id;

extern void (*Alarm_Monitor_State)(void);


STATE_define(AlarmOFF);
STATE_define(AlarmON);
STATE_define(AlarmWaiting);


#endif /* ALARMMONITOR_H_ */
