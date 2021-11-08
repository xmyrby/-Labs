#include <stdio.h>
#include <math.h>
//7.	Дано целое число. Проверить, является ли оно отрицательным двузначным.
int main()
{
	int x;

	//Ввод числа
	scanf_s("%d", &x);

	//Проверяем
	if (x < 0 && x / 100 == 0 && x / 10 <= -1)
	{
		printf("yes");
	}
	else
	{
		printf("no");
	}

	return 0;
}