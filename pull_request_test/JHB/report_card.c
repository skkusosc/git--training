#include<stdio.h>

int main()
{
	int kor, eng, math;
	int sum = 0;
	int average;

	math = 80;
	eng = 100;
	kor = 90;
	sum = 80 + 100 + 90;
	average = sum/3;
	printf("This program print report card.\n");

	printf("Korean : %d\n", kor);
	printf("English : %d\n", eng);
	printf("Math : %d\n", math);
	printf("Sum : %d\n", sum);
	printf("Mean : %d\n", average);
	return 0;
}
