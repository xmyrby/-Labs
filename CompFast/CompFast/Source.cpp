#include<iostream>

//Вывод массива в консоль
void PrintMas(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", mas[i]);
	}
	printf("\n");
}

//Перенос в один массиив
int* WayDif(int* mas0, int* mas1, int sizes[2])
{
	int size = sizes[0] + sizes[1];
	int* mas = (int*)malloc(sizeof(int) * size);
	int comps = 0;

	int st0 = 0, st1 = 0;

	//Упорядоченный перенос в 1 массив значений всех массивов
	for (int i = 0; i < size; i++)
	{
		if (mas0[st0] > mas1[st1])
		{
			mas[i] = mas0[st0];
			st0++;
		}
		else
		{
			mas[i] = mas1[st1];
			st1++;
		}
		comps++;
	}

	printf("\nКомпарсий: %d\n\n", comps);

	return mas;
}

//Заполнение массивов
void FillMas(int* mas0, int* mas1, int* sizes)
{
	FILE* ft;
	if (fopen_s(&ft, "c.txt", "rt") != 0)
	{
		exit(1);
	}
	fscanf_s(ft, "%d", &sizes[0]);
	for (int i = 0; i < sizes[0]; i++)
		fscanf_s(ft, "%d", &mas0[i]);
	fclose(ft);

	if (fopen_s(&ft, "d.txt", "rt") != 0)
	{
		exit(1);
	}
	fscanf_s(ft, "%d", &sizes[1]);
	for (int i = 0; i < sizes[1]; i++)
		fscanf_s(ft, "%d", &mas1[i]);
	fclose(ft);
}

//Запись в файл
void SaveMas(int* mas, int size)
{
	FILE* ft;
	if (fopen_s(&ft, "f.txt", "w+") != 0)
	{
		exit(1);
	}
	fprintf(ft, "%d\n", size);
	for (int i = 0; i < size; i++)
		fprintf(ft, "%d\n", mas[i]);
	fclose(ft);
}

int main()
{
	system("chcp 1251 > nul");

	int sizes[2];

	//Создание массивов и выделение размера в памяти

	int mas0[100];
	int mas1[100];

	FillMas(mas0, mas1, sizes);

	//Вывод массивов0
	PrintMas(mas0, sizes[0]);
	PrintMas(mas1, sizes[1]);

	int* mas = WayDif(mas0, mas1, sizes);

	PrintMas(mas, sizes[0] + sizes[1]);

	SaveMas(mas, sizes[0] + sizes[1]);

	return 0;
}