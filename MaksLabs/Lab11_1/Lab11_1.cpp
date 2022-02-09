#include <iostream>
//(-1)^(2*i)*((2)/(x-i))
int main()
{
	int n = 0;
	double x = 0, s = 0;
	system("chcp 1251 > nul");

	do
	{
		system("cls");
		printf("¬ведите n = ");
		scanf_s("%d", &n);
	} while (n <= 1);

	printf("¬ведите x = ");
	scanf_s("%lf", &x);

	for (int i = 1; i <= n; i++)
	{
		s += 2.0 / (x - i);
	}

	printf("«начение выражени€ = %.3lf", s);

	return 0;
}