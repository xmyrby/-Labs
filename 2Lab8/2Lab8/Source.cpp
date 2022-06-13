//7. ������ ����������� ������������. ���������� �����
//������������ ����� �����������.���������� ��������� ������
//������������ ������������ ��������.
#include<iostream>
#include<Windows.h>

//����������
struct RaggedArray
{
	int** data;
	int rows;
	//int* cols = NULL;
};

//�������� �������
void CreateArraySelf(RaggedArray& mas, int count_el_str, int count_rows)
{
	printf("\n������� ���-�� ����� �������: \n");
	scanf_s("%d", &count_rows);
	mas.rows = count_rows;
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	//mas.cols = (int*)malloc(sizeof(int) * mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		printf("������� ���-�� ��������� ������: \n");
		scanf_s("%d", &count_el_str);
		//scanf_s("%i", &mas.cols[i]);
		mas.data[i] = (int*)malloc(sizeof(int) * (count_el_str + 1));
		mas.data[i][-1] = count_el_str;
	}
}

//�������� �������
void CreateArray(RaggedArray& mas, int count_el_str, int count_rows)
{
	mas.rows = count_rows;
	//mas.cols = (int*)malloc(sizeof(int) * mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		mas.data[i] = (int*)malloc(sizeof(int) * (count_el_str + 1));
		mas.data[i][-1] = count_el_str;
	}
}

//���������� �������
void FillArray(RaggedArray& mas)
{
	for (int i = 0; i < mas.rows; i++)
		for (int j = 0; j < mas.data[i][-1]; j++)
			mas.data[i][j] = rand() % 100;
}

//����� �������
void PrintArray(RaggedArray mas)
{
	for (int i = 0; i < mas.rows; i++)
	{
		for (int j = 0; j < mas.data[i][-1]; j++)
			printf("%3i ", mas.data[i][j]);
		printf("\n");
	}

	free(mas.data);
}

//���������� � ��������� ����
void SaveTxt(int count_el_str, int count_rows)
{
	FILE* f;
	if (fopen_s(&f, "save.txt", "w") != 0)
	{
		printf("Couldn't open file save.txt!\n");
		exit(1);
	}
	fprintf(f, "%i %i", count_el_str, count_rows);
	fclose(f);
}

//������ ������� �� ���������� �����
void ReadTxt(int& count_el_str, int& count_rows)
{
	FILE* f;
	if (fopen_s(&f, "save.txt", "r") != 0)
	{
		printf("Couldn't open file save.txt!\n");
		exit(1);
	}
	fscanf_s(f, "%i %i", &count_el_str, &count_rows);
	fclose(f);
}

//���������� � �������� ����
void SaveBin(int count_el_str, int count_rows)
{
	FILE* f;
	if (fopen_s(&f, "save.bin", "wb") != 0)
	{
		printf("Couldn't open file save.bin!\n");
		exit(1);
	}
	fwrite(&count_el_str, sizeof(int), 1, f);
	fwrite(&count_rows, sizeof(int), 1, f);
	fclose(f);
}

//������ ������� �� ��������� �����
void ReadBin(int count_el_str, int count_rows)
{
	FILE* f;
	if (fopen_s(&f, "save.bin", "rb") != 0)
	{
		printf("Couldn't open file save.bin!\n");
		exit(1);
	}
	fread(&count_el_str, sizeof(int), 1, f);
	fread(&count_rows, sizeof(int), 1, f);
	fclose(f);
}

void Switcher(int choose, RaggedArray mas, int count_el_str, int count_rows)
{
	do {
		printf("��������� ������:\n0-�������\n1-��������� ����\n2-�������� ����\n�����: ");
		scanf_s("%i", &choose);
	} while (0 > choose or choose > 3);

	switch (choose)
	{
	case 0:
	{
		CreateArraySelf(mas, count_el_str, count_rows);
		FillArray(mas);
		PrintArray(mas);
		SaveTxt(count_el_str, count_rows);
		SaveBin(count_el_str, count_rows);
		break;
	}
	case 1:
	{
		ReadTxt(count_el_str, count_rows);
		CreateArray(mas, count_el_str, count_rows);
		FillArray(mas);
		PrintArray(mas);
		SaveTxt(count_el_str, count_rows);
		SaveBin(count_el_str, count_rows);
		break;
	}
	case 2:
	{
		ReadBin(count_el_str, count_rows);
		CreateArray(mas, count_el_str, count_rows);
		FillArray(mas);
		PrintArray(mas);
		SaveTxt(count_el_str, count_rows);
		SaveBin(count_el_str, count_rows);
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

	int count_el_str = NULL, count_rows = NULL, choose = NULL;
	RaggedArray mas{};
	Switcher(choose, mas, count_el_str, count_rows);
	return 0;
}