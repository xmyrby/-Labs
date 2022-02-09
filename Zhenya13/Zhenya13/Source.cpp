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
		printf("Выберите способ задания чисел массива:\n1 - ввести значения саммостоятельно\n2 - заполнение случайными\nВыбор: ");
		scanf_s("%d", &way);
	} while (way > 2 || way < 1);

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
	default:
		break;
	}

	printf("Сумма всех положительных элементов массива S=%d\nМассив после изменения: \n", task(a, n));
	printmas(a, n);

	return 0;
}