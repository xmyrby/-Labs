#include<iostream>
#include"Stack.h"

void InitStack(Stack* stack, int length)
{
	if (stack->data == NULL)
	{
		stack->data = (int*)malloc(sizeof(int) * length);
		stack->length = length;
	}
	else printf("\n\tСтек инициализирован\n");
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
	if (stack->top >= 0) return stack->data[stack->top--];
	else return NULL;
}

void PrintStack(Stack const* stack)
{
	printf("\nСтек:\n");
	for (int i = 0; i <= stack->top; i++)
		printf("[%i] - %i\n", i + 1, (stack->data)[i]);
	printf("\n");
}

void FreeStack(Stack* stack)
{
	if (stack->data) free(stack->data);

	stack->data = NULL;
	stack->length = 0;
	stack->top = -1;
}