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
void FillArr(int* arr1, int s, int& otr)
{
	printf("Массив:\n");
	for (int i = 0; i < s; i++)
	{
		arr1[i] = rand() % 201 - 100;
		printf("a[%2d] = %3d\n", i, arr1[i]);
		if (arr1[i] < 0)
			otr++;
	}
}

//Заполнение второго массива
void Refill(int* arr1, int* arr2, int s, int otr)
{
	int po = 0, ot = 0;

	for (int i = 0; i < s; i++)
	{
		if (arr1[i] < 0)
		{
			arr2[ot] = arr1[i];
			ot++;
		}
		else
		{
			arr2[otr + po] = arr1[i];
			po++;
		}
	}
}
//Вывод массива
void PrintMas(int* arr2, int s)
{
	printf("\nНовый массив:\n");
	for (int i = 0; i < s; i++)
		printf("a[%2d] = %3d\n", i, arr2[i]);
}

int main()
{
	system("chcp 1251");
	srand(time(0));
	//Объявление переменных
	int s = 3, otr = 0, arr1[20], arr2[20];

	SetSize(s); //Задача размера

	FillArr(arr1, s, otr); //Заполнение массива

	Refill(arr1, arr2, s, otr); //Заполнение второго массива

	PrintMas(arr2, s); //Вывод второго массива

	return 0;
}