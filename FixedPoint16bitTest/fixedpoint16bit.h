#ifndef _FIXEDPOINT16BIT_H_
#define _FIXEDPOINT16BIT_H_

#include <stdint.h>

typedef int16_t fp16;
typedef int32_t fp32;

#define FIXQ				(14u)
#define double_to_fp16(x)	((fp16)((1u<<FIXQ)*((double)x)))
#define fp16_to_double(x)	(((double)(x))/(1u<<FIXQ))
#define int_to_fp16(x)		((fp16)(((int16_t)(x))<<FIXQ))
#define fp16_to_int(x)		(((int16_t)(x))>>FIXQ)
// Žl‘¥‰‰ŽZ
// œŽZ‚ÍˆÀ‘S‚Ì‚½‚ßŽg—p‚µ‚È‚¢
#define fp16_add(x,y)		((x)+(y))	
#define fp16_sub(x,y)		((x)-(y))
#define fp16_mul(x,y)		((fp16)(((fp32)(x)*(fp32)(y))>>FIXQ))
//#define fp16_div(x,y)		((fp16)(((fp32)(x)<<FIXQ)/((fp32)(y))))

#endif //_FIXEDPOINT16BIT_H_