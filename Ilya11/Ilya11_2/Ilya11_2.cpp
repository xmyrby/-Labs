#include <stdio.h>
#include <math.h>
//(-1)^i*(|x-9|^i/(i+4)!)
int main()
{
	int i = 0;
	double s = 0, x, e, number, fact = 24, lastx, polar = -1;
	printf("Print x: ");
	scanf_s("%lf", &x);
	printf("Print e: ");
	scanf_s("%lf", &e);
	lastx = x-9;

	do
	{
		i++;
		fact *= (i+4);
		number = polar * (lastx / fact);
		printf("Number %d = %.3lf\n", i, number);
		s += number;
		lastx *= x-9;
		polar *= -1;
	} while (fabs(number) > e);
	printf("%lf", s);

	return 1;
}
