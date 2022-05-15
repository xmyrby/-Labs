#include <iostream>

//Заполнение матрицы значениями
void FillMatrix(double matrix[10][10], int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			printf("a[%d, %d] = ", i, j);
			scanf_s("%lf", &matrix[i][j]);
		}
}

//Вывод матрицы
void PrintMatrix(double matrix[10][10], int n)
{
	system("cls");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%4.1lf ", matrix[i][j]);
		printf("\n");
	}
}

//Задание размера матрицы
void SetSize(int& n)
{
	do
	{
		system("cls");
		printf("Введите n (3-10): ");
		scanf_s("%d", &n);
	} while (n <= 2 || n > 10);
}

//Проверка на симметричность
bool Check(double matrix[10][10], int n)
{
	bool sim = true;
	for (int i = 1; i < n; i++)
		for (int j = 1; j < i; j++)
			if (matrix[i][j] != matrix[j][i])
				sim = false;
	return sim;
}

int main()
{
	system("chcp 1251 > nul");
	double matrix[10][10];
	int n;

	SetSize(n);

	printf("Матрица:\n");
	FillMatrix(matrix, n);

	PrintMatrix(matrix, n);
	
	if (Check(matrix, n))
		printf("Матрица симметрична");
	else
		printf("Матрица не симметрична");

	return 0;
}