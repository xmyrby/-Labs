#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <windows.h>

//��������� ����
struct Sums
{
	int sums[100];
	int indexes[100];
};

//��������� ���� ��������� �����
Sums getSums(int mas[100][100], int sizei, int sizej)
{
	Sums sums;

	for (int i = 0; i < sizei; i++)
	{
		sums.sums[i] = 0;
		sums.indexes[i] = i;
		for (int j = 0; j < sizej; j++)
			if (mas[i][j] % 2 == 0 && mas[i][j] >= 0)
				sums.sums[i] += mas[i][j];
	}
	return sums;
}

//�������� �� ���������� �����
void input_file(int mas[100][100], int& sizei, int& sizej)
{
	FILE* ft;
	if (fopen_s(&ft, "save.txt", "rt") != 0)
	{
		printf("\n������ ������ txt!");
		exit(1);
	}
	fscanf_s(ft, "%d", &sizei);
	fscanf_s(ft, "%d", &sizej);

	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			fscanf_s(ft, "%d", &mas[i][j]);
	fclose(ft);
}

//�������� �� bin �����
void input_bin(int mas[100][100], int& sizei, int& sizej)
{
	FILE* ft = NULL;
	if (fopen_s(&ft, "save.bin", "rt"))
	{
		printf("\n������ ������ bin!");
		exit(1);
	}
	fread(&sizei, sizeof(int), 1, ft);
	fread(&sizej, sizeof(int), 1, ft);

	for (int i = 0; i < sizei; i++)
		fread(mas[i], sizeof(int), sizej, ft);
	fclose(ft);
}

//���������� � ��������� ����
void output_file(int mas[100][100], int sizei, int sizej)
{
	FILE* f;

	if (fopen_s(&f, "save.txt", "r+b") != 0)
	{
		printf("\n������ ������ txt!");
		exit(1);
	}
	fprintf_s(f, "%d\n", sizei);
	fprintf_s(f, "%d\n", sizej);
	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			fprintf_s(f, "%d\n", mas[i][j]);
	fclose(f);
}

//���������� � bin ����
void output_bin(int mas[100][100], int sizei, int sizej)
{
	FILE* f;

	if (fopen_s(&f, "save.bin", "w+"))
	{
		printf("\n������ ������ bin!");
		exit(1);
	}
	fwrite(&sizei, sizeof(int), 1, f);
	fwrite(&sizej, sizeof(int), 1, f);
	for (int i = 0; i < sizei; i++)
		fwrite(mas[i], sizeof(int), sizej, f);
	fclose(f);
}

//���������� ���������� �������
void randfill(int mas[100][100], int sizei, int sizej)
{
	int err = 0;
	int start, end;
	do
	{
		system("cls");
		if (err)
			printf("�������� ����!\n");
		err = 1;
		printf("������� ��������� ������� �������� = ");
		scanf_s("%d", &start);
		printf("������� �������� ������� �������� = ");
		scanf_s("%d", &end);
	} while (start >= end);

	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			mas[i][j] = (rand() % (end - start + 1) + start);
}

//��������� ������������ ��������� �����, �� ���������� ������������� ����������
int getRowPro(int mas[100][100], int i, int sizej)
{
	int pro = 1;
	int otr = 0;
	for (int j = 0; j < sizej; j++)
		if (mas[i][j] < 0)
			otr++;
	if (!otr)
		for (int j = 0; j < sizej; j++)
			pro *= mas[i][j];
	else
		return 0;
	return pro;
}

//��������� ������� ������������� ����� � ����������
void getMaxDiagInd(int mas[100][100], int sizei, int sizej, int& im, int& jm)
{
	if (sizei != sizej)
		return;

	int max = -1000;

	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			if (i != j && mas[i][j] > max)
			{
				max = mas[i][j];
				im = i;
				jm = j;
			}
}

//�������� ������� �� ���������� � �� ������� ���������
int CheckCol(int mas[100][100], int sizei, int j)
{
	int zero = 0;
	for (int i = 0; i < sizei; i++)
		if (mas[i][j] == 0)
			zero++;
	if (!zero)
		return 1;
	return 0;
}

//����� ������� � ���������� �����
void printmas(int mas[100][100], int sizei, int sizej, int stage)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	Sums sums = getSums(mas, sizei, sizej);
	int im = -1, jm = -1;
	printf("������:\n");
	if (stage == 0)
		getMaxDiagInd(mas, sizei, sizej, im, jm);

	for (int i = 0; i < sizei; i++)
	{
		for (int j = 0; j < sizej; j++)
		{
			if (im == i && jm == j)
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
			if (j == i && stage == 0 && sizei == sizej)
				SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
			printf("%6d", mas[i][j]);
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}

		if (sums.sums[i] > 0)
			printf("	: ����� %5d", sums.sums[i]);
		if (stage == 0)
		{
			int pro = getRowPro(mas, i, sizej);
			if (pro)
				printf("	: ������������ %5d", pro);
		}
		printf("\n");
	}

	if (stage == 0)
	{
		for (int j = 0; j < sizej; j++)
		{
			int check = CheckCol(mas, sizei, j);
			if (check)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
				printf("     ^");
			}
			else
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				printf("     *");
			}
		}
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	printf("\n");
}

//����� ������� ����������
void choosetype(int& type)
{
	int err = 0;
	do
	{
		system("cls");
		if (err)
			printf("�������� ����!\n");
		err = 1;
		printf("������� �����:\n1 - ���������� �������\n2 - �� �����\n3 - �� ��������� �����\n����� : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 3);
}

//������� ������� �������
void setsize(int& sizei, int& sizej)
{
	int err = 0;
	do
	{
		system("cls");
		if (err)
			printf("�������� ����!\n");
		err = 1;
		printf("������� ������ ������� i = ");
		scanf_s("%d", &sizei);
	} while (sizei <= 0 || sizei > 100);
	err = 0;
	do
	{
		system("cls");
		if (err)
			printf("�������� ����!\n");
		err = 1;
		printf("������� ������ ������� j = ");
		scanf_s("%d", &sizej);
	} while (sizej <= 0 || sizej > 100);
}

//���������� �������
void switcher(int mas[100][100], int& sizei, int& sizej, int type)
{
	switch (type)
	{
	case 1:
	{
		randfill(mas, sizei, sizej);
		break;
	}
	case 2:
	{
		input_file(mas, sizei, sizej);
		break;
	}
	case 3:
	{
		input_bin(mas, sizei, sizej);
		break;
	}
	default:
		break;
	}
}

//��������� ���������� �������, �� ���������� ������� ���������
int getCol(int mas[100][100], int sizei, int sizej)
{
	int count = 0;
	for (int j = 0; j < sizej; j++)
	{
		int zero = 0;
		for (int i = 0; i < sizei; i++)
			if (mas[i][j] == 0)
				zero++;
		if (!zero)
			count++;
	}
	return count;
}

//���������� ����� �� ������
void moveRows(int mas[100][100], int sizei, int sizej)
{
	Sums sums = getSums(mas, sizei, sizej);
	int mas2[100][100];

	int moved = 0, iter = sizei - 1;
	do
	{
		moved = 0;
		for (int i = 0; i < iter; i++)
		{
			if (sums.sums[i] > sums.sums[i + 1])
			{
				int c = sums.sums[i];
				sums.sums[i] = sums.sums[i + 1];
				sums.sums[i + 1] = c;

				c = sums.indexes[i];
				sums.indexes[i] = sums.indexes[i + 1];
				sums.indexes[i + 1] = c;

				moved++;
			}
		}
		iter--;
	} while (moved);

	for (int s = 0; s < sizei; s++)
		for (int j = 0; j < sizej; j++)
			mas2[s][j] = mas[sums.indexes[s]][j];
	printmas(mas2, sizei, sizej, 1);
}

//��������� ������������� ����� ����������
void getMaxDiag(int mas[100][100], int sizei, int sizej)
{
	if (sizei != sizej)
		return;

	int max = -1000;

	for (int i = 0; i < sizei; i++)
		for (int j = 0; j < sizej; j++)
			if (i != j && mas[i][j] > max)
				max = mas[i][j];

	printf("�������� ����� ��������� ����������, ������������ ������� = %d\n\n", max);
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	int type = 0, sizei = 0, sizej = 0, max = 0, index = 0;
	int mas[100][100];

	choosetype(type);

	if (type == 1)
		setsize(sizei, sizej);

	switcher(mas, sizei, sizej, type);
	system("cls");
	printmas(mas, sizei, sizej, 0);
	int a = getRowPro(mas, sizei, sizej);
	printf("\n������� �� ���������� ������� ��-��� = %d\n", getCol(mas, sizei, sizej));
	getMaxDiag(mas, sizei, sizej);
	moveRows(mas, sizei, sizej);
	output_file(mas, sizei, sizej);
	output_bin(mas, sizei, sizej);

	return 0;
}