#include <iostream>
#include <ctime>

struct Student
{
	int Math;
	int Physics;
	int Informatics;
};

void printmas(Student* mas, int size)
{
	system("cls");
	for (int i = 0; i < size; i++)
	{
		printf("Оценки студента %d\nМатематика: %d\nФизика: %d\nИнформатика: %d\n\n", i, mas[i].Math, mas[i].Physics, mas[i].Informatics);
	}
}

void task(Student* mas, int size, double& math, double& phys, double& info)
{
	for (int i = 0; i < size; i++)
	{
		math += mas[i].Math;
		phys += mas[i].Physics;
		info += mas[i].Informatics;
	}

	math /= size;
	phys /= size;
	info /= size;
}

void Hand(Student* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("Введите оценки %d студента:\n", i);
		printf("Математика: ");
		scanf_s("%d", &a[i].Math);
		printf("Физика: ");
		scanf_s("%d", &a[i].Physics);
		printf("Информатика: ");
		scanf_s("%d", &a[i].Informatics);
	}
}

void input_file(Student* mas, int& size)
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
			fscanf_s(ft, "%d %d %d", &mas[i].Math, &mas[i].Physics, &mas[i].Informatics);
		fclose(ft);
	}
}

void output_file(Student* mas, int size)
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
			fprintf_s(f, "%d %d %d\n", mas[i].Math, mas[i].Physics, mas[i].Informatics);
		fclose(f);
	}
}

int getSize()
{
	int n = 0;
	do
	{
		printf("Введите кол-во студентов (не более 100) - ");
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
	Student mas[100];
	int size;
	double  math = 0, phys = 0, info = 0;

	system("chcp 1251>nul");

	int way;

	// проверка ввода
	do
	{
		system("cls");
		printf("Выберите способ задания:\n1 - ввести значения самостоятельно\n2 - загрузка из файла\nВыбор: ");
		scanf_s("%d", &way);
	} while (way > 2 || way < 1);

	if (way != 2)
		size = getSize();
	// оператор множественного выбора
	switch (way)
	{
	case 1:
	{
		Hand(mas, size);
		printmas(mas, size);
		break;
	}
	case 2:
	{
		input_file(mas, size);
		printmas(mas, size);
		break;
	}
	default:
		break;
	}

	task(mas, size, math, phys, info);

	printf("\nСредние оценки\nМатематика: %.3lf\nФизика: %.3lf\nИнформатика: %.3lf", math, phys, info);

	output_file(mas, size);

	return 0;
}