#ifndef _FIXEDPOINT_H_
#define _FIXEDPOINT_H_

#include <stdint.h>

typedef int32_t fp32;
typedef int64_t fp64;

#define FIXQ				(24u)
#define double_to_fp32(x)	((fp32)((1u<<FIXQ)*((double)x)))
#define fp32_to_double(x)	(((double)(x))/(1u<<FIXQ))
// �l�����Z
// �I�[�o�[�t���[�ɒ���
// ���ɏ��Z�̏���
#define fp32_add(x,y)		((x)+(y))	
#define fp32_sub(x,y)		((x)-(y))
#define fp32_mul(x,y)		((fp32)(((fp64)(x)*(fp64)(y))>>FIXQ))
#define fp32_div(x,y)		((fp32)(((fp64)(x)<<FIXQ)/(y)))

#endif //_FIXEDPOINT_H_