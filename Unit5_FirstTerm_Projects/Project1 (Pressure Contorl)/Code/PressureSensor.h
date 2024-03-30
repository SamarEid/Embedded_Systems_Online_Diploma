/*
 * PressureSensor.h
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */

#ifndef PRESSURESENSOR_H_
#define PRESSURESENSOR_H_

#include <stdio.h>
#include <stdlib.h>
#include "States.h"

enum {
	Reading,
	Waiting
}PSensor_States_id;


extern void (*PSensor_states) (void);

void PS_init(void);
STATE_define(Reading);
STATE_define(Waiting);

#endif /* PRESSURESENSOR_H_ */
