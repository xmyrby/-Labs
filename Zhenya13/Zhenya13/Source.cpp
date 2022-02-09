#include <iostream>
#include <ctime>

void printmas(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("a[%d] = %d\n", i, a[i]);
	}
}

int task(int* a, int n)
{
	int S = 0;

	for (int i = 0; i < n; i++)
	{
		if (a[i] % 2 != 0)
		{
			a[i] *= 3;
		}

		if (a[i] > 0)
		{
			S += a[i];
		}
	}
	return S;
}

void Hand(int* a, int n)
{
	printf("���� �������:\n");
	for (int i = 0; i < n; i++)
	{
		printf("a[%d] = ", i);
		scanf_s("%d", &a[i]);
	}
}

void Rand(int* a, int n)
{
	int A, B;
	srand(time(NULL));
	printf("A = ");
	scanf_s("%d", &A);
	printf("B = ");
	scanf_s("%d", &B);
	printf("������:\n");
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % (B - A + 1) + A;
	}
}

int getN()
{
	int n = 0;
	do
	{
		printf("������� ���-�� ��������� ������� (�� ����� 100) - ");
		scanf_s("%d", &n);

		if (n < 1) // �������� ���������� ���-�� ��������� �������
		{
			printf("����������� ���-�� ���������.");
		}
		if (n > 100) // �������� ���������� ���-�� ��������� �������
		{
			printf("������� ����� ���������!");
		}

	} while (n <= 0 || n > 100);
	return n;
}

int main()
{
	int a[100], n;

	system("chcp 1251>nul");

	int way;

	// �������� �����
	do
	{
		system("cls");
		printf("�������� ������ ������� ����� �������:\n1 - ������ �������� ���������������\n2 - ���������� ����������\n�����: ");
		scanf_s("%d", &way);
	} while (way > 2 || way < 1);

	n = getN();
	// �������� �������������� ������
	switch (way)
	{
	case 1:
	{
		Hand(a, n);
		break;
	}
	case 2:
	{
		Rand(a, n);
		printmas(a, n);
		break;
	}
	default:
		break;
	}

	printf("����� ���� ������������� ��������� ������� S=%d\n������ ����� ���������: \n", task(a, n));
	printmas(a, n);

	return 0;
}