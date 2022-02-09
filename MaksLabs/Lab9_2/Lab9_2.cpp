#include <iostream>
//2𝑥 − 1/3𝑥, 𝑥 < −1; 3 cos(2x) , −1 ≤ 𝑥 ≤ 10; 3, 𝑥 > 10;
int main()
{
	double f, a = 0, b = 0, c = 0;
	system("chcp 1251 > nul");

	do
	{
		system("cls");
		printf("Введите A = ");
		scanf_s("%lf", &a);
		printf("Введите B = ");
		scanf_s("%lf", &b);
		printf("Введите C = ");
		scanf_s("%lf", &c);
	} while (a > b || c <= 0);

	for (; a <= b; a += c)
	{
		if (a < -1)
		{
			f = 2.0 * a - 1.0 / (3.0 * a);
		}
		else if (a <= 10)
		{
			f = 3.0 * cos(2.0 * a);
		}
		else
		{
			f = 3;
		}
		printf("f(%.3lf) = %.3lf\n", a, f);
	}

	return 0;
}