#include <iostream>

//������� ������� �������
void SetSize(int& s)
{
	s = rand() % 5 + 5;
}

//���������� �������
void FillArr(double* arr, int s)
{
	printf("������ (������ - %d):\n", s);
	for (int i = 0; i < s; i++)
	{
		printf("a[%d] = ", i);
		scanf_s("%lf", &arr[i]);
	}
}

//����� �������� �������� ���������
void MoveIndexes(double* arr, int s)
{
	int count = s / 2 * 2;
	printf("\n������ ����� �������������:\n");
	for (int i = 0; i < count; i += 2)
	{
		double c = arr[i + 1];
		arr[i + 1] = arr[i];
		arr[i] = c;
	}
}

//����� ������ �������
void PrintArray(double* arr, int s)
{
	for (int i = 0; i < s; i++)
	{
		printf("%4.1lf\n", arr[i]);
	}
}

int main()
{
	system("chcp 1251");
	srand(time(0));
	//���������� ����������
	int s = 3;
	double arr[20];

	SetSize(s); //������ �������

	FillArr(arr, s); //���������� �������

	MoveIndexes(arr, s); //�������������� �������

	PrintArray(arr, s); //����� ������ �������

	return 0;
}