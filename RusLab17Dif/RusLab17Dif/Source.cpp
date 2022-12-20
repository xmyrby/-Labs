#include<iostream>

//Свап указателей на значения чисел
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//Вывод массива в консоль
void PrintMas(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", mas[i]);
	}
	printf("\n");
}

//Способ 1
void WayDif_0(int* mas0, int* mas1, int* mas2, int sizes[3])
{
	int size = sizes[0] + sizes[1] + sizes[2];
	int* mas = (int*)malloc(sizeof(int) * size);
	int iters = 0;

	//Перенос в 1 массив значений всех массивов
	for (int i = 0; i < size; i++)
	{
		if (i < sizes[0])
			mas[i] = mas0[i];
		if (i < sizes[1])
			mas[i + sizes[0]] = mas1[i];
		if (i < sizes[2])
			mas[i + sizes[0] + sizes[1]] = mas2[i];
	}

	//Сортировка пузырьком
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
		{
			if (mas[j] > mas[j + 1])
			{
				swap(&mas[j], &mas[j + 1]);
			}
			iters++;
		}

	//Возвращение в массивы отсортированных значений
	for (int i = 0; i < size; i++)
	{
		if (i < sizes[0])
			mas0[i] = mas[i];
		if (i < sizes[1])
			mas1[i] = mas[i + sizes[0]];
		if (i < sizes[2])
			mas2[i] = mas[i + sizes[0] + sizes[1]];
	}
	printf("\nИтераций: %d\n\n", iters);
}

//Способ 2
void WayDif_1(int* mas0, int* mas1, int* mas2, int sizes[3])
{
	int size = sizes[0] + sizes[1] + sizes[2];
	int* mas = (int*)malloc(sizeof(int) * size);
	int iters = 0;

	//Перенос в 1 массив значений всех массивов
	for (int i = 0; i < size; i++)
	{
		if (i < sizes[0])
			mas[i] = mas0[i];
		if (i < sizes[1])
			mas[i + sizes[0]] = mas1[i];
		if (i < sizes[2])
			mas[i + sizes[0] + sizes[1]] = mas2[i];
	}

	//Сортировка вставкой
	for (int i = 0; i < size; i++)
	{
		int x = mas[i];
		int j = i;
		while (j > 0 && mas[j - 1] > x)
		{
			mas[j] = mas[j - 1];
			--j;
			iters++;
		}
		mas[j] = x;
	}

	//Возвращение в массивы отсортированных значений
	for (int i = 0; i < size; i++)
	{
		if (i < sizes[0])
			mas0[i] = mas[i];
		if (i < sizes[1])
			mas1[i] = mas[i + sizes[0]];
		if (i < sizes[2])
			mas2[i] = mas[i + sizes[0] + sizes[1]];
	}
	printf("\nИтераций: %d\n\n",iters);
}

//Задание размера
void SetSize(int& size)
{
	do
	{
		printf("Введите размер массива: ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 10);
	printf("\n");
}

//Заполнение массива
void FillMas(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("Введите элемент №%d: ", i + 1);
		scanf_s("%d", &mas[i]);
	}
	printf("\n");
}

int choose()
{
	int t = 0;
	do
	{
		printf("Выберите способ сортировки:\n1 - Пузырьковая\n2 - Сортировка вставками\nВыбор: ");
		scanf_s("%d", &t);
	} while (t<1 || t>2);
	return t;
}

int main()
{
	system("chcp 1251 > nul");

	int sizes[3];

	//Создание массивов и выделение размера в памяти
	SetSize(sizes[0]);
	int* mas0 = (int*)malloc(sizeof(int) * sizes[0]);
	FillMas(mas0, sizes[0]);

	SetSize(sizes[1]);
	int* mas1 = (int*)malloc(sizeof(int) * sizes[1]);
	FillMas(mas1, sizes[1]);

	SetSize(sizes[2]);
	int* mas2 = (int*)malloc(sizeof(int) * sizes[2]);
	FillMas(mas2, sizes[2]);

	//Вывод массивов0
	PrintMas(mas0, sizes[0]);
	PrintMas(mas1, sizes[1]);
	PrintMas(mas2, sizes[2]);

	if(choose()==1)
		WayDif_0(mas0, mas1, mas2, sizes);
	else
		WayDif_1(mas0, mas1, mas2, sizes);

	PrintMas(mas0, sizes[0]);
	PrintMas(mas1, sizes[1]);
	PrintMas(mas2, sizes[2]);

	return 0;
}