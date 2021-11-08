#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
	int x1, x2;
	printf("1st: "); scanf_s("%d", &x1);
	printf("2nd: "); scanf_s("%d", &x2);

	int h = int(2 / (1/x1+1/x2));

	printf("%d", h);

	return 0;
}