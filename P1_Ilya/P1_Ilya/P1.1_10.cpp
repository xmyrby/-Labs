// ��� ������ ������������ ��������� �����(������ ������� ���������� ������������, �� � ���������[3; 20]).���������� ����� ����� �� ���������[-5; 5]
#include <iostream>
//��������� ������� �������
void SetSize(int& s)
{
	do
	{
		system("cls");
		printf("input size = ");
		scanf_s("%d", &s);
	} while (s < 3 || s > 20); //�������� ��������� ��������
}
//���������� �������
void FillArr(double* arr, int s)
{
	printf("������:\n");
	for (int i = 0; i < s; i++)
	{
		arr[i] = (rand() % 2001 - 1000.0) / 10; // ��������� ���������� �����
		printf("%4.11f\n", arr[i]);
	}
}
//��������� ���������� ����� � ��������� [-5;5]
int GetCount(double* arr, int s)
{
	int count = 0;
	for (int i = 0; i < s; i++)
	{
		if (arr[i] >= -5 && arr[i] <= 5) // ��������, ��� ����� � ���������
			count++;
	}
	return count;
}

int main()
{
	system("chcp 1251");
	srand(time(0)); // ������������� ������������

	//���������� ����������
	int s = 3;
	double arr[20];

	SetSize(s); // ��������� ������� �������

	FillArr(arr, s); // ���������� �������

	printf("\n���������� = %d", GetCount(arr, s)); // ����� ���������� �����

	return 0;
}