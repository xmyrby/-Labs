#include<iostream>
#include"Stack.h"

void InsertStack(Stack* stack, char ch, int position)
{
	Element* tmp = (Element*)malloc(sizeof(Element));

	if (!tmp)
		return;

	int counter = 0;

	for (Element* current = stack->head; current != NULL; current = current->next)
		counter++;

	if (position >= counter)
		PushStack(stack, ch);
	else if (position == 0)
	{
		tmp->data = ch;
		Element* old_head = stack->head;
		stack->head = tmp;
		tmp->next = old_head;
	}
	else
	{
		int i = 0;
		Element* next = stack->head, * prev = NULL;
		while (i != position)
		{
			prev = next;
			next = next->next;
			i++;
		}
		tmp->data = ch;
		tmp->next = next;
		prev->next = tmp;
	}
}

void PushStack(Stack* stack, char ch)
{
	Element* tmp = (Element*)malloc(sizeof(Element));

	if (!tmp)
		return;

	tmp->data = ch;
	tmp->next = NULL;

	if (stack->head == NULL)
	{
		stack->head = tmp;
		stack->tail = tmp;
	}
	else
	{
		stack->tail->next = tmp;
		stack->tail = tmp;
	}
}

char PopStack(Stack* stack)
{
	if (stack->head == NULL)
		return 0;

	char ch = stack->head->data;

	if (stack->head == stack->tail)
		stack->tail = NULL;

	Element* tmp = stack->head;
	stack->head = stack->head->next;
	free(tmp);

	return ch;
}

void PrintStack(Stack const* stack)
{
	for (Element* current = stack->head; current != NULL; current = current->next)
		printf("%c", current->data);
}

void ClearStack(Stack* stack)
{
	while (stack->head != NULL)
	{
		if (stack->head == stack->tail)
			stack->tail = NULL;

		Element* tmp = stack->head;
		stack->head = stack->head->next;
		free(tmp);
	}
} 