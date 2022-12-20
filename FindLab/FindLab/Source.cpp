#include<iostream>
#include <chrono>

//����� ������� � �������
void PrintMas(char mas[10][100], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("[%d] %s", i + 1, mas[i]);
		printf("\n\n");
	}
	printf("\n");
}

//������ ������ 1 (������� � ���������� �����, ���� ����� �� �������)
void Finder1(char mas[10][100], int size, char word[100])
{
	printf("\n\n������ 1\n");

	auto start = std::chrono::system_clock::now();

	for (int i = 0; i < size; i++)
	{
		int j = 0;
		while (mas[i][j] != '\0' && word[j] != '\0')
		{
			if (mas[i][j] != word[j])
				break;

			j++;
		}

		if (mas[i][j] == word[j])
		{
			printf("\n[%d] %s\n", i + 1, mas[i]);
		}
	}

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "������ �������: " << elapsed_seconds.count() * 10000 << std::endl;
}

//������ ������ 2 (����� ����� ���������� ����������)
void Finder2(char mas[10][100], int size, char word[100])
{
	printf("\n\n������ 2\n");

	auto start = std::chrono::system_clock::now();

	for (int i = 0; i < size; i++)
	{
		if (!strcmp(mas[i],word))
		{
			printf("\n[%d] %s\n", i + 1, mas[i]);
		}
	}

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "������ �������: " << elapsed_seconds.count()*10000 << std::endl;
}


//������� �������
void SetSize(int& size)
{
	do
	{
		printf("������� ������ ������� (�� 2 �� 10): ");
		scanf_s("%d", &size);
	} while (size <= 1 || size > 10);
	printf("\n");
}

//���������� �������
void FillMas(char mas[10][100], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("������� ������� �%d: ", i + 1);
		scanf_s("%s", &mas[i], 100);
	}
	printf("\n");
}

int choose()
{
	int t = 0;
	do
	{
		printf("�������� ������ ����������:\n1 - �����������\n2 - ���������� ���������\n�����: ");
		scanf_s("%d", &t);
	} while (t < 1 || t>2);
	return t;
}

int main()
{
	system("chcp 1251 > nul");

	int size;

	SetSize(size);
	char mas[10][100];
	FillMas(mas, size);

	PrintMas(mas, size);

	char word[100];
	printf("\n������� ����� ��� ������: ");
	scanf_s("%s", &word, 100);

	Finder1(mas, size, word);
	Finder2(mas, size, word);

	return 0;
}