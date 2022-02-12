#include <iostream>

//������� ������� �������
void SetSize(int& s)
{
	do
	{
		system("cls");
		printf("������� ������ ������� (�� 3 �� 20) = ");
		scanf_s("%d", &s);
	} while (s < 3 || s > 20);
}

//���������� �������
void FillArr(int* arr, int s)
{
	printf("������:\n");
	for (int i = 0; i < s; i++)
	{
		printf("a[%2d] = ", i);
		scanf_s("%d", &arr[i]);
	}
}

//��������� ������������� �����
void GetMax(int* arr, int s, int& max)
{
	for (int i = 0; i < s; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
}

//��������� ������������ �����
void GetMin(int* arr, int s, int& min)
{
	for (int i = 0; i < s; i++)
	{
		if (arr[i] < min)
			min = arr[i];
	}
}
//����� ���� ����������
void GetType(int& type)
{
	printf("�������� ��� �������:\n1 - ������ ����� � ����������� ���������\n2 - ������ ����� � ������������ ���������\n��� �����: ");
	do
	{
		scanf_s("%d", &type);
	} while (type < 1 || type > 2);
}

//����� ������
void Answer(int* arr, int s, int type, int min, int max)
{
	printf("\n������� = %d\n�������� = %d\n", min, max);
	printf("\n������ ���������:\n");
	for (int i = 0; i < s; i++)
	{
		switch (type)
		{
		case 1:
		{
			if (arr[i] == min)
				printf("%d\n", i + 1);
			break;
		}
		case 2:
		{
			if (arr[i] == max)
				printf("%d\n", i + 1);
			break;
		}
		default:
			break;
		}
	}
}

int main()
{
	system("chcp 1251");
	//���������� ����������
	int s = 3, type = 0, min = 10000, max = -10000, arr[20];

	SetSize(s); //������ �������

	FillArr(arr, s); //���������� �������

	GetType(type);

	GetMax(arr, s, max);

	GetMin(arr, s, min);

	Answer(arr, s, type, min, max); //��������� �����

	return 0;
}