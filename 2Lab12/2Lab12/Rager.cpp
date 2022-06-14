#include<Windows.h>
#include"Rager.h"

void CreateArraySelf(RaggedArray& mas)
{
	int count_rows = 0;
	printf("\nВведите кол-во строк массива: \n");
	scanf_s("%d", &count_rows);
	mas.rows = count_rows;
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		int count_el_str;
		printf("Введите кол-во элементов строки: \n");
		scanf_s("%d", &count_el_str);
		mas.data[i] = (int*)malloc(sizeof(int) * (count_el_str + 1));
		mas.data[i][-1] = count_el_str;
	}
}

//Заполнение массива
void FillArray(RaggedArray& mas)
{
	for (int i = 0; i < mas.rows; i++)
		for (int j = 0; j < mas.data[i][-1]; j++)
			mas.data[i][j] = rand() % 100;
}

//Вывод массива
void PrintArray(RaggedArray mas)
{
	for (int i = 0; i < mas.rows; i++)
	{
		for (int j = 0; j < mas.data[i][-1]; j++)
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
		for (int j = -1; j < mas.data[i][-1]; j++)
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
		mas.data[i][-1] = count_el_str;
		for (int j = 0; j < mas.data[i][-1]; j++)
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
		fwrite(&mas.data[i][-1], sizeof(int), 1, f);
		fwrite(mas.data[i], sizeof(int), mas.data[i][-1], f);
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
		mas.data[i][-1] = count_el_str;
		fread(mas.data[i], sizeof(int), mas.data[i][-1], f);
	}

	fclose(f);
}

int AddLine(RaggedArray& mas, int* line)
{
	mas.rows++;
	mas.data = (int**)realloc(mas.data, sizeof(int*) * mas.rows);
	mas.data[mas.rows - 1] = line;
	PrintArray(mas);
	return mas.rows;
}

void MakeLine(RaggedArray& mas)
{
	int count_el_str;
	int* line;
	printf("Введите кол-во элементов строки: \n");
	scanf_s("%d", &count_el_str);
	line = (int*)malloc(sizeof(int) * (count_el_str + 1));
	line[-1] = count_el_str;
	for (int i = 0; i < line[-1]; i++)
		line[i] = rand() % 100;
	AddLine(mas, line);
}

void AskForAdd(RaggedArray& mas)
{
	int choose = NULL;
	do {
		printf("Прочитать массив:\n0-Добавить новую строку\n1-закончить работу с массивом\nВыбор: ");
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
		printf("Прочитать массив:\n0-Создать\n1-текстовый файл\n2-бинарный файл\nВыбор: ");
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

void FreeMas(RaggedArray& mas)
{
	free(mas.data);

	mas.data = NULL;
}