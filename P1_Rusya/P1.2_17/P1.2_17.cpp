#include <iostream>

//Задание размера массива
void SetSize(int& s)
{
	s = rand() % 5 + 5;
}

//Заполнение массива
void FillArr(double* arr, int s)
{
	printf("Массив (Размер - %d):\n", s);
	for (int i = 0; i < s; i++)
	{
		printf("a[%d] = ", i);
		scanf_s("%lf", &arr[i]);
	}
}

//Вывод индексов нечетных элементов
void MoveIndexes(double* arr, int s)
{
	int count = s / 2 * 2;
	printf("\nМассив после преобразоваия:\n");
	for (int i = 0; i < count; i += 2)
	{
		double c = arr[i + 1];
		arr[i + 1] = arr[i];
		arr[i] = c;
	}
}

//Вывод нового массива
void PrintArray(double* arr, int s)
{
	for (int i = 0; i < s; i++)
	{
		printf("%4.1lf\n", arr[i]);
	}
}

int main()
{
	system("chcp 1251");
	srand(time(0));
	//Объявление переменных
	int s = 3;
	double arr[20];

	SetSize(s); //Задача размера

	FillArr(arr, s); //Заполнение массива

	MoveIndexes(arr, s); //Преобразование массива

	PrintArray(arr, s); //Вывод нового массива

	return 0;
}