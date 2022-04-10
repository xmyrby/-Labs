#include <iostream>
#include <malloc.h>

void Inter(int& a, int& b)
{
	do
	{
		system("cls");
		printf("Введите начало интервала: ");
		scanf_s("%d", &a);
		printf("Введите конец интервала: ");
		scanf_s("%d", &b);
	} while (a > b || a < 0 || b < 0);
}

int main()
{
	system("chcp 1251 > null");

	int* a;
	int n, m, an, bn, am, bm, sum = 0, count = 0;

	do
	{
		system("cls");
		printf("Введите количество строк: ");
		scanf_s("%d", &n);
		printf("Введите количество столбцов: ");
		scanf_s("%d", &m);
	} while (n <= 0 || m <= 0);

	a = (int*)malloc(n * m * sizeof(int));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			printf("a[%d][%d] = ", i, j);
			scanf_s("%d", (a + i * m + j));
		}

	system("cls");

	Inter(an, bn);
	Inter(am, bm);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if ((i<an || i>bn) && (j<am || j>bm))
			{
				sum += *(a + i * m + j);
				count++;
			}

	free(a);

	printf("Количество: %d\nСумма: %d\n", count, sum);

	return 0;
}