// FixedPointRandTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fixedpoint.h"

#define MY_RAND_MAX (0xFFFF)

static uint32_t next = 1;

inline uint32_t my_rand(void)
{
	next = next * 1103515245 + 12345;
	return (uint32_t)(next >> 16) & MY_RAND_MAX;
}

// -1.0 .. 1.0‚Ì—”
inline fp32 generateNoise()
{
	int32_t r, v;
	fp32 fv;

	r = my_rand();
	v = (r & 0x8000) ? (0xffff0000 | (r << 1)) : (r << 1);
	fv = (fp32)v;

	return fv;
}

int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < 0xffff; i++) {
		//printf("%d\n", my_rand());
		printf("%f\n", fp32_to_double(generateNoise()));
	}
	return 0;
}

