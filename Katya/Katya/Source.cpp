#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

/*Для решения задачи согласно варианту предоставить пользователю возможность выбора варианта ввода (с клавиатуры, случайные числа из диапазона от А до В,
из файла). Результат выводить на экран. Предлагать пользователю выводить массив в файл. При заполнении массива случайными числами и чтении его из файла,
выводить массив на экран. Все операции над массивом выполняются в пользовательских функциях. Каждое задание выполнять в отдельной функции.

1. Найти сумму отрицательных двузначных элементов массива. Все четные элементы массива разделить на 2. Удалить все элементы, меньшие суммы
отрицательных двузначных элементов. Вставить после каждого, кратного трем, элемента случайное число.*/


//void - не возвращает никакого значения, "пустая"

void self_fill(int*, int); //Заполнение с клавиатуры
void rand_fill(int*, int); //Заполнение случайными числами в диапазоне
void input_file(int*, int&); //Заполнение из файла
void output_file(int*, int); //Вывод массива в файл
void size_mass(int&); //Размер массива
void print_mas(int[], int); //Вывод массива на экран
void input_type_mass(int&); //Выбор варианта заполнения
void switcher(int*, int&, int); //Заполнение массива в зависимости от выбранного варианта
void output_mass(int*, int&, int); //Вывод массива
void massou_tput_type(int&); //Выбор варианта вывода массива
int sum_of_negative_two_digit_nums(int*, int); //Сумма отрицательных двузначных элементов массива
void divide_every_even_elem_by_two(int*, int); //Все четные элементы массива разделить на 2
void delete_elem(int*, int&, int); //Удалить все элементы, меньшие суммы отрицательных двузначных элементов
void insert_elem(int*, int&); //Вставить после каждого, кратного трем, элемента случайное число


int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	int type = 0, option = 0, size = 0;
	int mas[100];

	input_type_mass(type); //Выбор варианта заполнения
	if (type != 3) {
		size_mass(size);
	} //Размер массива в тех случаях, когда ввод не из файла
	switcher(mas, size, type); //Заполнение массива в зависимости от выбранного варианта

	system("cls"); //Очищаем экран
	printf("Исходный массив:\n");
	print_mas(mas, size);

	int sum = sum_of_negative_two_digit_nums(mas, size);
	divide_every_even_elem_by_two(mas, size);
	delete_elem(mas, size, sum);
	insert_elem(mas, size);

	massou_tput_type(option);
	output_mass(mas, size, option);

	return 0;
}

//Заполнение с клавиатуры
void self_fill(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls"); //очистить экран
		printf("mas[%d] = ", i);
		scanf_s("%d", &mas[i]);
	}
}

//Заполнение случайными числами в диапазоне
void rand_fill(int* mas, int size)
{
	int min, max;
	do
	{
		system("cls");
		printf("Введите минимальную границу значений = ");
		scanf_s("%d", &min);
		printf("Введите максимальную границу значений = ");
		scanf_s("%d", &max);
	} while (min > max);

	for (int i = 0; i < size; i++)
		mas[i] = rand() % (max - min + 1) + min;
}

//Заполнение из файла
void input_file(int* mas, int& size)
{
	FILE* ft;
	if (fopen_s(&ft, "file13.txt", "rt") != 0) //r - чтение, t - текстовый файл (но так по умолчанию)
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

//Вывод массива в файл
void output_file(int* mas, int size)
{
	FILE* f;

	if (fopen_s(&f, "file13.txt", "w+") != 0) //для чтения и записи
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

//Размер массива
void size_mass(int& size)
{
	do
	{
		system("cls");
		printf("Введите размер массива (не больше 100):");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

//Вывод массива на экран
void print_mas(int mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("mas[%d] = %d\n", i, mas[i]);
	}
}

//Выбор варианта заполнения
void input_type_mass(int& type)
{
	do
	{
		system("cls");
		printf("Выберете способ ввода:\n1 - с клавиатуры\n2 - случайными числами\n3 - из файла\nВыбор : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 3);
}

//Заполнение массива в зависимости от выбранного варианта
void switcher(int* mas, int& size, int type)
{
	switch (type)
	{
	case 1:
	{
		system("cls");
		self_fill(mas, size);
		break;
	}
	case 2:
	{
		rand_fill(mas, size);
		break;
	}
	case 3:
	{
		input_file(mas, size);
		break;
	}
	default: { break; }
	}
}

//Выбор варианта вывода массива
void massou_tput_type(int& option)
{
	do
	{
		printf("\nКак хотите вывести массив? \n 1 - на экран\n 2 - в файл\nВыбор: ");
		scanf_s("%d", &option);
	} while (option < 1 || option > 2);
}

//Вывод массива
void output_mass(int* mas, int& size, int option)
{
	switch (option)
	{
	case 1:
	{
		printf("\nМассив после преобразований:\n");
		print_mas(mas, size);
		break;
	}
	case 2:
	{
		output_file(mas, size);
		printf("\nМассив выведен в файл.\n");
		break;
	}
	default: { break; }
	}
}

//Сумма отрицательных двузначных элементов массива
int sum_of_negative_two_digit_nums(int* mas, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		if (mas[i] < -9 && mas[i] > -100) {
			sum += mas[i];
		}; //если элемент меньше -9, но больше -100 - суммируем
	}
	return sum;
}

//Все четные элементы массива разделить на 2
void divide_every_even_elem_by_two(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (mas[i] % 2 == 0) {
			mas[i] /= 2;
		} //если остаток от деления элемента =0, то делим
	}
}

//Удалить все элементы, меньшие суммы отрицательных двузначных элементов
void delete_elem(int* mas, int& size, int sum) // передаём по ссылке для того, чтоб изменить данные и повлиять на указатель
{

	for (int i = size - 1; i >= 0; i--)
	{
		if (mas[i] < sum)
		{
			for (int j = i + 1; j < size; j++)
			{
				mas[j - 1] = mas[j];
			}
			size--;
		}
	}

	/*
	int* new_mas = new int [j]; // создаём динамический массив
	for (int i = 0; i < size; i++) // переписываем массив
	{
	new_mas[i] = mas[i];
	}
	delete[] mas; // стёрли данные старого массива
	mas = new_mas; //направили указатель куда надо
	*/
}

//Вставить после каждого, кратного трем, элемента случайное число
void insert_elem(int* mas, int& size)
{
	for (int i = 0; i < size; i++)
	{
		if (mas[i] % 3 == 0)
		{
			printf("%d", mas[i]);
			for (int j = size - 1; j > i; j--)
			{
				mas[j + 1] = mas[j];
			}
			mas[i + 1] = rand() % (201) - 100;
			size++;
		}
	}
}