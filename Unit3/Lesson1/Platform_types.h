#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#define CPU_TYPE    CPU_TYPE_32
#define CPU_BIT_ORDER   MSB_FIRST
#define CPU_BYTE_ORDER  HIGH_BYTE_FIRST

#ifndef FALSE
#define FALSE   (boolean)false
#endif

#ifndef TRUE
#define TRUE    (boolean)true
#endif


typedef unsigned char boolean;
typedef char char_t;
typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef signed long sint32;
typedef unsigned long uint32;
typedef signed long long sint64;
typedef unsigned long long uint64;
typedef float float32;
typedef double float64;


typedef volatile signed char vint8_t;
typedef volatile unsigned char vuint8_t;
typedef volatile signed short vint16_t;
typedef volatile unsigned short vuint16_t;
typedef volatile signed long vint32_t;
typedef volatile unsigned long vuint32_t;
typedef volatile signed long long vint64_t;
typedef volatile unsigned long long vuint64_t;

#endif