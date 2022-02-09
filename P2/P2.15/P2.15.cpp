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
		printf("a[%2d] = ", i);
		scanf_s("%d", &arr[i]);
	}
}

//Получение максимального числа
void GetMax(int* arr, int s, int& max)
{
	for (int i = 0; i < s; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
}

//Получение минимального числа
void GetMin(int* arr, int s, int& min)
{
	for (int i = 0; i < s; i++)
	{
		if (arr[i] < min)
			min = arr[i];
	}
}
//Выбор хода выполнения
void GetType(int& type)
{
	printf("Выберите что вывести:\n1 - Номера чисел с минимальным значением\n2 - Номера чисел с максимальным значением\nВаш выбор: ");
	do
	{
		scanf_s("%d", &type);
	} while (type < 1 || type > 2);
}

//Вывод ответа
void Answer(int* arr, int s, int type, int min, int max)
{
	printf("\nМинимум = %d\nМаксимум = %d\n", min, max);
	printf("\nНомера элементов:\n");
	for (int i = 0; i < s; i++)
	{
		switch (type)
		{
		case 1:
		{
			if (arr[i] == min)
				printf("%d\n", i + 1);
			break;
		}
		case 2:
		{
			if (arr[i] == max)
				printf("%d\n", i + 1);
			break;
		}
		default:
			break;
		}
	}
}

int main()
{
	system("chcp 1251");
	//Объявление переменных
	int s = 3, type = 0, min = 10000, max = -10000, arr[20];

	SetSize(s); //Задача размера

	FillArr(arr, s); //Заполнение массива

	GetType(type);

	GetMax(arr, s, max);

	GetMin(arr, s, min);

	Answer(arr, s, type, min, max); //Получение ответ

	return 0;
}