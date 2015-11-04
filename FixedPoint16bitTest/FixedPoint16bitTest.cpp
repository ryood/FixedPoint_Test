// FixedPoint16bitTest.cpp : Defines the entry point for the console application.
//
// 2015.10.31 Q2.14でテスト
// 2015.10.11 Q16.16でテスト
// 2015.10.08 Q8.24でテスト

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include "fixedpoint16bit.h"

#define TEST_INT	0
#define CALC_DIV	0

#define CALC_REPEAT	0xffff	// Excelの最大行
#define	FP16_MAX	(1.0f)
#define INT_MAX		1
#define INT_MIN		-1

double dbl_rand()
{
	double dr = (double)rand() / RAND_MAX;
	return (dr - 0.5) * FP16_MAX;
}

void calc(double dx, double dy)
{
	fp16 fpx = double_to_fp16(dx);
	fp16 fpy = double_to_fp16(dy);

	double x_v = fp16_to_double(fpx);
	double y_v = fp16_to_double(fpy);
	double add_v = fp16_to_double(fp16_add(fpx, fpy));
	double sub_v = fp16_to_double(fp16_sub(fpx, fpy));
	double mul_v = fp16_to_double(fp16_mul(fpx, fpy));
#if CALC_DIV
	// 0除算回避
	if (fpy == 0) {
		printf("fpy: %d !!!!!!!!!\n", (int16_t)fpy);
		return;
	}
	double div_v = fp16_to_double(fp16_div(fpx, fpy));
#endif

	printf("x\t%lf\t%lf\t%lf\n", dx, x_v, dx - x_v);
	printf("y\t%lf\t%lf\t%lf\n", dy, y_v, dy - y_v);
	printf("x+y\t%lf\t%lf\t%lf\n", dx + dy, add_v, (dx + dy) - add_v);
	printf("x-y\t%lf\t%lf\t%lf\n", dx - dy, sub_v, (dx - dy) - sub_v);
	printf("x*y\t%lf\t%lf\t%lf\n", dx * dy, mul_v, (dx * dy) - mul_v);
#if CALC_DIV
	printf("x/y\t%lf\t%lf\t%lf\n", dx / dy, div_v, (dx / dy) - div_v);
#endif
}

int _tmain(int argc, _TCHAR* argv[])
{
#if TEST_INT
	// 整数のテスト
	printf("fp16_to_double\tfp16_to_int\tinner\n");
	for (int i = INT_MIN; i <= INT_MAX; i++) {
		fp16 fv = int_to_fp16(i);
		printf("%d\t%lf\t%d\t%d\n", i, fp16_to_double(fv), fp16_to_int(fv), fv);
	}
#else
	// 浮動小数点のテスト
	printf("expr\tdouble\tfp32\terr\n");
	calc(INT_MAX, INT_MIN);

	for (int i = 0; i < CALC_REPEAT; i++) {
		double dx = dbl_rand();
		double dy = dbl_rand();
		// 除算エラー回避
		if (dy == 0.0f)
			continue;
		calc(dx, dy);
	}
#endif
	return 0;
}

