/*
 * Util.h
 *
 * Created: 3/11/2024 1:14:58 AM
 *  Author: dell
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#define SetBit(reg,bit) (reg |= (1<<bit))
#define ClrBit(reg,bit) (reg &= ~(1<<bit))
#define ReadBit(reg,bit) ((reg>>bit)&1)
#define ToggleBit(reg,bit) (reg ^= (1<<bit))



#endif /* UTIL_H_ */