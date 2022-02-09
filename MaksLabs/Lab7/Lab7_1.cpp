#include <iostream>
//Дано целое число n. Получить наименьшее число вида 2r, превосходящее n(r - натуральное).
int main()
{
	int n, r = 0, power = 1;
	system("chcp 1251 > nul");

	printf("Введите n  = ");
	scanf_s("%d", &n);

	while (power <= n)
	{
		r++;
		power *= 2;
	}

	printf("r = %d",r);

	return 0;
}