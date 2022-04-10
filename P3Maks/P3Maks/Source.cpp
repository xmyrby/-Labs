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
		printf("%d ", mas[i]);
}

//���������� �������
void FillMas(int* mas, int n)
{
	for (int i = 0; i < n; i++)
		mas[i] = rand() % 5;
}

//���������� ���������
void Task(int* mas, int n)
{
	printf("\n������������������:\n");
	int times[5]{ 0,0,0,0,0 };
	for (int i = 0; i < n; i++)
	{
		times[mas[i]]++;
		for (int j = 0; j < times[mas[i]]; j++)
		{
			printf("%d ", mas[i]);
		}
	}
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

	Task(mas, n);

	return 0;
}