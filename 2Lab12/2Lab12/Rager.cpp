#include<Windows.h>
#include"Rager.h"

int AskSize()
{
	int size = 0;
	do
	{
		scanf_s("%d", &size);
	} while (size <= 0 || size > 15);
	return size;
}

void CreateArraySelf(RaggedArray& mas)
{
	printf("\nВведите кол-во строк массива: \n");
	mas.rows = AskSize();
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		printf("Введите кол-во элементов строки: \n");
		int count_el_str = AskSize();
		mas.data[i] = (int*)malloc(sizeof(int) * (count_el_str + 1));
		mas.data[i][0] = count_el_str;
	}
}

//Заполнение массива
void FillArray(RaggedArray& mas)
{
	for (int i = 0; i < mas.rows; i++)
		for (int j = 1; j <= mas.data[i][0]; j++)
			mas.data[i][j] = rand() % 100;
}

//Вывод массива
void PrintArray(RaggedArray mas)
{
	system("cls");
	printf("Массив:\n\n");
	for (int i = 0; i < mas.rows; i++)
	{
		for (int j = 1; j <= mas.data[i][0]; j++)
			printf("%3i ", mas.data[i][j]);
		printf("\n");
	}
}

//Сохранение в текстовый файл
void SaveTxt(RaggedArray mas)
{
	FILE* f;
	if (fopen_s(&f, "save.txt", "w") != 0)
	{
		printf("Couldn't open file save.txt!\n");
		exit(1);
	}
	fprintf(f, "%i\n", mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		for (int j = 0; j <= mas.data[i][0]; j++)
			fprintf(f, "%i ", mas.data[i][j]);
		fprintf(f, "\n");
	}
	fclose(f);
}

//Чтение массива из текстового файла
void ReadTxt(RaggedArray& mas)
{
	FILE* f;
	if (fopen_s(&f, "save.txt", "r") != 0)
	{
		printf("Couldn't open file save.txt!\n");
		exit(1);
	}
	fscanf_s(f, "%i", &mas.rows);
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		int count_el_str;
		fscanf_s(f, "%i", &count_el_str);
		mas.data[i] = (int*)malloc(sizeof(int) * (count_el_str + 1));
		mas.data[i][0] = count_el_str;
		for (int j = 1; j <= mas.data[i][0]; j++)
		{
			fscanf_s(f, "%i", &mas.data[i][j]);
		}
	}
	fclose(f);
}

//Сохранение в бинарный файл
void SaveBin(RaggedArray& mas)
{
	FILE* f;
	if (fopen_s(&f, "save.bin", "wb") != 0)
	{
		printf("Couldn't open file save.bin!\n");
		exit(1);
	}
	fwrite(&mas.rows, sizeof(int), 1, f);
	for (int i = 0; i < mas.rows; i++)
	{
		fwrite(mas.data[i], sizeof(int), mas.data[i][0] + 1, f);
	}

	fclose(f);
}

//Чтение массива из бинарного фалйа
void ReadBin(RaggedArray& mas)
{
	FILE* f;
	if (fopen_s(&f, "save.bin", "rb") != 0)
	{
		printf("Couldn't open file save.bin!\n");
		exit(1);
	}
	fread(&mas.rows, sizeof(int), 1, f);
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		int count_el_str;
		fread(&count_el_str, sizeof(int), 1, f);

		mas.data[i] = (int*)malloc(sizeof(int) * (count_el_str + 1));
		mas.data[i][0] = count_el_str;
		fread(&mas.data[i][1], sizeof(int), mas.data[i][0], f);
	}

	fclose(f);
}

void FreeMas(RaggedArray& mas)
{
	for (int i = 0; i < mas.rows; i++)
	{
		free(mas.data[i]);
	}

	free(mas.data);

	mas.data = NULL;
}

int AddLine(RaggedArray& mas, int* line)
{
	mas.rows++;
	mas.data = (int**)realloc(mas.data, sizeof(int*) * mas.rows);
	mas.data[mas.rows - 1] = line;
	return mas.rows;
}

void MakeLine(RaggedArray& mas)
{
	printf("Введите кол-во элементов строки: \n");
	int count_el_str = AskSize();
	int* line;
	line = (int*)malloc(sizeof(int) * (count_el_str + 1));
	line[0] = count_el_str;
	for (int i = 1; i <= line[0]; i++)
		line[i] = rand() % 100;
	int newSize = AddLine(mas, line);
	PrintArray(mas);
	printf("\nНовое количество строк: %i\n", newSize);

	AskForAdd(mas);
}

void AskForAdd(RaggedArray& mas)
{
	int choose = NULL;
	do {
		printf("\nПродолжение:\n0-Добавить новую строку\n1-Закончить работу с массивом\nВыбор: ");
		scanf_s("%i", &choose);
	} while (0 > choose or choose > 1);

	switch (choose)
	{
	case 0:
	{
		MakeLine(mas);
		//void* realloc(void* ptr, size_t size)
		break;
	}
	break;
	}
}

void Switcher(RaggedArray& mas)
{
	int choose = NULL;
	do {
		printf("Прочитать массив:\n0-Создать\n1-Текстовый файл\n2-Бинарный файл\nВыбор: ");
		scanf_s("%i", &choose);
	} while (0 > choose or choose > 2);

	switch (choose)
	{
	case 0:
	{
		CreateArraySelf(mas);
		FillArray(mas);
		PrintArray(mas);
		AskForAdd(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	case 1:
	{
		ReadTxt(mas);
		PrintArray(mas);
		AskForAdd(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	case 2:
	{
		ReadBin(mas);
		PrintArray(mas);
		AskForAdd(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	break;
	}
}