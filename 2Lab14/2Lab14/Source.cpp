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

void PushNumberInStack(Stack* stack, int number)
{
	int j = 1, number_length = Length(number);

	for (int i = 1; i < number_length; i++)
		j *= 10;

	while (number != 0)
	{
		PushStack(stack, number / j);
		number %= j;
		j /= 10;
		PrintStack(stack);
		printf("\n");
	}
}

int ReverseNumber(Stack* stack)
{
	int length = 0, number = 0, j = 1;

	for (Element* current = stack->head; current != NULL; current = current->next)
	{
		length++;
		j *= 10;
	}

	for (int i = 0; i < length; i++)
	{
		j /= 10;
		number += PopStack(stack) * j;
	}

	return number;
}

int main()
{
	system("chcp 1251 > nul");

	Stack stack;
	int number = 0;

	do {
		printf("Введите число: ");
		scanf_s("%i", &number);
	} while (number < 10);

	PushNumberInStack(&stack, number);

	printf("\n%i", ReverseNumber(&stack));

	ClearStack(&stack);

	return 0;
}