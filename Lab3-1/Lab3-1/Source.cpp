#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
	int b, x, c;

	printf("Cost: "); scanf_s("%d", &b);

	printf("Length: ");  scanf_s("%d", &x);

	c = 0.8 * b * x;

	printf("Total: %d", c);

	return 0;
}