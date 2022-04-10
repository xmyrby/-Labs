#include <iostream>

//������� ������� �������
void SetSize(int& n)
{
	do
	{
		printf("������� ������ ������� (2-100): ");
		scanf_s("%d", &n);
	} while (n < 2 || n > 100);
	system("cls");
}

//����� �������
void PrintMas(int* mas, int n)
{
	printf("������:\n");
	for (int i = 0; i < n; i++)
		printf("a[%d] = %d\n", i + 1, mas[i]);
}

//���������� �������
void FillMas(int* mas, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("������� %d ������� �������: ", i + 1);
		scanf_s("%d", &mas[i]);
	}
	system("cls");
}

//������������ ������������ � ������������� ��������� � ��������� �����
int Task1(int* mas, int n)
{
	int mini, maxi, min = 1000, max = -1000;
	for (int i = 0; i < n; i++)
	{
		if (min > mas[i])
		{
			min = mas[i];
			mini = i;
		}
		else if (max < mas[i])
		{
			max = mas[i];
			maxi = i;
		}
	}

	mas[maxi] = min;
	mas[mini] = max;

	if (mini > maxi)
	{
		int c = maxi;
		maxi = mini;
		mini = c;
	}

	PrintMas(mas, n);

	int sum = 0;
	for (int i = mini + 1; i < maxi; i++)
	{
		sum += mas[i];
	}

	return sum;
}

//����� ������� �������������� ��������
void Task2(int* mas, int n)
{
	bool found = false;
	for (int i = 0; i < n; i++)
		if (mas[i] >= 0)
		{
			printf("������ ������������� ������� � ������� %d = %d\n", i + 1, mas[i]);
			found = true;
			break;
		}

	if (!found)
		printf("������������� ��������� ���\n");
}

int main()
{
	system("chcp 1251 > nul");

	int mas[100];
	int n;

	SetSize(n);

	FillMas(mas, n);

	PrintMas(mas, n);

	printf("����� ����� ����� ������������ � ����������� = %d\n", Task1(mas, n));

	Task2(mas, n);

	return 0;
}