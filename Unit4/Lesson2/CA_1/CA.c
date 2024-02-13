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
int US_Get_distance_random(int l, int r, int count);

STATE_define(CA_Waiting){
	// state_name
	CA_state_id = CA_Waiting;
	// state_action
	CA_speed = 0;
	// event_check
	// us_get_distance(CA_distance)
	CA_distance =US_Get_distance_random(45, 55, 1);
	(CA_distance <= CA_threshold )? (CA_state = STATE(CA_Waiting)): (CA_state = STATE(CA_Driving));
	printf("CA_Waiting State: distance = %d		Speed = %d \n", CA_distance, CA_speed);

}
STATE_define(CA_Driving){
	// state name
	CA_state_id = CA_Driving;
	// state_action
	CA_speed = 30;
	// event_check
	// us_get_distance(CA_distance)
	CA_distance =US_Get_distance_random(45, 55, 1);
	(CA_distance <= CA_threshold )? (CA_state = STATE(CA_Waiting)): (CA_state = STATE(CA_Driving));
	printf("CA_Waiting State: distance = %d		Speed = %d \n", CA_distance, CA_speed);

}
int US_Get_distance_random(int l, int r, int count){
	int i;
		for(i=0; i<count; ++i){
			int rand_num = (rand() % (r - l + 1)) + l;
			return rand_num;
		}
}
