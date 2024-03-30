/*
 * DC.c
 *
 *  Created on: Feb 13, 2024
 *      Author: dell
 */
#include "DC.h"
// variables
int DC_speed = 0;

// state pointer to function
void (*DC_state ) ();
void DC_init(){
	//init PWM
	printf("DC_init \n");
}
void DC_motor(int s){
	DC_speed = s;
	DC_state = STATE(DC_busy);
	printf("CA --------- Speed = %d --------> DC \n", DC_speed);

}

STATE_define(DC_idle){
	// state_name
	DC_state_id = DC_idle;
	// state_action
	//call pwm to make speed = DC_speed

	printf("DC_idle State: Speed = %d \n", DC_speed);

}
STATE_define(DC_busy){
	// state name
	DC_state_id = DC_busy;
	// state_action
	//call pwm to make speed = DC_speed
	DC_state = STATE(DC_idle);
	printf("DC_busy State: Speed = %d \n", DC_speed);

}

