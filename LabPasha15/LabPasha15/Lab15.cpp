#include<iostream>

struct segment
{
	double lenght, x1, y1, x2, y2;
};

void UserSegment(segment* arr, int count)
{
	for (int i = 1; i <= count; i++)
	{
		printf("¬ведите координаты начала отрезка: ");
		scanf_s("%lf %lf", &arr[i].x1, &arr[i].y1);
		printf("¬ведите координаты конца отрезка:");
		scanf_s("%lf %lf", &arr[i].x2, &arr[i].y2);
	}
}

void FileSegment(segment* arr, int& count)
{
	FILE* f;
	if (fopen_s(&f, "1.txt", "r") != 0) //проверка открылс€ ли файл
	{
		printf("could't open file 1.txt!\n");
		exit(1);
	}
	while (!feof(f))
	{
		for (int i = 1; !feof(f); i++)
		{
			fscanf_s(f, "%lf %lf %lf %lf", &arr[i].x1, &arr[i].y1, &arr[i].x2, &arr[i].y2);
			count++;
		}
	}
	fclose(f);//«акрываем файл
}

void RandomSegment(segment* arr, int count)
{
	int min, max;
	printf("¬ведите минимальное число: ");
	scanf_s("%i", &min);
	printf("¬ведите макссимальное число: ");
	scanf_s("%i", &max);
	for (int i = 1; i <= count; i++)
	{
		arr[i].x1 = rand() % (max - min + 1) + min;
		arr[i].y1 = rand() % (max - min + 1) + min;
		arr[i].x2 = rand() % (max - min + 1) + min;
		arr[i].y2 = rand() % (max - min + 1) + min;
	}
}

void LenghtSegment(segment* arr, int count)
{
	for (int i = 1; i <= count; i++)
	{
		arr[i].lenght = sqrt((arr[i].x2 - arr[i].x1) * (arr[i].x2 - arr[i].x1) + (arr[i].y2 - arr[i].y1) * (arr[i].y2 - arr[i].y1));
	}
}

void AverageLenghtSegment(segment* arr, int count, double& average_lenght)
{
	double sum_lenght = 0;
	for (int i = 1; i <= count; i++)
	{
		sum_lenght += arr[i].lenght;
	}
	average_lenght = sum_lenght / count;
}

void PrintAverage(segment* arr, int count, double average_lenght)
{
	for (int i = 1; i <= count; i++)
	{
		if (arr[i].lenght > average_lenght)
			printf("ќтрезок под номером %i имеет длину больше средней.\n", i);
	}
	printf("—редн€€ длина %.3lf", average_lenght);
}

void ChooseSwitch(int& trigger)
{
	do {
		printf("1 - ¬вести данные из файла. 2 - ¬вести данные самосто€тельно. 3 - —лучайные отрезки\n");
		scanf_s("%i", &trigger);
	} while (trigger < 1 || trigger>3);
}

void CountSegment(int& count)
{
	do
	{
		printf("¬ведите количество отрезков: ");
		scanf_s("%i", &count);
	} while (count < 0);
}

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
		UserSegment(arr, count);
		break;
	}
	case 3:
	{
		RandomSegment(arr, count);
		break;
	}
	default: break;
	}
}

int main()
{
	system("chcp 1251");
	int trigger = 0, count = 0;
	double average_lenght = 0;
	segment arr[100];
	ChooseSwitch(trigger);
	if (trigger > 1)
		CountSegment(count);
	Switcher(arr, count, trigger);
	LenghtSegment(arr, count);
	AverageLenghtSegment(arr, count, average_lenght);
	PrintAverage(arr, count, average_lenght);
}