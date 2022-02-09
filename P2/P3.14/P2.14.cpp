#include <iostream>

//���������� ��������
struct Product
{
	char Name[100];
	int Cost;
};

//���������� �������
void FillHand(Product* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("���� %d ������\n��������: ", i+1);
		scanf_s("%s\0", &mas[i].Name, 100);
		printf("����: ");
		scanf_s("%d", &mas[i].Cost);
	}
}

//����� �������
void PrintMas(Product* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s | ����: %d\n", mas[i].Name, mas[i].Cost);
	}
}

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

//��������� �������� ��������
int GetAverage(Product* mas, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += mas[i].Cost;
	}
	return sum / size;
}

//��������� ���������� ������� ����� ���� ��������
int GetCount(Product* mas, int size, int average)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (mas[i].Cost < average)
			count++;
	}
	return count;
}

int main()
{
	system("chcp 1251 > nul");

	//���������� ����������
	int size = 0, average;
	Product mas[100];
	SetSize(size);
	FillHand(mas, size);
	system("cls");
	PrintMas(mas, size);

	average = GetAverage(mas, size);

	printf("\n������� ���� ������� = %d", average);

	printf("\n���������� ������� ����� ���� ��������: %d", GetCount(mas, size, average));

	return 0;
}