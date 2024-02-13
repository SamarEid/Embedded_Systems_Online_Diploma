/*
 * state.h
 *
 *  Created on: Feb 13, 2024
 *      Author: dell
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"

// Automatic State function generated
#define STATE_define(_statFun_) void ST_##_statFun_()
#define STATE(_statFun_) ST_##_statFun_

// States Connection
void US_Set_ditance (int d);
void DC_motor(int s);

#endif /* STATE_H_ */
