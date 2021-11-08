#include<iostream>
// Дано натуральное число n и вещественное число x.Вычислить 1 + x / 2 + x ^ 2 / 4 + ⋯ + x ^ n / 2n

int main()
{
	//Объявление переменных
	int n;
	double x, s = 1, lpow = 1;

	//Ввод
	do
	{
		system("cls");
		printf("Print n = ");
		scanf_s("%d", &n);
	} while (n <= 0);
	printf("Print x = ");
	scanf_s("%lf", &x);

	//Вычисление
	for (int i = 0; i < n; i++)
	{
		lpow *= x;
		s += lpow / (2 * (i + 1));
	}

	//Вывод
	printf("%.3lf", s);

	return 0;
}