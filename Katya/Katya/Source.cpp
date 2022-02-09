#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

/*��� ������� ������ �������� �������� ������������ ������������ ����������� ������ �������� ����� (� ����������, ��������� ����� �� ��������� �� � �� �,
�� �����). ��������� �������� �� �����. ���������� ������������ �������� ������ � ����. ��� ���������� ������� ���������� ������� � ������ ��� �� �����,
�������� ������ �� �����. ��� �������� ��� �������� ����������� � ���������������� ��������. ������ ������� ��������� � ��������� �������.

1. ����� ����� ������������� ���������� ��������� �������. ��� ������ �������� ������� ��������� �� 2. ������� ��� ��������, ������� �����
������������� ���������� ���������. �������� ����� �������, �������� ����, �������� ��������� �����.*/


//void - �� ���������� �������� ��������, "������"

void self_fill(int*, int); //���������� � ����������
void rand_fill(int*, int); //���������� ���������� ������� � ���������
void input_file(int*, int&); //���������� �� �����
void output_file(int*, int); //����� ������� � ����
void size_mass(int&); //������ �������
void print_mas(int[], int); //����� ������� �� �����
void input_type_mass(int&); //����� �������� ����������
void switcher(int*, int&, int); //���������� ������� � ����������� �� ���������� ��������
void output_mass(int*, int&, int); //����� �������
void massou_tput_type(int&); //����� �������� ������ �������
int sum_of_negative_two_digit_nums(int*, int); //����� ������������� ���������� ��������� �������
void divide_every_even_elem_by_two(int*, int); //��� ������ �������� ������� ��������� �� 2
void delete_elem(int*, int&, int); //������� ��� ��������, ������� ����� ������������� ���������� ���������
void insert_elem(int*, int&); //�������� ����� �������, �������� ����, �������� ��������� �����


int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	int type = 0, option = 0, size = 0;
	int mas[100];

	input_type_mass(type); //����� �������� ����������
	if (type != 3) {
		size_mass(size);
	} //������ ������� � ��� �������, ����� ���� �� �� �����
	switcher(mas, size, type); //���������� ������� � ����������� �� ���������� ��������

	system("cls"); //������� �����
	printf("�������� ������:\n");
	print_mas(mas, size);

	int sum = sum_of_negative_two_digit_nums(mas, size);
	divide_every_even_elem_by_two(mas, size);
	delete_elem(mas, size, sum);
	insert_elem(mas, size);

	massou_tput_type(option);
	output_mass(mas, size, option);

	return 0;
}

//���������� � ����������
void self_fill(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls"); //�������� �����
		printf("mas[%d] = ", i);
		scanf_s("%d", &mas[i]);
	}
}

//���������� ���������� ������� � ���������
void rand_fill(int* mas, int size)
{
	int min, max;
	do
	{
		system("cls");
		printf("������� ����������� ������� �������� = ");
		scanf_s("%d", &min);
		printf("������� ������������ ������� �������� = ");
		scanf_s("%d", &max);
	} while (min > max);

	for (int i = 0; i < size; i++)
		mas[i] = rand() % (max - min + 1) + min;
}

//���������� �� �����
void input_file(int* mas, int& size)
{
	FILE* ft;
	if (fopen_s(&ft, "file13.txt", "rt") != 0) //r - ������, t - ��������� ���� (�� ��� �� ���������)
	{
		printf("������ ������!");
		exit(1);
	}
	else
	{
		fscanf_s(ft, "%d", &size);

		for (int i = 0; i < size; i++)
			fscanf_s(ft, "%d", &mas[i]);
		fclose(ft);
	}
}

//����� ������� � ����
void output_file(int* mas, int size)
{
	FILE* f;

	if (fopen_s(&f, "file13.txt", "w+") != 0) //��� ������ � ������
	{
		printf("������ ������!");
		exit(1);
	}
	else
	{
		fprintf_s(f, "%d\n", size);
		for (int i = 0; i < size; i++)
			fprintf_s(f, "%d\n", mas[i]);
		fclose(f);
	}
}

//������ �������
void size_mass(int& size)
{
	do
	{
		system("cls");
		printf("������� ������ ������� (�� ������ 100):");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

//����� ������� �� �����
void print_mas(int mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("mas[%d] = %d\n", i, mas[i]);
	}
}

//����� �������� ����������
void input_type_mass(int& type)
{
	do
	{
		system("cls");
		printf("�������� ������ �����:\n1 - � ����������\n2 - ���������� �������\n3 - �� �����\n����� : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 3);
}

//���������� ������� � ����������� �� ���������� ��������
void switcher(int* mas, int& size, int type)
{
	switch (type)
	{
	case 1:
	{
		system("cls");
		self_fill(mas, size);
		break;
	}
	case 2:
	{
		rand_fill(mas, size);
		break;
	}
	case 3:
	{
		input_file(mas, size);
		break;
	}
	default: { break; }
	}
}

//����� �������� ������ �������
void massou_tput_type(int& option)
{
	do
	{
		printf("\n��� ������ ������� ������? \n 1 - �� �����\n 2 - � ����\n�����: ");
		scanf_s("%d", &option);
	} while (option < 1 || option > 2);
}

//����� �������
void output_mass(int* mas, int& size, int option)
{
	switch (option)
	{
	case 1:
	{
		printf("\n������ ����� ��������������:\n");
		print_mas(mas, size);
		break;
	}
	case 2:
	{
		output_file(mas, size);
		printf("\n������ ������� � ����.\n");
		break;
	}
	default: { break; }
	}
}

//����� ������������� ���������� ��������� �������
int sum_of_negative_two_digit_nums(int* mas, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		if (mas[i] < -9 && mas[i] > -100) {
			sum += mas[i];
		}; //���� ������� ������ -9, �� ������ -100 - ���������
	}
	return sum;
}

//��� ������ �������� ������� ��������� �� 2
void divide_every_even_elem_by_two(int* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (mas[i] % 2 == 0) {
			mas[i] /= 2;
		} //���� ������� �� ������� �������� =0, �� �����
	}
}

//������� ��� ��������, ������� ����� ������������� ���������� ���������
void delete_elem(int* mas, int& size, int sum) // ������� �� ������ ��� ����, ���� �������� ������ � �������� �� ���������
{

	for (int i = size - 1; i >= 0; i--)
	{
		if (mas[i] < sum)
		{
			for (int j = i + 1; j < size; j++)
			{
				mas[j - 1] = mas[j];
			}
			size--;
		}
	}

	/*
	int* new_mas = new int [j]; // ������ ������������ ������
	for (int i = 0; i < size; i++) // ������������ ������
	{
	new_mas[i] = mas[i];
	}
	delete[] mas; // ����� ������ ������� �������
	mas = new_mas; //��������� ��������� ���� ����
	*/
}

//�������� ����� �������, �������� ����, �������� ��������� �����
void insert_elem(int* mas, int& size)
{
	for (int i = 0; i < size; i++)
	{
		if (mas[i] % 3 == 0)
		{
			printf("%d", mas[i]);
			for (int j = size - 1; j > i; j--)
			{
				mas[j + 1] = mas[j];
			}
			mas[i + 1] = rand() % (201) - 100;
			size++;
		}
	}
}