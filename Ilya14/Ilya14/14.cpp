#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

void selffill(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("mas[%d] = ", i);
		scanf_s("%d", &mas[i]);
	}
}

void randfill(int* mas, int size)
{
	int start, end;
	do
	{
		system("cls");
		printf("Введите начальную границу значений = ");
		scanf_s("%d", &start);
		printf("Введите конечную границу значений = ");
		scanf_s("%d", &end);
	} while (start > end);

	for (int i = 0; i < size; i++)
		mas[i] = rand() % (end - start + 1) + start;
}

void printmas(int mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("mas[%d] = %d\n", i, mas[i]);
	}
}

void input_file(int* mas, int& size)
{
	FILE* ft;
	if (fopen_s(&ft, "save.txt", "rt") != 0)
	{
		printf("Ошибка чтения!");
		exit(1);
	}
	else
	{
		fscanf_s(ft, "%d", &size);

		for (int i = 0; i < size; i++)
			fscanf_s(ft, "%d", &mas[i]);
		fclose(ft);
	}
}

void output_file(int* mas, int size)
{
	FILE* f;

	if (fopen_s(&f, "save.txt", "w+") != 0)
	{
		printf("Ошибка записи!");
		exit(1);
	}
	else
	{
		fprintf_s(f, "%d\n", size);
		for (int i = 0; i < size; i++)
			fprintf_s(f, "%d\n", mas[i]);
		fclose(f);
	}
}

void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("Способы ввода:\n1 - с клавиатуры\n2 - случайными числами\n3 - из файла\nВыбор : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 3);
}

void setsize(int& size)
{
	do
	{
		system("cls");
		printf("Введите размер массива = ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

int transform(int* mas, int size)
{
	int count = 0, min = 100000;
	for (int i = 0; i < size; i++)
	{
		if (mas[i] > 0 && mas[i] < min)
		{
			min = mas[i];
		}
		if (mas[i] * mas[i + 1] < 0)
		{
			count++;
		}
	}

	for (int i = 0; i < size; i++)
	{
		mas[i] *= min;
	}
	return count;
}

void switcher(int* mas, int& size, int type)
{
	switch (type)
	{
	case 1:
	{
		system("cls");
		selffill(mas, size);
		break;
	}
	case 2:
	{
		randfill(mas, size);
		break;
	}
	case 3:
	{
		input_file(mas, size);
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

	int type = 0, size = 0;
	int mas[100];

	choosetype(type);

	if (type != 3)
		setsize(size);

	switcher(mas, size, type);

	system("cls");
	printf("Исходный массив:\n");
	printmas(mas, size);
	printf("\nКол-во изменений знака: %d\n", transform(mas, size));

	printf("\nМассив после преобразований:\n");
	printmas(mas, size);

	output_file(mas, size);

	return 0;
}