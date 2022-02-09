#include <iostream>

//Объявление продукта
struct Product
{
	char Name[100];
	int Cost;
};

//Заполнение массива
void FillHand(Product* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("Ввод %d товара\nНазвание: ", i+1);
		scanf_s("%s\0", &mas[i].Name, 100);
		printf("Цена: ");
		scanf_s("%d", &mas[i].Cost);
	}
}

//Вывод массива
void PrintMas(Product* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s | Цена: %d\n", mas[i].Name, mas[i].Cost);
	}
}

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

//Получение среднего значения
int GetAverage(Product* mas, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += mas[i].Cost;
	}
	return sum / size;
}

//Получение количества товаров ценой ниже среднего
int GetCount(Product* mas, int size, int average)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (mas[i].Cost < average)
			count++;
	}
	return count;
}

int main()
{
	system("chcp 1251 > nul");

	//Объявление переменных
	int size = 0, average;
	Product mas[100];
	SetSize(size);
	FillHand(mas, size);
	system("cls");
	PrintMas(mas, size);

	average = GetAverage(mas, size);

	printf("\nСредняя цена товаров = %d", average);

	printf("\nКоличество товаров ценой ниже среднего: %d", GetCount(mas, size, average));

	return 0;
}