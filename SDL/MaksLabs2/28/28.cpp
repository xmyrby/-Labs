#include <iostream>

//���������� ������� ����������
void FillMatrix(double matrix[10][10], int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			printf("a[%d, %d] = ", i, j);
			scanf_s("%lf", &matrix[i][j]);
		}
}

//����� �������
void PrintMatrix(double matrix[10][10], int n)
{
	system("cls");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%4.1lf ", matrix[i][j]);
		printf("\n");
	}
}

//������� ������� �������
void SetSize(int& n)
{
	do
	{
		system("cls");
		printf("������� n (3-10): ");
		scanf_s("%d", &n);
	} while (n <= 2 || n > 10);
}

//�������� �� ��������������
bool Check(double matrix[10][10], int n)
{
	bool sim = true;
	for (int i = 1; i < n; i++)
		for (int j = 1; j < i; j++)
			if (matrix[i][j] != matrix[j][i])
				sim = false;
	return sim;
}

int main()
{
	system("chcp 1251 > nul");
	double matrix[10][10];
	int n;

	SetSize(n);

	printf("�������:\n");
	FillMatrix(matrix, n);

	PrintMatrix(matrix, n);
	
	if (Check(matrix, n))
		printf("������� �����������");
	else
		printf("������� �� �����������");

	return 0;
}