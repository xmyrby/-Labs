#include<iostream>
#include <conio.h>

struct Stack
{
	int* data = NULL;
	int length = 0;
	int top = -1;
};

void InitStack(Stack* stack, int length)
{
	if (stack->data == NULL)
	{
		stack->data = (int*)malloc(sizeof(int) * length);
		stack->length = length;
	}
	else
		printf("\n\tСтек инициализирован\n");
}

void PushStack(Stack* stack, int number)
{
	if (stack->top >= stack->length)
	{
		stack->length += 10;
		stack->data = (int*)realloc(stack->data, sizeof(int) * stack->length);
	}

	stack->top++;

	stack->data[stack->top] = number;
}

int PopStack(Stack* stack)
{
	if (stack->top >= 0)
		return stack->data[stack->top--];
	else
		return NULL;
}

void PrintStack(Stack const* stack)
{
	system("cls");
	printf("Стек:\n");
	for (int i = 0; i <= stack->top; i++)
		printf("[%i] - %i\n", i + 1, (stack->data)[i]);
	printf("\n");
}

void FreeStack(Stack* stack)
{
	if (stack->data)
		free(stack->data);

	stack->data = NULL;
	stack->length = 0;
	stack->top = -1;
}

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