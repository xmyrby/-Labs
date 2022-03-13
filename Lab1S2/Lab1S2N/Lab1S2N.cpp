#include <conio.h>
#include <stdio.h>
#include <iostream>

int main()
{
	system("chcp 1251 > null");

	double m[2][3], dt[2], x[2], d, * det;
	printf("Система:\na1 * b2 + b1 * x2 = c1\na2 * x2 + b2 * x2 = c2\n\n");

	for (int i = 0; i < 2; i++)
	{
		double* a, * b, * c;
		printf("Введите a b c для %d системы:\n", i + 1);
		a = &m[i][0];
		b = &m[i][1];
		c = &m[i][2];
		scanf_s("%lf %lf %lf", a, b, c);
	}

	double* a1 = &m[0][0], * a2 = &m[1][0], * b1 = &m[0][1], * b2 = &m[1][1], * c1 = &m[0][2], * c2 = &m[1][2], * x1 = &x[0], * x2 = &x[1];

	d = *a1 * *b2 - *a2 * *b1;

	printf("\nОпределитель: %5.3lf\n", d);

	if (d == 0)
	{
		printf("\nЧастный случай");
		exit(1);
	}
	else
	{
		det = &dt[0];
		*det = *c1 * *b2 - *c2 * *b1;
		*x1 = *det / d;
		printf("\nx1 = %5.3lf/%5.3lf = %5.3lf\n", *det, d, *x1);

		det = &dt[1];
		*det = *a1 * *c2 - *a2 * *c1;
		*x2 = *det / d;
		printf("\nx2 = %5.3lf/%5.3lf = %5.3lf", *det, d, *x2);
	}
}