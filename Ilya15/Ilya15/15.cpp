#include<iostream>

//�������� ���������
struct Product
{
	char Name[100];
	int Cost;
};

//�������� �� �����
void input_file(Product* mas, int& size)
{
	FILE* ft;
	if (fopen_s(&ft, "save.txt", "rt") != 0)
	{
		printf("������ ������!");
		exit(1);
	}
	else
	{
		fscanf_s(ft, "%d", &size);

		for (int i = 0; i < size; i++)
			fscanf_s(ft, "%s %d", &mas[i].Name, 100, &mas[i].Cost);
		fclose(ft);
	}
}

//���������� � ����
void output_file(Product* mas, int size)
{
	FILE* f;

	if (fopen_s(&f, "save.txt", "w+") != 0)
	{
		printf("������ ������!");
		exit(1);
	}
	else
	{
		fprintf_s(f, "%d\n", size);
		for (int i = 0; i < size; i++)
			fprintf_s(f, "%s %d\n", mas[i].Name, mas[i].Cost);
		fclose(f);
	}
}

//����� �������
void printmas(Product* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s | ����: %d\n", mas[i].Name, mas[i].Cost);
	}
}

//������ ����������
void hand(Product* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		system("cls");
		printf("���� %d ������\n��������: ", i);
		scanf_s("%s\0", &mas[i].Name, 100);
		printf("����: ");
		scanf_s("%d", &mas[i].Cost);
	}
}

//��������� ������� ���������
double task(Product* mas, int size)
{
	double sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += mas[i].Cost;
		}
	return sum / size;
}

//����� �������
void choosetype(int& type)
{
	do
	{
		system("cls");
		printf("������� �����:\n1 - � ����������\n2 - �� �����\n����� : ");
		scanf_s("%d", &type);
	} while (type < 1 || type > 2);
}

//������� �������
void setsize(int& size)
{
	do
	{
		system("cls");
		printf("������� ���������� �������= ");
		scanf_s("%d", &size);
	} while (size <= 0 || size > 100);
}

//�������
void switcher(Product* mas, int& size, int type)
{
	switch (type)
	{
	case 1:
	{
		system("cls");
		hand(mas, size);
		break;
	}
	case 2:
	{
		system("cls");
		input_file(mas, size);
		break;
	}
	default:
		break;
	}
}

int main()
{
	system("chcp 1251 > nul");
	srand(time(NULL));

	//���������� ����������
	int type = 0, size = 0;
	Product mas[100];

	choosetype(type);

	if (type != 2)
		setsize(size);

	switcher(mas, size, type);

	system("cls");
	printmas(mas, size);

	printf("\n������� ���� ������� = %.3lf", task(mas, size));

	output_file(mas, size);

	return 0;
}