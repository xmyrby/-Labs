// Дан массив вещественных случайных чисел(размер массива определяет пользователь, но в диапазоне[3; 20]).Определить число чисел из диапазона[-5; 5]
#include <iostream>
//Установка размера массива
void SetSize(int& s)
{
	do
	{
		system("cls");
		printf("input size = ");
		scanf_s("%d", &s);
	} while (s < 3 || s > 20); //Проверка введённого значения
}
//Заполнение массива
void FillArr(double* arr, int s)
{
	printf("Массив:\n");
	for (int i = 0; i < s; i++)
	{
		arr[i] = (rand() % 2001 - 1000.0) / 10; // Получение случайного числа
		printf("%4.11f\n", arr[i]);
	}
}
//Получение количества чисел в диапазоне [-5;5]
int GetCount(double* arr, int s)
{
	int count = 0;
	for (int i = 0; i < s; i++)
	{
		if (arr[i] >= -5 && arr[i] <= 5) // Проверка, что число в диапазоне
			count++;
	}
	return count;
}

int main()
{
	system("chcp 1251");
	srand(time(0)); // Инициализация рандомайзера

	//Объявление переменных
	int s = 3;
	double arr[20];

	SetSize(s); // Установка размера массива

	FillArr(arr, s); // Заполнение массива

	printf("\nКоличество = %d", GetCount(arr, s)); // Вывод количества чисел

	return 0;
}