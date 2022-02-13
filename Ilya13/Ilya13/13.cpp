#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

//Заполнение самостоятельно
void selffill(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("mas[%d] = ", i);
		scanf_s("%d", &mas[i]);
	}
}

//Заполнение случайными числами
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

//Вывод массива
void printmas(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("mas[%d] = %d\n", i, mas[i]);
	}
}

//Выбор способа
void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("Способы ввода:\n1 - с клавиатуры\n2 - случайными числами\nВыбор : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 2);
}

//Задания размера
void setsize(int& size)
{
	do
	{
		system("cls");
		printf("Введите размер массива = ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

//Заполнение
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
	default:
		break;
	}
}

//Трансформация массива
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

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	//Объявление пременных
	int type, size;
	int mas[100];

	choosetype(type);

	setsize(size);

	switcher(mas, size, type);

	system("cls");
	printf("Исходный массив:\n");
	printmas(mas, size);
	printf("\nКол-во изменений знака: %d\n", transform(mas, size));

	printf("\nМассив после преобразований:\n");
	printmas(mas, size);

	return 0;
}