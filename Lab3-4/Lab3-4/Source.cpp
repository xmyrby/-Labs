#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <string>

int main()
{
	int a,b,c,d;
	printf("a: "); scanf_s("%d", &a);

	b = a;

	b *= b; b *= b;

	printf("a^4 = %d\n", b);

	b = a;
	c = a;

	b *= b; b *= c; b *= b; b *= b; b *= c;

	printf("a^13 = %d\n", b);

	b = a;
	c = a;

	b *= b; b *= c; b *= b;

	printf("a^6 = %d\n", b);

	b = a;
	c = a;

	b *= b; b *= b; c *= b;

	d = c;

	c *= c; c *= d;

	printf("a^15 = %d\n", c);

	return 0;
}