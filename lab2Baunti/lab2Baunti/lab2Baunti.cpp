#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	setlocale(LC_ALL, "rus");
	double x, y, c;
	int k, m, n, i;

	printf("Ввод x = ");
	scanf_s("%lf", &x);

	printf("Ввод y = ");
	scanf_s("%lf", &y);

	c = (2.71 * pow(x, 2) - cos((180 / M_PI * y))) / (tan(pow((180 / M_PI * x), 2)) * exp(-y));

	k = c;
	m = floor(c);
	i = ceil(c);
	n = static_cast<int>(c);

	printf("c = %lf\nОкругление в большую сторону i = %d\nЦелая часть результата m = %d\nЦелое k = %d\nЦелое n = %d\nПрефиксное ++k = %d\nПостфиксное n++ = %d",c,i,m,k,n,++k,n++);

	return 0;
}