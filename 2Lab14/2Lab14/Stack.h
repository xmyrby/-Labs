#ifndef __STACK_H__
#define __STACK_H__

struct Element
{
	int data = 0;
	Element* next = NULL;
};

struct Stack
{
	Element* head = NULL;
};

void PushStack(Stack* stack, int number);

int PopStack(Stack* stack);

void PrintStack(Stack const* stack);

void ClearStack(Stack* stack);

bool CheckIfStackIsEmpty(Stack* stack);

#endif