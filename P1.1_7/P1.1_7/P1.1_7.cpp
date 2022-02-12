#include <iostream>

//Задание размера массива
void SetSize(int& s)
{
	do
	{
		system("cls");
		printf("Введите размер массива (от 3 до 20) = ");
		scanf_s("%d", &s);
	} while (s < 3 || s > 20);
}

//Заполнение массива
void FillArr(int* arr, int s)
{
	printf("Массив:\n");
	for (int i = 0; i < s; i++)
	{
		arr[i] = rand() % 201 - 100;
		printf("a[%2d] = %3d\n", i, arr[i]);
	}
}
//Вывод индексов четных элементов
void PrintIndexes(int* arr, int s)
{
	printf("\nИндексы чётных эл-тов:\n");
	for (int i = 0; i < s; i++)
	{
		//Проверка
		if (arr[i] % 2 == 0)
			printf("%3d\n", i);
	}
}

int main()
{
	system("chcp 1251");
	srand(time(0));
	//Объявление переменных
	int s = 3, arr[20];

	SetSize(s); //Задача размера

	FillArr(arr, s); //Заполнение массива

	PrintIndexes(arr, s); //Вывод индексов

	return 0;
}