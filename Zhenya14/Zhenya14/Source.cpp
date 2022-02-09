#include <iostream>
#include <ctime>

void printmas(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("a[%d] = %d\n", i, a[i]);
	}
}

int task(int* a, int n)
{
	int S = 0;

	for (int i = 0; i < n; i++)
	{
		if (a[i] % 2 != 0)
		{
			a[i] *= 3;
		}

		if (a[i] > 0)
		{
			S += a[i];
		}
	}
	return S;
}

void Hand(int* a, int n)
{
	printf("Ввод Массива:\n");
	for (int i = 0; i < n; i++)
	{
		printf("a[%d] = ", i);
		scanf_s("%d", &a[i]);
	}
}

void Rand(int* a, int n)
{
	int A, B;
	srand(time(NULL));
	printf("A = ");
	scanf_s("%d", &A);
	printf("B = ");
	scanf_s("%d", &B);
	printf("Массив:\n");
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % (B - A + 1) + A;
	}
}

void input_file(int* mas, int& size)
{
	FILE* ft;
	if (fopen_s(&ft, "save.txt", "rt") != 0)
	{
		printf("Ошибка чтения!");
		exit(1);
	}
	else
	{
		fscanf_s(ft, "%d", &size);

		for (int i = 0; i < size; i++)
			fscanf_s(ft, "%d", &mas[i]);
		fclose(ft);
	}
}

void output_file(int* mas, int size)
{
	FILE* f;

	if (fopen_s(&f, "save.txt", "w+") != 0)
	{
		printf("Ошибка записи!");
		exit(1);
	}
	else
	{
		fprintf_s(f, "%d\n", size);
		for (int i = 0; i < size; i++)
			fprintf_s(f, "%d\n", mas[i]);
		fclose(f);
	}
}

int getN()
{
	int n = 0;
	do
	{
		printf("Введите кол-во элементов массива (не более 100) - ");
		scanf_s("%d", &n);

		if (n < 1) // проверка введенного кол-ва элементов массива
		{
			printf("Невозможное кол-во элементов.");
		}
		if (n > 100) // проверка введенного кол-ва элементов массива
		{
			printf("Слишком много элементов!");
		}

	} while (n <= 0 || n > 100);
	return n;
}

int main()
{
	int a[100], n;

	system("chcp 1251>nul");

	int way;

	// проверка ввода
	do
	{
		system("cls");
		printf("Выберите способ задания чисел массива:\n1 - ввести значения саммостоятельно\n2 - заполнение случайными\n3 - загрузка из файла\nВыбор: ");
		scanf_s("%d", &way);
	} while (way > 3 || way < 1);

	if (way != 3)
		n = getN();
	// оператор множественного выбора
	switch (way)
	{
	case 1:
	{
		Hand(a, n);
		break;
	}
	case 2:
	{
		Rand(a, n);
		printmas(a, n);
		break;
	}
	case 3:
	{
		input_file(a, n);
		printmas(a, n);
		break;
	}
	default:
		break;
	}

	printf("Сумма всех положительных элементов массива S=%d\nМассив после изменения: \n", task(a, n));
	printmas(a, n);

	output_file(a, n);

	return 0;
}