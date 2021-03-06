#include <iostream>
#include <malloc.h>

void Inter(int& a, int& b)
{
	do
	{
		system("cls");
		printf("??????? ?????? ?????????: ");
		scanf_s("%d", &a);
		printf("??????? ????? ?????????: ");
		scanf_s("%d", &b);
	} while (a > b || a < 0 || b < 0);
}

void GetRC(int& n, int& m)
{
	do
	{
		system("cls");
		printf("??????? ?????????? ?????: ");
		scanf_s("%d", &n);
		printf("??????? ?????????? ????????: ");
		scanf_s("%d", &m);
	} while (n <= 0 || m <= 0);
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

void GetSumNCount(int* a, int& sum, int& count, int n, int m, int an, int bn, int am, int bm)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if ((i<an || i>bn) && (j<am || j>bm))
			{
				sum += *(a + i * m + j);
				count++;
			}

}

int main()
{
	system("chcp 1251 > null");

	int* a;
	int n, m, an, bn, am, bm, sum = 0, count = 0;

	GetRC(n, m);

	a = Mem(n, m);

	system("cls");

	Inter(an, bn);
	Inter(am, bm);

	GetSumNCount(a, sum, count, n, m, an, bn, am, bm);

	free(a);

	printf("??????????: %d\n?????: %d\n", count, sum);

	return 0;
}