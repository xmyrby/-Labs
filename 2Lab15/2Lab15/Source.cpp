#include<iostream>
#include"Stack.h"

void PushText(const char* text, Stack* stack, int len)
{
	for (int i = 0; i < len; i++)
		PushStack(stack, text[i]);
}

void Encrypt(Stack* stack, int len, int bias)
{
	for (int i = 0; i < len; i++)
		PushStack(stack, PopStack(stack) + bias);
}

void Decipher(Stack* stack, int len, int bias)
{
	for (int i = 0; i < len; i++)
		PushStack(stack, PopStack(stack) - bias);
}

void Chooser(Stack* stack, int len)
{
	system("cls");
	printf("��� ������ � �������?\n0 - ����������� � ������������\n1 - �����������\n2 - ������������\n�����: ");
	int choose, bias = 1;
	scanf_s("%d", &choose);

	system("cls");
	printf("�������� ���������: ");
	scanf_s("%d", &bias);

	system("cls");
	printf("����:\n	");
	PrintStack(stack);

	switch (choose)
	{
	case 0:
	{
		Encrypt(stack, len, bias);
		printf("\n\n������������� ����:\n	");
		PrintStack(stack);
		Decipher(stack, len, bias);
		printf("\n\n�������������� ����:\n	");
		PrintStack(stack);
		printf("\n");
		break;
	}
	case 1:
	{
		Encrypt(stack, len, bias);
		printf("\n\n������������� ����:\n	");
		PrintStack(stack);
		break;
	}
	case 2:
	{
		Decipher(stack, len, bias);
		printf("\n\n�������������� ����:\n	");
		PrintStack(stack);
		break;
	}
	default:
		break;
	}
}

int main()
{
	system("chcp 1251 > nul");
	Stack stack;
	char str[80];

	printf("������� �����: ");
	gets_s(str, 80);
	int len = strlen(str);
	PushText(str, &stack, len);

	Chooser(&stack, len);

	ClearStack(&stack);
	return 0;
}