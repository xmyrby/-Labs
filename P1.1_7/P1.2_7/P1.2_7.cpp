#include <iostream>
//���������� �������
void FillArr(double* arr)
{
	printf("������:\n");
	for (int i = 0; i < 15; i++)
	{
		arr[i] = (rand() % 201 - 100.0) / 10;
		printf("a[%2d] = %4.1f\n", i, arr[i]);
	}
}
//����� �����
void PrintNumbers(double* arr)
{
	int ind = 1;
	printf("\n�����:\n");
	for (int i = 0; i < 15; i++)
	{
		//��������
		if (i == ind)
		{
			printf("%4.1f [%2d]\n", arr[i], i);
			ind *= 2;
		}
	}
}

int main()
{
	system("chcp 1251");
	srand(time(0));
	//���������� �������
	double arr[15];
	//���������� �������
	FillArr(arr);
	//����� �����
	PrintNumbers(arr);

	return 0;
}