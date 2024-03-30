/*
 * States.h
 *
 *  Created on: Feb 23, 2024
 *      Author: dell
 */

#ifndef STATES_H_
#define STATES_H_
#include "driver.h"

// Automatic State function generated
#define STATE_define(_statFun_) void ST_##_statFun_()
#define STATE(_statFun_) ST_##_statFun_

#define HIGH_PRESSURE ((int)1)
#define NORMAL_PRESSURE ((int)0)

// States Connection
void Set_Pressure_Val(int Pval);
void High_Pressure_Detection(void);
void Start_Alarm(void);
void Stop_Alarm(void);

#endif /* STATES_H_ */
