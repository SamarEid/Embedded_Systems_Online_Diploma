/*
 * main.c
 *
 *  Created on: Feb 13, 2024
 *      Author: dell
 */


#include "CA.h"

void setup(){
	//init all drivers
	// init IRQ....
	// init HAL US_Driver DC_Driver
	//init Block
	//set State pointers
	CA_state = STATE(CA_Waiting);
}
void main(){

	setup();

	volatile int d;
	while(1){
		// call state for each block
		CA_state();
		for (d = 0; d <= 1000; d++);
	}
}
