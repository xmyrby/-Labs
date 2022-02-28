/*Программа должна предоставить пользователю возможность выбора одного из двух способов заполнения массива: с клавиатуры или из текстового файла.
Заполнение массива каждым способом, вывод массива на экран и решение задач согласно варианту
из списка задач для самостоятельного решения необходимо оформить в виде отдельных подпрограмм.
Массивы и их длины передавать функциям необходимо через список аргументов, глобальные данные не использовать.
Ответ выводить на экран

Пусть задано N отрезков с помощью координат их концов.
Определить среднюю длину отрезков,
вывести номера отрезков, чьи длины больше средней.
Массивы и их длины передавать функциям необходимо через список аргументов*/

#include<iostream>

//Стуркута с длиной и координатами концов отрезка
struct segment
{
	double lenght, x1, y1, x2, y2;
};

//Пользователь вводит координаты отрезков
void UserSegment(segment* arr, int count)
{
	for (int i = 1; i <= count; i++)
	{
		printf("Введите координаты начала отрезка(через пробел X Y): ");
		scanf_s("%lf %lf", &arr[i].x1, &arr[i].y1);
		printf("Введите координаты конца отрезка(через пробел X Y):");
		scanf_s("%lf %lf", &arr[i].x2, &arr[i].y2);
	}
}

//Данные координат отрезков считываются из файла
void FileSegment(segment* arr, int& count)
{
	FILE* f;
	if (fopen_s(&f, "save.txt", "r") != 0) //проверка открылся ли файл
	{
		printf("could't open file save.txt!\n");
		exit(1);
	}
	fscanf_s(f, "%d", &count);
	for (int i = 0; i < count; i++)
	{
		fscanf_s(f, "%lf %lf %lf %lf", &arr[i].x1, &arr[i].y1, &arr[i].x2, &arr[i].y2);
	}
	fclose(f);//Закрываем файл
}

//Данные координат отрезков считываются из бинарного файла
void BinFileSegment(segment* arr, int& count)
{
	FILE* ft = NULL;
	if (fopen_s(&ft, "save.bin", "rb"))
	{
		printf("Ошибка чтения!");
		exit(1);
	}
	fread(&count, sizeof(int), 1, ft);
	fread(arr, sizeof(segment), count, ft);
	fclose(ft);
}

//Данные координат отрезков заполняются случайными числами. Пользователь сам выбирает промежуток случайных чисел.
void RandomSegment(segment* arr, int count)
{
	int min, max;
	printf("Введите минимальное число: ");
	scanf_s("%i", &min);
	printf("Введите максимальное число: ");
	scanf_s("%i", &max);
	for (int i = 0; i < count; i++)
	{
		arr[i].x1 = rand() % (max - min + 1) + min;
		arr[i].y1 = rand() % (max - min + 1) + min;
		arr[i].x2 = rand() % (max - min + 1) + min;
		arr[i].y2 = rand() % (max - min + 1) + min;
	}
}

//Считается длина отрезка относительно его координат
void LenghtSegment(segment* arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		arr[i].lenght = sqrt((arr[i].x2 - arr[i].x1) * (arr[i].x2 - arr[i].x1) + (arr[i].y2 - arr[i].y1) * (arr[i].y2 - arr[i].y1));
	}
}

//Считается средняя длина всех отрезков
void AverageLenghtSegment(segment* arr, int count, double& average_lenght)
{
	double sum_lenght = 0;
	for (int i = 0; i < count; i++)
	{
		sum_lenght += arr[i].lenght;
	}
	average_lenght = sum_lenght / count;
}

//Вывод на экран номера отрезко с длиной больше среднего и само значение средней длины
void PrintAverage(segment* arr, int count, double average_lenght)
{
	for (int i = 0; i < count; i++)
	{
		if (arr[i].lenght > average_lenght)
			printf("Отрезок под номером %i имеет длину больше средней.\n", i);
	}
	printf("Средняя длина %.3lf", average_lenght);
}

//Меню выбора способа ввода данных
void ChooseSwitch(int& trigger)
{
	do {
		printf("1 - Ввести данные из текстового файла.\n2 - Ввести данные из бинарного файла.\n3 - Ввести данные самостоятельно.\n4 - Случайные отрезки\nВыбор: ");
		scanf_s("%i", &trigger);
	} while (trigger < 1 || trigger>4);
}

//Пользователь вводит кол-во отрезков
void CountSegment(int& count)
{
	do
	{
		printf("Введите количество отрезков: ");
		scanf_s("%i", &count);
	} while (count < 0);
}

//Тело множественного выбора способа заполнения
void Switcher(segment* arr, int& count, int trigger)
{
	switch (trigger)
	{
	case 1:
	{
		FileSegment(arr, count);
		break;
	}
	case 2:
	{
		BinFileSegment(arr, count);
		break;
	}
	case 3:
	{
		UserSegment(arr, count);
		break;
	}
	case 4:
	{
		RandomSegment(arr, count);
		break;
	}
	default: break;
	}
}

//Сохранение данных в бинарный файл
void SaveBinFile(segment* arr, int count)
{
	FILE* f;
	if (fopen_s(&f, "save.bin", "w+"))
	{
		printf("Ошибка записи!");
		exit(1);
	}
	fwrite(&count, sizeof(int), 1, f);
	fwrite(arr, sizeof(segment), count, f);
	fclose(f);
}

void SaveFile(segment* arr, int count)
{
	FILE* f;
	if (fopen_s(&f, "save.txt", "w+") != 0)
	{
		printf("Ошибка записи!");
		exit(1);
	}
	fprintf_s(f, "%d\n", count);
	for (int i = 0; i < count; i++)
	{
		fprintf_s(f, "%lf %lf %lf %lf\n", arr[i].x1, arr[i].y1, arr[i].x2, arr[i].y2);
	}
	fclose(f);
}

int main()
{
	system("chcp 1251 > nul");
	int trigger = 0, count = 0;
	double average_lenght = 0;
	segment arr[100];
	ChooseSwitch(trigger);
	if (trigger > 2)
		CountSegment(count);
	Switcher(arr, count, trigger);
	LenghtSegment(arr, count);
	AverageLenghtSegment(arr, count, average_lenght);
	PrintAverage(arr, count, average_lenght);
	SaveBinFile(arr, count);
	SaveFile(arr, count);
}