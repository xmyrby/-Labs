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
	printf("\n������� ���-�� ����� �������: \n");
	mas.rows = AskSize();
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		printf("������� ���-�� ��������� ������: \n");
		int count_el_str = AskSize();
		mas.data[i] = (int*)malloc(sizeof(int) * (count_el_str + 1));
		mas.data[i][0] = count_el_str;
	}
}

//���������� �������
void FillArray(RaggedArray& mas)
{
	for (int i = 0; i < mas.rows; i++)
		for (int j = 1; j <= mas.data[i][0]; j++)
			mas.data[i][j] = rand() % 100;
}

//����� �������
void PrintArray(RaggedArray mas)
{
	system("cls");
	printf("������:\n\n");
	for (int i = 0; i < mas.rows; i++)
	{
		for (int j = 1; j <= mas.data[i][0]; j++)
			printf("%3i ", mas.data[i][j]);
		printf("\n");
	}
}

//���������� � ��������� ����
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

//������ ������� �� ���������� �����
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

//���������� � �������� ����
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

//������ ������� �� ��������� �����
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

void Switcher(RaggedArray& mas)
{
	int choose = NULL;
	do {
		printf("��������� ������:\n0-�������\n1-��������� ����\n2-�������� ����\n�����: ");
		scanf_s("%i", &choose);
	} while (0 > choose or choose > 2);

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