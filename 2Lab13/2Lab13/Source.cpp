#include<iostream>
#include"Stack.h"
#include <conio.h>

int Length(int number)
{
	int length = 0;

	while (number != 0)
	{
		length++;
		number /= 10;
	}

	return length;
}

int ReverseNumber(Stack* stack)
{
	int number = 0;

	for (int i = 0, j = 1; i < stack->length; i++, j *= 10)
		number += PopStack(stack) * j;

	return number;
}

int main()
{
	system("chcp 1251");
	system("cls");

	Stack stack;
	int number = 0;

	do {
		printf("Введите число: ");
		scanf_s("%i", &number);
	} while (number < 10);

	InitStack(&stack, Length(number));

	while (number != 0)
	{
		PushStack(&stack, number % 10);
		number /= 10;
		PrintStack(&stack);
		_getch();
	}

	printf("%i\n", ReverseNumber(&stack));

	FreeStack(&stack);

	return 0;
}