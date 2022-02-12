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
void FillArr(int* arr1, int s)
{
	printf("������:\n");
	for (int i = 0; i < s; i++)
	{
		printf("a[%2d] = ", i);
		scanf_s("%d", &arr1[i]);
	}
}
//����� ���� ����������
void GetType(int& type)
{
	printf("�������� ��� �������:\n1 - ����� ��-��� � ���� �� ��������\n2 - ������������ ��-��� � ���� �� ��������\n3 - ������������� ��-�� �� ���� � ���� ��  ��������\n��� �����: ");
	do
	{
		scanf_s("%d", &type);
	} while (type < 1 || type > 3);
}

//��������� ������������� �����
int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

//��������� ������
void GetAnswer(int* arr1, int* arr2, int* arr3, int s, int type)
{
	for (int i = 0; i < s; i++)
	{
		switch (type)
		{
		case 1:
		{
			arr3[i] = arr1[i] + arr2[i];
			break;
		}
		case 2:
		{
			arr3[i] = arr1[i] * arr2[i];
			break;
		}
		case 3:
		{
			arr3[i] = Max(arr1[i], arr2[i]);
			break;
		}
		default:
			break;
		}
		printf("a[%d] = %d\n", i, arr3[i]);
	}
}

int main()
{
	system("chcp 1251");
	//���������� ����������
	int s = 3, type = 0, arr1[20], arr2[20], arr3[20];

	SetSize(s); //������ �������

	FillArr(arr1, s); //���������� ������� 1

	FillArr(arr2, s); //���������� ������� 2

	GetType(type); //����� ���� ����������

	GetAnswer(arr1, arr2, arr3, s, type); //��������� �����

	return 0;
}