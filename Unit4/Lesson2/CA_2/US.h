/*
 * US.h
 *
 *  Created on: Feb 13, 2024
 *      Author: dell
 */

#ifndef US_H_
#define US_H_

#include "state.h"

// Define States
enum {
	US_busy
}US_state_id;
// declare states functions CA
STATE_define(US_busy);


void US_init();
// state pointer to function
extern void (*US_state ) ();


#endif /* US_H_ */
