#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

//���������� ��������������
void selffill(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("mas[%d] = ", i);
		scanf_s("%d", &mas[i]);
	}
}

//���������� ���������� �������
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

//����� �������
void printmas(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("mas[%d] = %d\n", i, mas[i]);
	}
}

//����� �������
void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("������� �����:\n1 - � ����������\n2 - ���������� �������\n����� : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 2);
}

//������� �������
void setsize(int& size)
{
	do
	{
		system("cls");
		printf("������� ������ ������� = ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

//����������
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
	default:
		break;
	}
}

//������������� �������
int transform(int* mas, int size)
{
	int count = 0, min = 100000;
	for (int i = 0; i < size; i++)
	{
		if (mas[i] > 0 && mas[i] < min)
		{
			min = mas[i];
		}
		if (mas[i] * mas[i + 1] < 0)
		{
			count++;
		}
	}

	for (int i = 0; i < size; i++)
	{
		mas[i] *= min;
	}
	return count;
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	//���������� ���������
	int type, size;
	int mas[100];

	choosetype(type);

	setsize(size);

	switcher(mas, size, type);

	system("cls");
	printf("�������� ������:\n");
	printmas(mas, size);
	printf("\n���-�� ��������� �����: %d\n", transform(mas, size));

	printf("\n������ ����� ��������������:\n");
	printmas(mas, size);

	return 0;
}