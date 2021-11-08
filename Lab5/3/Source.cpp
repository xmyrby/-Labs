#include <stdio.h>
#include <math.h>
//(4x + 10, x ≤ - 10); (1, -10 < x ≤ 10); (2x ^ 2, x > 10);
int main()
{
	double x;
	//Ввод x
	scanf_s("%lf", &x);

	//Проверяем
	if (x <= -10)
	{
		printf("f(x) = %.3lf", 4 * x + 10);
	}
	if (x > -10 && x <= 10)
	{
		printf("f(x) = 1");
	}
	if (x > 10)
	{
		printf("f(x) = %.3lf", 2 * x * x);
	}

	return 0;
}