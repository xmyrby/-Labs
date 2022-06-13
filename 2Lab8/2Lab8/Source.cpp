//7. Массив представлен дескриптором. Количество строк
//определяется полем дескриптора.Количество элементов строки
//определяется терминальным символом.
#include<iostream>
#include<Windows.h>

//дескриптор
struct RaggedArray
{
	int** data;
	int rows;
};

//Создание массива
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

void FreeMas(RaggedArray& mas)
{
	free(mas.data);

	mas.data = NULL;
}

void Switcher(int choose, RaggedArray& mas)
{
	do {
		printf("Прочитать массив:\n0-Создать\n1-текстовый файл\n2-бинарный файл\nВыбор: ");
		scanf_s("%i", &choose);
	} while (0 > choose or choose > 3);

	switch (choose)
	{
	case 0:
	{
		CreateArraySelf(mas);
		FillArray(mas);
		PrintArray(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	case 1:
	{
		ReadTxt(mas);
		PrintArray(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	case 2:
	{
		ReadBin(mas);
		PrintArray(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	break;
	}
}

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(NULL));

	int choose = NULL;
	RaggedArray mas{};
	Switcher(choose, mas);
	return 0;
}