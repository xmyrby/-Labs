#include<iostream>
#include <chrono>

//Вывод массива в консоль
void PrintMas(char mas[10][100], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("[%d] %s", i + 1, mas[i]);
		printf("\n\n");
	}
	printf("\n");
}

//Способ поиска 1 (Переход к следующему слову, если буквы не совпали)
void Finder1(char mas[10][100], int size, char word[100])
{
	printf("\n\nСпособ 1\n");

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
	std::cout << "Единиц времени: " << elapsed_seconds.count() * 10000 << std::endl;
}

//Способ поиска 2 (Поиск через встроенную библиотеку)
void Finder2(char mas[10][100], int size, char word[100])
{
	printf("\n\nСпособ 2\n");

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
	std::cout << "Единиц времени: " << elapsed_seconds.count()*10000 << std::endl;
}


//Задание размера
void SetSize(int& size)
{
	do
	{
		printf("Введите размер массива (От 2 до 10): ");
		scanf_s("%d", &size);
	} while (size <= 1 || size > 10);
	printf("\n");
}

//Заполнение массива
void FillMas(char mas[10][100], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("Введите элемент №%d: ", i + 1);
		scanf_s("%s", &mas[i], 100);
	}
	printf("\n");
}

int choose()
{
	int t = 0;
	do
	{
		printf("Выберите способ сортировки:\n1 - Пузырьковая\n2 - Сортировка вставками\nВыбор: ");
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
	printf("\nВведите слово для поиска: ");
	scanf_s("%s", &word, 100);

	Finder1(mas, size, word);
	Finder2(mas, size, word);

	return 0;
}