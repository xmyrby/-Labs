#include <iostream>

//������� ������� �������
void SetSize(int& n)
{
	do
	{
		printf("������� ������ ������� (1-100): ");
		scanf_s("%d", &n);
	} while (n < 1 || n > 100);
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
		mas[i] = rand() % 2;
}

//��������� ������������ ����� �������
int Task(int* mas, int n)
{
	int max = 0, count = 0;
	for (int i = 0; i < n; i++)
	{
		if (mas[i] == 1)
			count++;
		else
		{
			if (count > max)
				max = count;
			count = 0;
		}
	}
	return max;
}

int main()
{
	system("chcp 1251 > nul");

	int mas[100];
	int n;

	srand(time(NULL));

	SetSize(n);

	FillMas(mas, n);

	PrintMas(mas, n);

	printf("\n������������ ����� ������� ������: %d\n",Task(mas,n));

	return 0;
}