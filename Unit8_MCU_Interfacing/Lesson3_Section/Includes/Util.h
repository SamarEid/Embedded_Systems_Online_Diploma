/*
 * Util.h
 *
 * Created: 3/24/2024 1:21:59 AM
 *  Author: dell
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#include "stdio.h"
#include "stdint.h"



#define Set_Bit(Reg,bit)		Reg |= (1<<bit)
#define Clr_Bit(Reg,bit)		Reg &= ~(1<<bit)
#define Toggle_Bit(Reg,bit)		Reg ^= (1<<bit)
#define Read_Bit(Reg,bit)		(Reg>>bit)&1



#endif /* UTIL_H_ */