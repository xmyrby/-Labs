#include<iostream>
bool cortub(int arr[], int size)
{
	for (int j = 0; j < size - 1; j++)
	{
		for (int i = 0; i < size - 1 - j; i++)
			if (arr[i] < arr[i + 1])
			{
				int tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
	}
	return true;


}
int main()
{
	system("chcp 1251>nul");
	int max, l, a, b, n;
	const int N = 100;
	int mas[N];
	srand(time(0));
	printf("��� ������� ����� - 1, ��� ������� ������ �����...");
	scanf_s("%d", &a);
	do
	{
		printf("������� ���������� ��������� �������...");
		scanf_s("%d", &n);
	} while (n >= 100 || n <= 0);
	if (a == 1)
	{
		for (int i = 0; i < n; i++)
		{
			scanf_s("%d", &a);
			mas[i] = a;
		}
	}
	else
	{
		printf("������� ����������� ���������� ��������\n");
		scanf_s("%d", &a); // �������� ������������ ��������
		printf("������� ���������� ���������� ��������\n");
		scanf_s("%d", &b); // �������� ����������� ��������
		for (int i = 0; i < n; i++)
		{
			mas[i] = rand() % (a - b + 1) + b;
			printf("mas[%d] = %d\n", i, mas[i]);
		}
	}
	bool low = false;
	for (int i = 0; i < (N - 1); i++)
	{
		if (mas[i] > mas[i + 1])
		{
			low = true;
			break;
		}
	}

	if (low)
	{
		int start = 0, koef = 0;
		printf("������ �� �� ��������\n��������� ��������: ");
		scanf_s("%d", &start);
		printf("��������: ");
		scanf_s("%d", &koef);

		for (int i = 0; i < n; i++)
		{
			mas[i] = start + koef * i;
			printf("mas[%d] = %d\n", i, mas[i]);
		}
	}
}