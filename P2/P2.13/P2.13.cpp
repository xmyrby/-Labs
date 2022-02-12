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
void FillArr(int* arr1, int s)
{
	printf("Массив:\n");
	for (int i = 0; i < s; i++)
	{
		printf("a[%2d] = ", i);
		scanf_s("%d", &arr1[i]);
	}
}
//Выбор хода выполнения
void GetType(int& type)
{
	printf("Выберите что вывести:\n1 - Сумма эл-тов с теми же номерами\n2 - Произведение эл-тов с теми же номерами\n3 - Максимальному эл-ту из двух с теми же  номерами\nВаш выбор: ");
	do
	{
		scanf_s("%d", &type);
	} while (type < 1 || type > 3);
}

//Получение максимального числа
int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

//Получение ответа
void GetAnswer(int* arr1, int* arr2, int* arr3, int s, int type)
{
	for (int i = 0; i < s; i++)
	{
		switch (type)
		{
		case 1:
		{
			arr3[i] = arr1[i] + arr2[i];
			break;
		}
		case 2:
		{
			arr3[i] = arr1[i] * arr2[i];
			break;
		}
		case 3:
		{
			arr3[i] = Max(arr1[i], arr2[i]);
			break;
		}
		default:
			break;
		}
		printf("a[%d] = %d\n", i, arr3[i]);
	}
}

int main()
{
	system("chcp 1251");
	//Объявление переменных
	int s = 3, type = 0, arr1[20], arr2[20], arr3[20];

	SetSize(s); //Задача размера

	FillArr(arr1, s); //Заполнение массива 1

	FillArr(arr2, s); //Заполнение массива 2

	GetType(type); //Выбор хода выполнения

	GetAnswer(arr1, arr2, arr3, s, type); //Получение ответ

	return 0;
}