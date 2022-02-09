#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

struct Rect
{
	int x1;
	int y1;
	int x2;
	int y2;
};

int getarea(Rect rectangle)
{
	return (rectangle.x2 - rectangle.x1) * (rectangle.y2 - rectangle.y1);
}

void input_file(Rect* mas, int& size)
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
			fscanf_s(ft, "%d %d %d %d", &mas[i].x1, &mas[i].x2, &mas[i].y1, &mas[i].y2);
		fclose(ft);
	}
}

void output_file(Rect* mas, int size)
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
			fprintf_s(f, "%d %d %d %d\n", mas[i].x1, mas[i].x2, mas[i].y1, mas[i].y2);
		fclose(f);
	}
}

void selffill(Rect* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		do
		{
			system("cls");
			printf("Ввод %d Прямоугольника\nКоордината X верхнего левого угла = ", i);
			scanf_s("%d", &mas[i].x1);
			printf("Координата Y верхнего левого угла = ");
			scanf_s("%d", &mas[i].y1);
			printf("Координата X нижнего правого угла = ");
			scanf_s("%d", &mas[i].x2);
			printf("Координата Y нижнего правого угла = ");
			scanf_s("%d", &mas[i].y2);
		} while (mas[i].x1 >= mas[i].x2 || mas[i].y1 >= mas[i].y2);
	}
}

void printmas(Rect mas[], int size)
{
	system("cls");
	printf("Список прямоугольников:\n");
	for (int i = 0; i < size; i++)
	{
		printf("\nПрямоугольник №%d:\n(%d;%d);(%d;%d)\nПлощадь = %d\n", i, mas[i].x1, mas[i].y1, mas[i].x2, mas[i].y2, getarea(mas[i]));
	}
}

void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("Способы ввода:\n1 - с клавиатуры\n2 - из файла\nВыбор : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 2);
}

void setsize(int& size)
{
	do
	{
		system("cls");
		printf("Введите количество прямоугольников = ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

void switcher(Rect* mas, int& size, int type)
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
		system("cls");
		input_file(mas, size);
		break;
	}
	default:
		break;
	}
}

bool maxing(int a, int b)
{
	if (a >= b)
		return true;
	return false;
}

void getmax(Rect mas[], int size, int& max, int& index)
{
	for (int i = 0; i < size; i++)
	{
		int area = getarea(mas[i]);
		if (maxing(area, max))
		{
			max = area;
			index = i;
		}
	}
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	int type = 0, size = 0, max = 0, index = 0;
	Rect mas[100];

	choosetype(type);

	if (type != 2)
		setsize(size);

	switcher(mas, size, type);

	printmas(mas, size);

	getmax(mas, size, max, index);

	printf("\nПлощадь прямоугольника №%d максимальна и равна %d", index, max);

	output_file(mas, size);

	return 0;
}