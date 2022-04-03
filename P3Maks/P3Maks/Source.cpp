#include <iostream>

//Задание размера массива
void SetSize(int& n)
{
	do
	{
		printf("Введите размер массива (1-100): ");
		scanf_s("%d", &n);
	} while (n < 1 || n > 100);
	system("cls");
}

//Вывод массива
void PrintMas(int* mas, int n)
{
	printf("Массив:\n");
	for (int i = 0; i < n; i++)
		printf("%d ", mas[i]);
}

//Заполнение массива
void FillMas(int* mas, int n)
{
	for (int i = 0; i < n; i++)
		mas[i] = rand() % 5;
}

//Повторение элементов
void Task(int* mas, int n)
{
	printf("\nПоследовательность:\n");
	int times[5]{ 0,0,0,0,0 };
	for (int i = 0; i < n; i++)
	{
		times[mas[i]]++;
		for (int j = 0; j < times[mas[i]]; j++)
		{
			printf("%d ", mas[i]);
		}
	}
}

int main()
{
	system("chcp 1251 > nul");

	int mas[100];
	int n;

	srand(time(NULL));

	SetSize(n);

	FillMas(mas, n);

	PrintMas(mas, n);

	Task(mas, n);

	return 0;
}