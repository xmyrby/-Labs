#include <iostream>
//(-1)^(2i+1)1/x+i
int main()
{
	//ќбъ€вление переменных
	int n = 0, polar = -1;
	double x = 0, s = 0;

	//¬вод количества элементов
	do
	{
		system("cls");
		printf("Print n: ");
		scanf_s("%d", &n);
	} while (n < 1);

	//¬вод x
	printf("Print x: ");
	scanf_s("%lf", &x);

	//—уммирование
	for (int i = 1; i <= n; i++)
	{
		double number = polar * (1 / (x + i));
		s += number;
		polar *= -1;
		printf("Number %d = %.3lf\n", i, number);
	}
	printf("S=%.3lf", s);

	return 1;
}
