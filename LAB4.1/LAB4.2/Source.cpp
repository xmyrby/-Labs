#include <stdio.h>
#include <math.h>

int main()
{
	int input = 0;

	//Ввод
	scanf_s("%d", &input);

	//Получение числа
	int output = ceil(input / 10) + input % 10 * 10000;

	//Вывод
	printf("%d", output);

	return 0;
}