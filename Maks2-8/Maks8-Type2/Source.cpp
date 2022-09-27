#include <iostream>
#include <malloc.h>

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

void PrintMas(int* a, int n, int m)
{
	printf("Массив:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%3d", *(a + i * m + j));
		}
		printf("\n");
	}
}

int* Mem(int n, int m)
{
	int* a = (int*)malloc(n * m * sizeof(int));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			printf("a[%d][%d] = ", i, j);
			scanf_s("%d", (a + i * m + j));
		}
	return a;
}

double raznEl(int* mas, int sizei, int sizej)
{
	double sum1 = 0;
	double sum2 = 0;
	for (int i = 0; i < sizei; i++)
		sum1 += *(mas + i * sizej + i);
	for (int i = 0; i < sizei; i++)
		sum2 += *(mas + i * sizej + (sizej - i - 1));

	int a = 5;
	return sum1 - sum2;
}

int main()
{
	system("chcp 1251 > null");

	int* a;
	int n, m;

	GetRC(n, m);

	a = Mem(n, m);

	system("cls");

	PrintMas(a, n, m);

	printf("\nРазность элементов диагоналей = %.3lf", raznEl(a, n, m));

	free(a);

	return 0;
}