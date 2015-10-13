// FixedPointTest.cpp : Defines the entry point for the console application.
//
// 2015.10.11 Q16.16でテスト
// 2015.10.08 Q8.24でテスト

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include "fixedpoint.h"

#define TEST_INT	0
#define CALC_DIV	0

#define CALC_REPEAT	0xffff	// Excelの最大行
#define	FP32_MAX	(128.0f)
#define INT_MAX		127
#define INT_MIN		-128

double dbl_rand()
{
	double dr = (double)rand() / RAND_MAX;
	return (dr - 0.5) * FP32_MAX;
}

void calc(double dx, double dy)
{
	fp32 fpx = double_to_fp32(dx);
	fp32 fpy = double_to_fp32(dy);

	double x_v = fp32_to_double(fpx);
	double y_v = fp32_to_double(fpy);
	double add_v = fp32_to_double(fp32_add(fpx, fpy));
	double sub_v = fp32_to_double(fp32_sub(fpx, fpy));
	double mul_v = fp32_to_double(fp32_mul(fpx, fpy));
#if CALC_DIV
	double div_v = fp32_to_double(fp32_div(fpx, fpy));
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
	printf("fp32_to_double\tfp32_to_int\tinner\n");
	for (int i =INT_MIN; i < INT_MAX; i++) {
		fp32 fv = int_to_fp32(i);
		printf("%d\t%lf\t%d\t%d\n", i, fp32_to_double(fv), fp32_to_int(fv), fv);
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

