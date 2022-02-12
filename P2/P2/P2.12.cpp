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
void FillArr(int* arr1, int s, int& otr)
{
	printf("������:\n");
	for (int i = 0; i < s; i++)
	{
		arr1[i] = rand() % 201 - 100;
		printf("a[%2d] = %3d\n", i, arr1[i]);
		if (arr1[i] < 0)
			otr++;
	}
}

//���������� ������� �������
void Refill(int* arr1, int* arr2, int s, int otr)
{
	int po = 0, ot = 0;

	for (int i = 0; i < s; i++)
	{
		if (arr1[i] < 0)
		{
			arr2[ot] = arr1[i];
			ot++;
		}
		else
		{
			arr2[otr + po] = arr1[i];
			po++;
		}
	}
}
//����� �������
void PrintMas(int* arr2, int s)
{
	printf("\n����� ������:\n");
	for (int i = 0; i < s; i++)
		printf("a[%2d] = %3d\n", i, arr2[i]);
}

int main()
{
	system("chcp 1251");
	srand(time(0));
	//���������� ����������
	int s = 3, otr = 0, arr1[20], arr2[20];

	SetSize(s); //������ �������

	FillArr(arr1, s, otr); //���������� �������

	Refill(arr1, arr2, s, otr); //���������� ������� �������

	PrintMas(arr2, s); //����� ������� �������

	return 0;
}