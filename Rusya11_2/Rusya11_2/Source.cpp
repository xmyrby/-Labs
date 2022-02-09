#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
//(-1)^i*(cos(2x^i)/(i+2)!)
int main()
{
	int i = 1, fact = 2;
	double s = 0, x, e, number, lastx, polar = -1;
	printf("Print x: ");
	scanf_s("%lf", &x);
	printf("Print e: ");
	scanf_s("%lf", &e);
	lastx = x;

	do
	{
		fact *= (i + 2);
		number = polar * (cos(2 * lastx * 180 / M_PI) / fact);
		i++;
		printf("Number %d = %.3lf\n", i, number);
		s += number;
		lastx *= x;
		polar *= -1;

	} while (fabs(number) > e);
	printf("%lf", s);

	return 1;
}
