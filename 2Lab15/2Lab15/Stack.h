#ifndef __STACK_H__
#define __STACK_H__

struct Element
{
	char data;
	Element* next = NULL;
};

struct Stack
{
	Element* head = NULL, * tail = NULL;
};

void InsertStack(Stack* stack, char ch, int position);

void PushStack(Stack* stack, char ch);

char PopStack(Stack* stack);

void PrintStack(Stack const* stack);

void ClearStack(Stack* stack);

#endif