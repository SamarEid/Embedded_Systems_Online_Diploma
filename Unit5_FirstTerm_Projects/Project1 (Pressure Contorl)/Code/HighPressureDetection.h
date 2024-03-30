/*
 * HighPressureDetection.h
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */

#ifndef HIGHPRESSUREDETECTION_H_
#define HIGHPRESSUREDETECTION_H_

#include "States.h"

enum {
	PressureDetection
}High_Pressure_State_id;

extern void (*High_pressure)(void);

STATE_define(PressureDetection);


#endif /* HIGHPRESSUREDETECTION_H_ */
