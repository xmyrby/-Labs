/*ƒан массив вещественных случайных чисел (размер массива определ€ет пользователь, но в диапазоне [3;20]). ”казать, упор€дочены ли числа в массиве по 
возрастанию.*/
//ѕо точке. ƒл€ нормально
#include<iostream>

void SetSize(int& size)
{
	do
	{
		printf("¬ведите разер массива от 3 до 20: ");
		scanf_s("%i", &size);
	} while (size < 3 || size>20);
}

void RandomArray(int size, double* arr)
{
	printf("Array:\n");
	for (int i = 0; i < size; i++)
	{
		arr[i] = (rand() % 201- 100.0)/10;
		printf("%3.1lf\n", arr[i]);
	}
}

void SequenceArray(int size,double* arr)
{
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("ћассив не упор€дочен по возрастанию"); break;
	}
	}
}

/*void PrintArray(int size, double* arr)
{
	for (int i = 1; i < size; i++)
		printf("%d\n", arr[i]);
}
*/
int main()
{
	system("chcp 1251");
	srand(time(0));
	double arr[20];int size = 3;
	SetSize(size);
	RandomArray(size, arr);

	SequenceArray(size, arr);
}
