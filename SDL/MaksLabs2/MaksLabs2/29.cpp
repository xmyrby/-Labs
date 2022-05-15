#include <iostream>

//Заполнение матрицы случайными числами
void FillMatrix(int matrix[5][5])
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			matrix[i][j] = rand() % 11;
}

//Вывод матрицы
void PrintMatrix(int matrix[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			printf("%3d ", matrix[i][j]);
		printf("\n");
	}
}

//Переворот матрицы
void Rotate(int matrix[5][5])
{
	int rotated[5][5];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			rotated[4 - i][4 - j] = matrix[i][j];

	printf("\nМатрица после поворота:\n");
	PrintMatrix(rotated);
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));
	int matrix[5][5];

	printf("Начальная матрица:\n");
	FillMatrix(matrix);

	PrintMatrix(matrix);

	Rotate(matrix);

	return 0;
}