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
		arr[i] = rand() % 201 - 100;
		printf("a[%2d] = %3d\n", i, arr[i]);
	}
}
//����� �������� ������ ���������
void PrintIndexes(int* arr, int s)
{
	printf("\n������� ������ ��-���:\n");
	for (int i = 0; i < s; i++)
	{
		//��������
		if (arr[i] % 2 == 0)
			printf("%3d\n", i);
	}
}

int main()
{
	system("chcp 1251");
	srand(time(0));
	//���������� ����������
	int s = 3, arr[20];

	SetSize(s); //������ �������

	FillArr(arr, s); //���������� �������

	PrintIndexes(arr, s); //����� ��������

	return 0;
}