#include<iostream>
#include<math.h>
//(x^2 * y^3)/(| x-5y |)
int main()
{
	//Русский язык
	system("chcp 1251");

	//Объявление переменных
	double x, y;

	//Ввод
	printf("Введите x: ");
	scanf_s("%lf", &x);

	printf("Введите y: ");
	scanf_s("%lf", &y);

	//Вывод
	printf("Ответ: %.3lf",(x * x * y * y * y) / (abs(x - 5 * y)));

	return 0;
}