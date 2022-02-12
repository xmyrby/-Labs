#include<iostream>

//Заполнение массива
void RandomArray(int* arr)
{
	printf("\nМассив:\n");
	for (int i = 0; i < 15; i++)
	{
		arr[i] = rand() % 201 - 100;
		printf("%i\n", arr[i]);
	}
}
//Вывод нового массива
void PrintNew(int* arr)
{
	printf("\nНовый массив:\n");
	int count = 0;
	for (int i = 0; i < 15; i++)
	{
		if (arr[i] < 0)
		{
			printf("a[%d] = %d\n", count, arr[i]);
			count++;
		}
	}
	for (int i = 0; i < 15; i++)
	{
		if (arr[i] >= 0)
		{
			printf("a[%d] = %d\n", count, arr[i]);
			count++;
		}
	}
}

int main()
{
	srand(time(0));
	system("chcp 1251");
	//Объявление переменных
	int arr[15];

	RandomArray(arr);

	PrintNew(arr);
}