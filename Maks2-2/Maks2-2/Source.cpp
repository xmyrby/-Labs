#include <iostream>

int main()
{
	int* number1 = 0;
	int* number2 = 0;

	scanf_s("%d %d", number1, number2);
	int sum = *number1 + *number2;
	int prod = *number1 * *number2;
	printf("%d\n%d", sum, prod);

	return 0;
}