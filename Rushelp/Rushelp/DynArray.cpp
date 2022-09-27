#include"DnyArray.h"
#include<stdlib.h>
#include"stdio.h"
#include<conio.h>

double** ConstructArray(int m, int* n)
{
	double** p = NULL;
	p = (double**)malloc(sizeof(double*) * m + sizeof(int));
	int* p1 = (int*)p;
	*p1 = m;
	p1++;
	p = (double**)p1;
	for (int i = 0; i < m; i++)
	{
		p[i] = (double*)malloc(n[i] * sizeof(double) + sizeof(int));
		p1 = (int*)p[i];
		*p1 = n[i];
		p1++;
		p[i] = (double*)p1;
		printf("Заполните строку №%d числами!Её длина равна=%d)\n", i + 1, n[i]);
		for (int j = 0; j < n[i]; j++)
		{
			scanf_s("%lf", &p[i][j]);

		}
	}
	return p;
}
void DestructArray(double** p)
{
	if (!p)
	{
		printf("Память особождалась раниее или не была занята\n");
		return;
	}
	int m;
	int* p1;
	p1 = (int*)p;
	m = p1[-1];
	for (int i = 0; i < m; i++)
	{
		int* p2 = (int*)p[i];
		p2--;
		free(p2);

	}
	p1--;
	free(p1);
	printf("Память отчистена\n");
}
void PrintArray(double** p)
{
	int n, m; // количество строк, столбцов
	int* p1;
	p1 = (int*)p;
	m = p1[-1];
	for (int i = 0; i < m; i++)
	{
		int* p2 = (int*)p[i];
		n = *(p2 - 1);
		printf("Длина строки №%d равна %d \n", i + 1, n);

		for (int j = 0; j < n; j++) printf("%-6.2lf", p[i][j]);
		printf("\n");
	}
}
void HandsArray(int& m, int n[100])
{
	do
	{
		printf("Введите кол-во строк (кол-во не может быть отрицательным числом)\n"); scanf_s("%d", &m);
		if (m < 0)
			printf("Кажется вы ввели отрицательное число!Попробуйте ещё раз\n");

	} while (m < 0);
	for (int i = 0; i < m; i++)
	{
		printf("Введите длину строки [%d](длина не может быть отрицательным числом:\n", i);
		do
		{
			scanf_s("%d", &n[i]);
			if (n[i] < 0)
				printf("Кажется вы ввели отрицательное число!Попробуйте ещё раз\n");
		} while (n[i] < 0);
	}
}
void inputfile(int& m, int n[100], Numbersforfile* s)
{
	FILE* f;
	if (fopen_s(&f, "readyarray.txt", "rt") != 0)
	{
		printf("Ошибка чтения!");
		exit(1);
	}
	else
	{
		fscanf_s(f, "%d", &m); int k = 0;
		if (m < 0)
		{
			printf("Кажется в файле кол-во строк равна отрицательному числу, проверьте и попробуйте еще раз\n");
			exit(2);
		}
		for (int i = 0; i < m; i++)
		{
			fscanf_s(f, "%d", &n[i]);
			if (n[i] < 0)
			{

				printf("Кажется в файле длина строки №%d равна отрицательному числу, проверьте и попробуйте еще раз\n", i + 1);
				exit(3);

			}
			for (int j = 0; j < n[i]; j++)
			{
				fscanf_s(f, "%lf", &s[k].numb[j]);
				k++;
			}
		}

	}
	fclose(f);
}
double** ConstructArrayfile(int m, int* n, Numbersforfile* s)
{
	double** p = NULL;
	p = (double**)malloc(sizeof(double*) * m + sizeof(int));
	int* p1 = (int*)p;
	*p1 = m;
	p1++;
	p = (double**)p1;
	int k = 0;
	for (int i = 0; i < m; i++)
	{
		p[i] = (double*)malloc(n[i] * sizeof(double) + sizeof(int));
		p1 = (int*)p[i];
		*p1 = n[i];
		p1++;
		p[i] = (double*)p1;
		for (int j = 0; j < n[i]; j++)
		{
			p[i][j] = s[k].numb[j];
			k++;
		}
	}
	return p;
}
void outputfile(double** p, int const m)
{
	FILE* ft;
	if (fopen_s(&ft, "finalarray.txt", "w+") != 0)
	{
		printf("Ошибка чтения!\n");
		exit(1);
	}
	else
	{
		fprintf(ft, "Кол строк=%d\n", m);
		int n, m; // количество строк, столбцов
		int* p1;
		p1 = (int*)p;
		m = p1[-1];
		for (int i = 0; i < m; i++)
		{
			int* p2 = (int*)p[i];
			n = *(p2 - 1);
			fprintf_s(ft, "Длина строки №%d равна %d \n", i + 1, n);

			for (int j = 0; j < n; j++) fprintf_s(ft, "%-6.2lf", p[i][j]);
			fprintf_s(ft, "\n");
		}
	}
	fclose(ft);
}
void inputfilebin(int& m, int n[100], Numbersforfile* s)
{
	FILE* f;
	if (fopen_s(&f, "finalarray.bin", "rb") != 0)
	{
		printf("Ошибка чтения!");
		exit(1);
	}
	else
	{
		fread(&m, sizeof(int), 1, f);
		if (m < 0)
		{
			printf("Кажется в файле кол-во строк равна отрицательному числу, проверьте и попробуйте еще раз\n");
			exit(2);
		}
		for (int i = 0; i < m; i++)
		{
			fread(&n[i], sizeof(int), 1, f);
			if (n[i] < 0)
			{

				printf("Кажется в файле длина строки №%d равна отрицательному числу, проверьте и попробуйте еще раз\n", i + 1);
				exit(3);

			}
			fread(&s[i].numb, sizeof(int), n[i], f);
		}

	}
	fclose(f);
}
void outputfilebin(double** p, int const m)
{
	FILE* ft;
	if (fopen_s(&ft, "finalarray.bin", "wb") != 0)
	{
		printf("Ошибка чтения!\n");
		exit(1);
	}
	else
	{
		fwrite(&m, sizeof(int), 1, ft);
		int n, m; // количество строк, столбцов
		int* p1;
		p1 = (int*)p;
		m = p1[-1];
		for (int i = 0; i < m; i++)
		{
			int* p2 = (int*)p[i];
			n = *(p2 - 1);
			for (int j = 0; j < n; j++) fwrite(&p[i][j], sizeof(double), 100, ft);

		}
	}
	fclose(ft);
}