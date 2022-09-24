#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>

void input_file(double mas[100][100], int& sizei, int& sizej)
{
	FILE* ft;
	if (fopen_s(&ft, "save.txt", "rt") != 0)
	{
		printf("Ошибка чтения!");
		exit(1);
	}
	fscanf_s(ft, "%d", &sizei);
	fscanf_s(ft, "%d", &sizej);

	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			fscanf_s(ft, "%lf", &mas[i][j]);
	fclose(ft);
}

void input_bin(double mas[100][100], int& sizei, int& sizej)
{
	FILE* ft = NULL;
	if (fopen_s(&ft, "save.bin", "rt"))
	{
		printf("Ошибка чтения!");
		exit(1);
	}
	fread(&sizei, sizeof(int), 1, ft);
	fread(&sizej, sizeof(int), 1, ft);

	for (int i = 0; i < sizei; i++)
		fread(mas[i], sizeof(double), sizej, ft);
	fclose(ft);
}

void output_file(double mas[100][100], int sizei, int sizej)
{
	FILE* f;

	if (fopen_s(&f, "save.txt", "r+b") != 0)
	{
		printf("Ошибка записи!");
		exit(1);
	}
	fprintf_s(f, "%d\n", sizei);
	fprintf_s(f, "%d\n", sizej);
	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			fprintf_s(f, "%lf\n", mas[i][j]);
	fclose(f);
}

void output_bin(double mas[100][100], int sizei, int sizej)
{
	FILE* f;

	if (fopen_s(&f, "save.bin", "w+"))
	{
		printf("Ошибка записи!");
		exit(1);
	}
	fwrite(&sizei, sizeof(int), 1, f);
	fwrite(&sizej, sizeof(int), 1, f);
	for (int i = 0; i < sizei; i++)
		fwrite(mas[i], sizeof(double), sizej, f);
	fclose(f);
}

void selffill(double mas[100][100], int sizei, int sizej)
{
	for (int i = 0; i < sizei; i++)
	{
		for (int j = 0; j < sizej; j++)
		{
			printf("a[%d,%d] = ", i, j);
			scanf_s("%lf", &mas[i][j]);
		}
	}
}

void randfill(double mas[100][100], int sizei, int sizej)
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
			mas[i][j] = (rand() % (end - start) + start) + ((rand() % 100) / 100.0);
}

void specfill(double mas[100][100], int sizei, int sizej)
{
	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
		{
			if (i > j)
				mas[i][j] = sin(i - j);
			else if (i == j)
				mas[i][j] = log(i + j + 2);
			else
				mas[i][j] = -cos(i + j);
		}
}

void printmas(double mas[100][100], int sizei, int sizej)
{
	system("cls");
	printf("Массив:\n");
	for (int j = 0; j < sizej; j++)
	{
		for (int i = 0; i < sizei; i++)
			printf("%8.2lf", mas[i][j]);
		printf("\n");
	}
}

double raznEl(double mas[100][100], int sizei, int sizej)
{
	double sum1 = 0;
	double sum2 = 0;
	for (int i = 0; i < sizei; i++)
		sum1 += mas[i][i];
	for (int i = 0; i < sizei; i++)
		sum2 += mas[i][sizej - i - 1];

	int a = 5;
	return sum1 - sum2;
}

void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("Способы ввода:\n1 - с клавиатуры\n2 - случайными числами\n3 - по формуле\n4 - из файла\n5 - из бинарного файла\nВыбор : ");
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

void switcher(double mas[100][100], int& sizei, int& sizej, int type)
{
	switch (type)
	{
	case 1:
	{
		system("cls");
		selffill(mas, sizei, sizej);
		break;
	}
	case 2:
	{
		randfill(mas, sizei, sizej);
		break;
	}
	case 3:
	{
		specfill(mas, sizei, sizej);
		break;
	}
	case 4:
	{
		input_file(mas, sizei, sizej);
		break;
	}
	case 5:
	{
		input_bin(mas, sizei, sizej);
		break;
	}
	default:
		break;
	}
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	int type = 0, sizei = 0, sizej = 0, max = 0, index = 0;
	double mas[100][100];

	choosetype(type);

	if (type < 4)
		setsize(sizei, sizej);

	switcher(mas, sizei, sizej, type);

	system("cls");
	printmas(mas, sizei, sizej);
	printf("\nРазность элементов диагоналей = %.3lf", raznEl(mas, sizei, sizej));

	output_file(mas, sizei, sizej);
	output_bin(mas, sizei, sizej);

	return 0;
}