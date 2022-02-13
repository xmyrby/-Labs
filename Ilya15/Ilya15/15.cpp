#include<iostream>

//Создание структуры
struct Product
{
	char Name[100];
	int Cost;
};

//Загрузка из файла
void input_file(Product* mas, int& size)
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
			fscanf_s(ft, "%s %d", &mas[i].Name, 100, &mas[i].Cost);
		fclose(ft);
	}
}

//Сохранение в файл
void output_file(Product* mas, int size)
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
			fprintf_s(f, "%s %d\n", mas[i].Name, mas[i].Cost);
		fclose(f);
	}
}

//Вывод массива
void printmas(Product* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s | Цена: %d\n", mas[i].Name, mas[i].Cost);
	}
}

//Ручное заполнение
void hand(Product* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("Ввод %d товара\nНазвание: ", i);
		scanf_s("%s\0", &mas[i].Name, 100);
		printf("Цена: ");
		scanf_s("%d", &mas[i].Cost);
	}
}

//Получение средней стоимости
double task(Product* mas, int size)
{
	double sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += mas[i].Cost;
		}
	return sum / size;
}

//Выбор способа
void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("Способы ввода:\n1 - с клавиатуры\n2 - из файла\nВыбор : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 2);
}

//Задание размера
void setsize(int& size)
{
	do
	{
		system("cls");
		printf("Введите количество товаров= ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

//Решение
void switcher(Product* mas, int& size, int type)
{
	switch (type)
	{
	case 1:
	{
		system("cls");
		hand(mas, size);
		break;
	}
	case 2:
	{
		system("cls");
		input_file(mas, size);
		break;
	}
	default:
		break;
	}
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	//Объявление переменных
	int type = 0, size = 0;
	Product mas[100];

	choosetype(type);

	if (type != 2)
		setsize(size);

	switcher(mas, size, type);

	system("cls");
	printmas(mas, size);

	printf("\nСредняя цена товаров = %.3lf", task(mas, size));

	output_file(mas, size);

	return 0;
}