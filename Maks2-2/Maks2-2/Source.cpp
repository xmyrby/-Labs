#include <iostream>

int main()
{
	int number1 = 0;
	int number2 = 0;
	int* n1 = &number1;
	int* n2 = &number2;

	scanf_s("%d %d", &number1, &number2);
	int sum = *n1 + *n2;
	int prod = *n1 * *n2;
	printf("%d\n%d", sum, prod);

	return 0;
}