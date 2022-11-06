#include<iostream>

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void PrintMas(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", mas[i]);
	}
	printf("\n");
}

void WayDif_0(int* mas0, int* mas1, int* mas2, int sizes[3])
{
	int size = sizes[0] + sizes[1] + sizes[2];
	int* mas = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++)
	{
		if (i < sizes[0])
			mas[i] = mas0[i];
		if (i < sizes[1])
			mas[i + sizes[0]] = mas1[i];
		if (i < sizes[2])
			mas[i + sizes[0] + sizes[1]] = mas2[i];
	}

	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (mas[j] > mas[j + 1])
				swap(&mas[j], &mas[j + 1]);

	for (int i = 0; i < size; i++)
	{
		if (i < sizes[0])
			mas0[i] = mas[i];
		if (i < sizes[1])
			mas1[i] = mas[i + sizes[0]];
		if (i < sizes[2])
			mas2[i] = mas[i + sizes[0] + sizes[1]];
	}
	printf("\n");
}

void SetSize(int& size)
{
	do
	{
		printf("Введите размер массива: ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 10);
	printf("\n");
}

void FillMas(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("Введите элемент №%d: ", i + 1);
		scanf_s("%d", &mas[i]);
	}
	printf("\n");
}

int main()
{
	system("chcp 1251 > nul");

	int sizes[3];

	SetSize(sizes[0]);
	int* mas0 = (int*)malloc(sizeof(int) * sizes[0]);
	FillMas(mas0, sizes[0]);

	SetSize(sizes[1]);
	int* mas1 = (int*)malloc(sizeof(int) * sizes[1]);
	FillMas(mas1, sizes[1]);

	SetSize(sizes[2]);
	int* mas2 = (int*)malloc(sizeof(int) * sizes[2]);
	FillMas(mas2, sizes[2]);

	PrintMas(mas0, sizes[0]);
	PrintMas(mas1, sizes[1]);
	PrintMas(mas2, sizes[2]);

	WayDif_0(mas0, mas1, mas2, sizes);

	PrintMas(mas0, sizes[0]);
	PrintMas(mas1, sizes[1]);
	PrintMas(mas2, sizes[2]);

	return 0;
}