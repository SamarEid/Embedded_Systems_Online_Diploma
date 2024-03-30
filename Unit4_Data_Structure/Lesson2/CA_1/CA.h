/*
 * CA.h
 *
 *  Created on: Feb 13, 2024
 *      Author: dell
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"

// Define States
enum {
	CA_Waiting,
	CA_Driving
}CA_state_id;
// declare states functions CA
STATE_define(CA_Waiting);
STATE_define(CA_Driving);

// state pointer to function
extern void (*CA_state ) ();


#endif /* CA_H_ */
