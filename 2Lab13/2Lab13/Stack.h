#ifndef __STACK_H__
#define __STACK_H__

struct Stack
{
	int* data = NULL;
	int length = 0;
	int top = -1;
};

void InitStack(Stack* stack, int length);

void PushStack(Stack* stack, int number);

int PopStack(Stack* stack);

void PrintStack(Stack const* stack);

void FreeStack(Stack* stack);

#endif