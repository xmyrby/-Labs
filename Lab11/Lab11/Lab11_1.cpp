#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
//(-1)^(i+1)1/cos(x)
int main()
{
	int n = 0, polar = 1;
	double x = 0, s = 0;

	do
	{
		system("cls");
		printf("Print n: ");
		scanf_s("%d", &n);
	} while (n < 1);

	printf("Print x: ");
	scanf_s("%lf", &x);

	for (int i = 1; i <= n; i++)
	{
		double number = (-1) * polar * (1 / cos((x * 180 / M_PI)));
		s += number;
		polar *= -1;
		printf("Number %d = %.3lf\n", i, number);
	}
	printf("S=%.3lf", s);

	return 1;
}
