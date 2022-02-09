#include <iostream>
//Дано целое положительное число. Определить произведение цифр, стоящих на четных позициях.
int main()
{
	int number = 0, out = 1;
	system("chcp 1251 > nul");
	do
	{
		system("cls");
		printf("Введите число = ");
		scanf_s("%d", &number);
	} while (number <= 0);

	while (number != 0)
	{
		out *= number % 10;
		number /= 100;
	}

	printf("Произведение = %d", out);

	return 0;
}