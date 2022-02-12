#include<iostream>

struct Kid
{
	char Name[100];
	int School;
	int Class;
};

void input_file(Kid mas[], int& size)
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
			fscanf_s(ft, "%s %d %d", &mas[i].Name, 100, &mas[i].School, &mas[i].Class);
		fclose(ft);
	}
}

void output_file(Kid mas[], int size)
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
			fprintf_s(f, "%s %d %d\n", mas[i].Name, mas[i].School, mas[i].Class);
		fclose(f);
	}
}
void printmas(Kid mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s | Школа №%d | Класс №%d\n", mas[i].Name, mas[i].School, mas[i].Class);
	}
}

void hand(Kid mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("Ввод %d ученика\nИмя: ", i);
		scanf_s("%s\0", &mas[i].Name, 100);
		printf("Школа: ");
		scanf_s("%d", &mas[i].School);
		printf("Класс: ");
		scanf_s("%d", &mas[i].Class);
	}
}

void task(Kid mas[], int size, int s)
{
	for (int i = 0; i < size; i++)
	{
		if (mas[i].School == s && mas[i].Class > 9)
		{
			printf("%s | Школа №%d | Класс №%d\n", mas[i].Name, mas[i].School, mas[i].Class);
		}
	}
}

int main()
{
	system("chcp 1251>nul");
	int n, s, c;
	Kid mas[100];
	srand(time(0));
	printf("Выберите способ задания чисел массива:\n1 - ввести значения саммостоятельно\n2 - загрузка из файла\nВыбор: ");
	scanf_s("%d", &c);
	if (c != 2)
	{
		do
		{
			printf("Введите количество учеников...");
			scanf_s("%d", &n);
		} while (n >= 100 || n <= 0);
	}
	if (c == 1)
	{
		hand(mas, n);
		printmas(mas, n);
	}
	else if (c == 2)
	{
		input_file(mas, n);
		printmas(mas, n);
	}

	printf("\nВведите номер школы: ");
	scanf_s("%d", &s);

	task(mas, n, s);

	output_file(mas, n);
}