/*
 * Register_Map.h
 *
 * Created: 3/24/2024 1:21:44 AM
 *  Author: dell
 */ 


#ifndef DEVICE_HEADER_H_
#define DEVICE_HEADER_H_
#include "Util.h"

//---------GPIO-----------
#define  GPIOA_BASE	0x39
#define  GPIOB_BASE	0x36
#define  GPIOC_BASE	0x33
#define  GPIOD_BASE	0x30

typedef struct{
	volatile uint8_t PIN;
	volatile uint8_t DDR;
	volatile uint8_t PORT;

}GPIO_Typdef;

#define GPIOA	((GPIO_Typdef *)GPIOA_BASE)
#define GPIOB	((GPIO_Typdef *)GPIOB_BASE)
#define GPIOC	((GPIO_Typdef *)GPIOC_BASE)
#define GPIOD	((GPIO_Typdef *)GPIOD_BASE)

//---------------------------

#define SREG	*(volatile unsigned char*)(0x5F)
#define SPH		*(volatile unsigned char*)(0x5E)
#define SPL		*(volatile unsigned char*)(0x5D)
#define OCR0	*(volatile unsigned char*)(0x5C)
#define GICR	*(volatile unsigned char*)(0x5B)
#define GIFR	*(volatile unsigned char*)(0x5A)
#define TIMSK	*(volatile unsigned char*)(0x59)
#define TIFR	*(volatile unsigned char*)(0x58)
#define SPMCR	*(volatile unsigned char*)(0x57)
#define TWCR	*(volatile unsigned char*)(0x56)
#define MCUCR	*(volatile unsigned char*)(0x55)
#define MCUCSR	*(volatile unsigned char*)(0x54)
#define TCCR0	*(volatile unsigned char*)(0x53)
#define TCNT0	*(volatile unsigned char*)(0x52)
#define OSCCAL	*(volatile unsigned char*)(0x51)
#define OCDR	*(volatile unsigned char*)(0x51)
#define SFIOR	*(volatile unsigned char*)(0x50)
#define TCCR1A	*(volatile unsigned char*)(0x4F)
#define TCCR1B	*(volatile unsigned char*)(0x4E)
#define TCNT1H	*(volatile unsigned char*)(0x4D)
#define TCNT1L	*(volatile unsigned char*)(0x4C)
#define OCR1AH	*(volatile unsigned char*)(0x4B)
#define OCR1AL	*(volatile unsigned char*)(0x4A)
#define OCR1BH	*(volatile unsigned char*)(0x49)
#define OCR1BL	*(volatile unsigned char*)(0x48)
#define ICR1H	*(volatile unsigned char*)(0x47)
#define ICR1L	*(volatile unsigned char*)(0x46)
#define TCCR2	*(volatile unsigned char*)(0x45)
#define TCNT2	*(volatile unsigned char*)(0x44)
#define OCR2	*(volatile unsigned char*)(0x43)
#define ASSR	*(volatile unsigned char*)(0x42)
#define WDTCR	*(volatile unsigned char*)(0x41)
#define UBRRH	*(volatile unsigned char*)(0x40)
#define UCSRC	*(volatile unsigned char*)(0x40)
#define EEARH	*(volatile unsigned char*)(0x3F)
#define EEARL	*(volatile unsigned char*)(0x3E)
#define EEDR	*(volatile unsigned char*)(0x3D)
#define EECR	*(volatile unsigned char*)(0x3C)

#define PORTA	(*(volatile unsigned char*)0x3B)
#define DDRA	(*(volatile unsigned char*)0x3A)
#define PINA	(*(volatile unsigned char*)0x39)
#define PORTB	(*(volatile unsigned char*)0x38)
#define DDRB	(*(volatile unsigned char*)0x37)
#define PINB	(*(volatile unsigned char*)0x36)
#define PORTC	(*(volatile unsigned char*)0x35)
#define DDRC	(*(volatile unsigned char*)0x34)
#define PINC	(*(volatile unsigned char*)0x33)
#define PORTD	(*(volatile unsigned char*)0x32)
#define DDRD	(*(volatile unsigned char*)0x31)
#define PIND	(*(volatile unsigned char*)0x30)

#define SPDR	*(volatile unsigned char*)(0x2F)
#define SPSR	*(volatile unsigned char*)(0x2E)
#define SPCR	*(volatile unsigned char*)(0x2D)
#define UDR		*(volatile unsigned char*)(0x2C)
#define UCSRA	*(volatile unsigned char*)(0x2B)
#define UCSRB	*(volatile unsigned char*)(0x2A)
#define UBRRL	*(volatile unsigned char*)(0x29)
#define ACSR	*(volatile unsigned char*)(0x28)
#define ADMUX	*(volatile unsigned char*)(0x27)
#define ADCSRA	*(volatile unsigned char*)(0x26)
#define ADCH	*(volatile unsigned char*)(0x25)
#define ADCL	*(volatile unsigned char*)(0x24)
#define TWDR	*(volatile unsigned char*)(0x23)
#define TWAR	*(volatile unsigned char*)(0x22)
#define TWSR	*(volatile unsigned char*)(0x21)
#define TWBR	*(volatile unsigned char*)(0x20)




#endif /* DEVICE_HEADER_H_ */