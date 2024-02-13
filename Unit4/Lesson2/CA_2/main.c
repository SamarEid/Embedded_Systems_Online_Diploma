/*
 * main.c
 *
 *  Created on: Feb 13, 2024
 *      Author: dell
 */


#include "CA.h"
#include "US.h"
#include "DC.h"

void setup(){
	//init all drivers
	// init IRQ....
	// init HAL US_Driver DC_Driver
	//init Block
	US_init();
	DC_init();
	//set State pointers
	CA_state = STATE(CA_Waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);
}
void main(){

	setup();

	volatile int d;
	while(1){
		// call state for each block
		US_state();
		CA_state();
		DC_state();
		for (d = 0; d <= 1000; d++);
	}
}
