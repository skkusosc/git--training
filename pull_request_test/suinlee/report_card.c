#include<stdio.h>

int main()
{
	int kor, eng, math;
	int sum = 0;

	math = 87;
	eng = 100;
	kor = 90;
	sum = 87 + 100 + 90;

	printf("This program print report card.\n");

	printf("Korean : %d\n", kor);
	printf("English : %d\n", eng);
	printf("Math : %d\n", math);
	printf("Sum : %d\n", sum);
	printf("Mean : %d\n", sum/3);
	return 0;
}
