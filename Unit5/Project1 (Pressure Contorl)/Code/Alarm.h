/*
 * Alarm.h
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */

#ifndef ALARM_H_
#define ALARM_H_
#include "States.h"

enum{
	Wait,
	OFF,
	ON
}Alarm_State_id;
extern void (*Alarm_State)(void);

void Alarm_init();
STATE_define(Wait);
STATE_define(OFF);
STATE_define(ON);


#endif /* ALARM_H_ */
