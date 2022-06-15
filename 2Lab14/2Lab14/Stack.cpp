#include<iostream>
#include"Stack.h"

int GetSize(Stack* stack)
{
	int size = 0;
	for (Element* current = stack->head; current != NULL; current = current->next)
		size++;
	return size;
}

void PushStack(Stack* stack, int number)
{
	Element* tmp = (Element*)malloc(sizeof(Element));

	if (!tmp)
		return;

	tmp->next = stack->head;
	tmp->data = number;
	stack->head = tmp;
}

int PopStack(Stack* stack)
{
	Element* tmp;
	int number = 0;
	if (stack->head)
	{
		tmp = stack->head;
		stack->head = stack->head->next;
		number = tmp->data;
		free(tmp);
	}
	return number;
}

void PrintStack(Stack const* stack)
{
	for (Element* current = stack->head; current != NULL; current = current->next)
		printf("%i ", current->data);
}


void ClearStack(Stack* stack)
{
	while (stack->head)
	{
		Element* tmp = stack->head;
		stack->head = stack->head->next;
		free(tmp);
	}
}

bool CheckIfStackIsEmpty(Stack* stack)
{
	if (stack->head != NULL)
		return true;
	return false;
}