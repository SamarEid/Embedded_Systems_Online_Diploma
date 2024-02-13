/*
 * CA.c
 *
 *  Created on: Feb 13, 2024
 *      Author: dell
 */
#include "CA.h"
// variables
int CA_speed = 0 , CA_distance = 0, CA_threshold = 50;

// state pointer to function
void (*CA_state ) ();
void US_Set_ditance (int d){
	CA_distance = d;
	(CA_distance <= CA_threshold )? (CA_state = STATE(CA_Waiting)): (CA_state = STATE(CA_Driving));
	printf("US---------distance = %d --------> CA \n", CA_distance);
}

STATE_define(CA_Waiting){
	// state_name
	CA_state_id = CA_Waiting;
	printf("CA_Waiting State: distance = %d		Speed = %d \n", CA_distance, CA_speed);

	// state_action
	CA_speed = 0;
	DC_motor(CA_speed);
}
STATE_define(CA_Driving){
	// state name
	CA_state_id = CA_Driving;
	printf("CA_Driving State: distance = %d		Speed = %d \n", CA_distance, CA_speed);

	// state_action
	CA_speed = 30;
	DC_motor(CA_speed);

}

