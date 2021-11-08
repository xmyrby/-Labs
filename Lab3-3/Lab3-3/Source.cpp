#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
	double x;
	printf("x: "); scanf_s("%lf", &x);

	printf("%.2lf", ( 2*(-pow(x,2)+7*x-7)/(pow(x,2)-2*x+2)-1 ));
	
	return 0;
}