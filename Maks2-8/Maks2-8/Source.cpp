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

void GetRC(int& n, int& m)
{
	do
	{
		system("cls");
		printf("Введите количество строк: ");
		scanf_s("%d", &n);
		printf("Введите количество столбцов: ");
		scanf_s("%d", &m);
	} while (n <= 0 || m <= 0);
}

int** Mem(int n, int m)
{
	int** a = (int**)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++)
	{
		a[i] = (int*)malloc(m * sizeof(int));
		for (int j = 0; j < m; j++)
		{
			printf("a[%d][%d] = ", i, j);
			scanf_s("%d", &a[i][j]);
		}
	}
	return a;
}

void GetSumNCount(int** a, int& sum, int& count, int n, int m, int an, int bn, int am, int bm)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if ((i<an || i>bn) && (j<am || j>bm))
			{
				sum += a[i][j];
				count++;
			}
}

void Free(int** a, int n)
{
	free(a);
	for (int i = 0; i < n; i++)
		free(a[i]);
}

int main()
{
	system("chcp 1251 > null");

	int** a;
	int n, m;

	GetRC(n, m);

	a = Mem(n, m);

	system("cls");

	Inter(an, bn);
	Inter(am, bm);

	GetSumNCount(a, sum, count, n, m, an, bn, am, bm);

	Free(a, n);

	printf("Количество: %d\nСумма: %d\n", count, sum);

	return 0;
}