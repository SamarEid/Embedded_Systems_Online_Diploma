/*
 * US.c
 *
 *  Created on: Feb 13, 2024
 *      Author: dell
 */
#include "US.h"
// variables
int  US_distance = 0;

// state pointer to function
void (*US_state ) ();
int US_Get_distance_random(int l, int r, int count);
void US_init(){
	//init US Driver
	printf("US_init \n");
}

STATE_define(US_busy){
	// state_name
	US_state_id = US_busy;
	// state action
	US_distance =US_Get_distance_random(45, 55, 1);
	printf("US_busy State: distance = %d	\n", US_distance);
	US_Set_ditance(US_distance);
	US_state = STATE(US_busy);

}

int US_Get_distance_random(int l, int r, int count){
	int i;
		for(i=0; i<count; ++i){
			int rand_num = (rand() % (r - l + 1)) + l;
			return rand_num;
		}
}
