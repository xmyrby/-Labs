#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <windows.h>

//Заполнение случайными числами
void randfill(double mas[100][100], int sizei, int sizej)
{
	int err = 0;
	int start = -50, end = 30;

	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			mas[i][j] = (rand() % (end - start) + start) + (rand() % 101) / 100.0;
}

//Вывод массива с выделением цвета
void printmas(double mas[100][100], int sizei, int sizej)
{
	printf("Массив:\n");
	for (int i = 0; i < sizei; i++)
	{
		for (int j = 0; j < sizej; j++)
			printf("%8.3lf", mas[i][j]);
		printf("\n");
	}
	printf("\n");
}

//Получение модуля максимального элемента
void getMax(double mas[100][100], int sizei, int sizej, double& max)
{
	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			if (fabs(mas[i][j]) > max)
				max = fabs(mas[i][j]);
}

//Задание размера массива
void setsize(int& sizei, int& sizej)
{
	int err = 0;
	do
	{
		system("cls");
		if (err)
			printf("Неверный ввод!\n");
		err = 1;
		printf("Введите размер массива m = ");
		scanf_s("%d", &sizei);
	} while (sizei <= 0 || sizei > 100);
	err = 0;
	do
	{
		system("cls");
		if (err)
			printf("Неверный ввод!\n");
		err = 1;
		printf("Введите размер массива n = ");
		scanf_s("%d", &sizej);
	} while (sizej <= 0 || sizej > 100);
	system("cls");
}

//Деление всех элементов на максимальный
void getNewMatrix(double mas[100][100], int sizei, int sizej, double max)
{
	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			mas[i][j] /= max;
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	int sizei = 0, sizej = 0;
	double mas[100][100], max = -50;

	setsize(sizei, sizej);

	randfill(mas, sizei, sizej);
	printmas(mas, sizei, sizej);
	getMax(mas, sizei, sizej, max);
	printf("Наибольший по модулю элемент = %.3lf\n\n",max);
	getNewMatrix(mas, sizei, sizej, max);
	printmas(mas, sizei, sizej);

	return 0;
}