/*��� ������ ������������ ��������� ����� (������ ������� ���������� ������������, �� � ��������� [3;20]). �������, ����������� �� ����� � ������� �� 
�����������.*/
//�� �����. ��� ���������
#include<iostream>

void SetSize(int& size)
{
	do
	{
		printf("������� ����� ������� �� 3 �� 20: ");
		scanf_s("%i", &size);
	} while (size < 3 || size>20);
}

void RandomArray(int size, double* arr)
{
	printf("Array:\n");
	for (int i = 0; i < size; i++)
	{
		arr[i] = (rand() % 201- 100.0)/10;
		printf("%3.1lf\n", arr[i]);
	}
}

void SequenceArray(int size,double* arr)
{
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("������ �� ���������� �� �����������"); break;
	}
	}
}

/*void PrintArray(int size, double* arr)
{
	for (int i = 1; i < size; i++)
		printf("%d\n", arr[i]);
}
*/
int main()
{
	system("chcp 1251");
	srand(time(0));
	double arr[20];int size = 3;
	SetSize(size);
	RandomArray(size, arr);

	SequenceArray(size, arr);
}
