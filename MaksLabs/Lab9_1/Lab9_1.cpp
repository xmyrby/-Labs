#include <iostream>
//Написать программу вычисления значения выражения z для значений x, равных 2, 4, …, 20: z = 8f^3 − f, f = 2x.
int main()
{
	int x = 2, f = 0, z = 0;
	system("chcp 1251 > nul");

	for (; x <= 20; x += 2)
	{
		f = 2 * x;
		z = 8 * (f * f * f) - f;
		printf("x = %d; f = %d; z = %d\n", x, f, z);
	}

	return 0;
}