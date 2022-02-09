#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
//(-1)^i*(sin(x^i)/i!)
int main()
{
	int i = 0;
	double s = 0, x, e, number, fact = 1, lastx, polar = -1;
	printf("Print x: ");
	scanf_s("%lf", &x);
	printf("Print e: ");
	scanf_s("%lf", &e);
	lastx = x;

	do
	{
		i++;
		fact *= i;
		number = polar * (sin(lastx * 180 / M_PI) / fact);
		printf("Number %d = %.3lf\n", i, number);
		s += number;
		lastx *= x;
		polar *= -1;
	} while (fabs(number) > e);
	printf("%lf", s);

	return 1;
}
