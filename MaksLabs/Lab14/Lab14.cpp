#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
//���������� ���������� ��������� �������, ��������� �� ��������� ������������� ��������[X, Y].������� �� ���� �������� ��������� ������� ����� ���� ��������� �������.
void input_file(int* mas, int& size)
{
	FILE* ft;
	if (fopen_s(&ft, "save.txt", "rt") != 0)
	{
		printf("������ ������!");
		exit(1);
	}
	else
	{
		fscanf_s(ft, "%d", &size);

		for (int i = 0; i < size; i++)
			fscanf_s(ft, "%d", &mas[i]);
		fclose(ft);
	}
}

void output_file(int* mas, int size)
{
	FILE* f;

	if (fopen_s(&f, "save.txt", "wb") != 0)
	{
		printf("������ ������!");
		exit(1);
	}
	else
	{
		fprintf_s(f, "%d\n", size);
		for (int i = 0; i < size; i++)
			fprintf_s(f, "%d\n", mas[i]);
		fclose(f);
	}
}

void selffill(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("mas[%d] = ", i);
		scanf_s("%d", &mas[i]);
	}
}

void randfill(int* mas, int size)
{
	int start, end;
	do
	{
		system("cls");
		printf("������� ��������� ������� �������� = ");
		scanf_s("%d", &start);
		printf("������� �������� ������� �������� = ");
		scanf_s("%d", &end);
	} while (start > end);

	for (int i = 0; i < size; i++)
		mas[i] = rand() % (end - start + 1) + start;
}

void printmas(int mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("mas[%d] = %d\n", i, mas[i]);
	}
}

void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("������� �����:\n1 - � ����������\n2 - ���������� �������\n3 - �� �����\n����� : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 3);
}

void setsize(int& size)
{
	do
	{
		system("cls");
		printf("������� ������ ������� = ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

void setxy(int& x, int& y)
{
	do
	{
		system("cls");
		printf("������� x = ");
		scanf_s("%d", &x);
		printf("������� y = ");
		scanf_s("%d", &y);
	} while (x > y);
}

void switcher(int* mas, int& size, int type)
{
	switch (type)
	{
	case 1:
	{
		system("cls");
		selffill(mas, size);
		break;
	}
	case 2:
	{
		randfill(mas, size);
		break;
	}
	case 3:
	{
		input_file(mas, size);
		break;
	}
	default:
		break;
	}
}

int getsum(int mas[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += mas[i];
	}
	return sum;
}

int transform(int* mas, int size, int sum, int x, int y)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (mas[i] >= x && mas[i] <= y)
		{
			count++;
		}
		if (mas[i] % 2 != 0)
		{
			mas[i] -= sum;
		}
	}
	return count;
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	int type, size, x, y, sum;
	int mas[100];

	choosetype(type);

	if (type != 3)
		setsize(size);

	setxy(x, y);

	switcher(mas, size, type);

	system("cls");
	sum = getsum(mas, size);
	printf("�������� ������:\n");
	printmas(mas, size);

	printf("\n���������� ����� ������������� [X,Y] = %d\n", transform(mas, size, sum, x, y));

	printf("\n������ ����� ��������������:\n");
	printmas(mas, size);

	output_file(mas, size);

	return 0;
}