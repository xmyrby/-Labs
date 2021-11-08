#include<iostream>
//7.    Дано целое положительное число.Определить максимальную цифру в его записи
int main()
{
	//Объявление переменных
	int a, m = 0;

	//Ввод
	printf("Print number = ");
	scanf_s("%d", &a);

	//Получение числа
	while (a > 0)
	{
		m = m < a % 10 ? a % 10 : m;
		a /= 10;
	}

	//Вывод
	printf("Max = %d", m);

	return 0;
}