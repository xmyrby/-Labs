#include<iostream>
//7.    Выяснить, является ли число А членом арифметической прогрессии с шагом В и первым членом С.
int main()
{
	//Объявление переменных
	int a, b, c;

	//Ввод
	printf("Print a = ");
	scanf_s("%d", &a);
	printf("Print b = ");
	scanf_s("%d", &b);
	printf("Print c = ");
	scanf_s("%d", &c);

	//Прогрессия
	while (c < a)
	{
		c += b;
	}

	//Проверка и вывод
	if (c == a)
	{
		printf("yes");
	}
	else
	{
		printf("no");
	}

	return 0;
}