#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>

struct Sums
{
	int sums[100];
	int indexes[100];
};

Sums getSums(int mas[100][100], int sizei, int sizej)
{
	Sums sums;

	for (int i = 0; i < sizei; i++)
	{
		sums.sums[i] = 0;
		sums.indexes[i] = i;
		for (int j = 0; j < sizej; j++)
			if (mas[i][j] % 2 == 0)
				sums.sums[i] += mas[i][j];
	}
	return sums;
}

void input_file(int mas[100][100], int& sizei, int& sizej)
{
	FILE* ft;
	if (fopen_s(&ft, "save.txt", "rt") != 0)
	{
		printf("\nОшибка чтения txt!");
		exit(1);
	}
	fscanf_s(ft, "%d", &sizei);
	fscanf_s(ft, "%d", &sizej);

	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			fscanf_s(ft, "%d", &mas[i][j]);
	fclose(ft);
}

void input_bin(int mas[100][100], int& sizei, int& sizej)
{
	FILE* ft = NULL;
	if (fopen_s(&ft, "save.bin", "rt"))
	{
		printf("\nОшибка чтения bin!");
		exit(1);
	}
	fread(&sizei, sizeof(int), 1, ft);
	fread(&sizej, sizeof(int), 1, ft);

	for (int i = 0; i < sizei; i++)
		fread(mas[i], sizeof(int), sizej, ft);
	fclose(ft);
}

void output_file(int mas[100][100], int sizei, int sizej)
{
	FILE* f;

	if (fopen_s(&f, "save.txt", "r+b") != 0)
	{
		printf("\nОшибка записи txt!");
		exit(1);
	}
	fprintf_s(f, "%d\n", sizei);
	fprintf_s(f, "%d\n", sizej);
	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			fprintf_s(f, "%d\n", mas[i][j]);
	fclose(f);
}

void output_bin(int mas[100][100], int sizei, int sizej)
{
	FILE* f;

	if (fopen_s(&f, "save.bin", "w+"))
	{
		printf("\nОшибка записи bin!");
		exit(1);
	}
	fwrite(&sizei, sizeof(int), 1, f);
	fwrite(&sizej, sizeof(int), 1, f);
	for (int i = 0; i < sizei; i++)
		fwrite(mas[i], sizeof(int), sizej, f);
	fclose(f);
}

void randfill(int mas[100][100], int sizei, int sizej)
{
	int start, end;
	do
	{
		system("cls");
		printf("Введите начальную границу значений = ");
		scanf_s("%d", &start);
		printf("Введите конечную границу значений = ");
		scanf_s("%d", &end);
	} while (start >= end);

	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			mas[i][j] = (rand() % (end - start + 1) + start);
}

void printmas(int mas[100][100], int sizei, int sizej)
{
	Sums sums = getSums(mas, sizei, sizej);
	printf("Массив:\n");
	for (int i = 0; i < sizei; i++)
	{
		for (int j = 0; j < sizej; j++)
			printf("%6d", mas[i][j]);
		printf("	: %d", sums.sums[i]);
		printf("\n");
	}
}

double sumEl(int mas[100][100], int sizei, int sizej)
{
	double sum = 0;
	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			if (i * j % 2 == 0)
				sum += mas[i][j];
	return sum;
}

void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("Способы ввода:\n1 - случайными числами\n2 - из файла\n3 - из бинарного файла\nВыбор : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 5);
}

void setsize(int& sizei, int& sizej)
{
	do
	{
		system("cls");
		printf("Введите размер массива i = ");
		scanf_s("%d", &sizei);
	} while (sizei <= 0 || sizei > 100);
	do
	{
		system("cls");
		printf("Введите размер массива j = ");
		scanf_s("%d", &sizej);
	} while (sizej <= 0 || sizej > 100);
}

void switcher(int mas[100][100], int& sizei, int& sizej, int type)
{
	switch (type)
	{
	case 1:
	{
		randfill(mas, sizei, sizej);
		break;
	}
	case 2:
	{
		input_file(mas, sizei, sizej);
		break;
	}
	case 3:
	{
		input_bin(mas, sizei, sizej);
		break;
	}
	default:
		break;
	}
}

int getCol(int mas[100][100], int sizei, int sizej)
{
	int count = 0;
	for (int j = 0; j < sizej; j++)
	{
		int zero = 0;
		for (int i = 0; i < sizei; i++)
			if (mas[i][j] == 0)
				zero++;
		if (!zero)
			count++;
	}
	return count;
}

void moveRows(int mas[100][100], int sizei, int sizej)
{
	Sums sums = getSums(mas, sizei, sizej);
	int mas2[100][100];

	int moved = 0, iter = sizei - 1;
	do
	{
		moved = 0;
		for (int i = 0; i < iter; i++)
		{
			if (sums.sums[i] > sums.sums[i + 1])
			{
				int c = sums.sums[i];
				sums.sums[i] = sums.sums[i + 1];
				sums.sums[i + 1] = c;

				c = sums.indexes[i];
				sums.indexes[i] = sums.indexes[i + 1];
				sums.indexes[i + 1] = c;

				moved++;
			}
		}
		iter--;
	} while (moved);

	for (int s = 0; s < sizei; s++)
		for (int j = 0; j < sizej; j++)
			mas2[s][j] = mas[sums.indexes[s]][j];
	printmas(mas2, sizei, sizej);
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	int type = 0, sizei = 0, sizej = 0, max = 0, index = 0;
	int mas[100][100];

	choosetype(type);

	if (type == 1)
		setsize(sizei, sizej);

	switcher(mas, sizei, sizej, type);
	system("cls");
	printmas(mas, sizei, sizej);
	printf("\nСтолбцы не содержащие нулевых эл-тов = %d\n\n", getCol(mas, sizei, sizej));
	moveRows(mas, sizei, sizej);
	output_file(mas, sizei, sizej);
	output_bin(mas, sizei, sizej);

	return 0;
}