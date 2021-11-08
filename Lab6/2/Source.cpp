#include<math.h>
#include<iostream>
//7.    Даны стороны шести квадратов. Определить количество квадратов, у которых площадь меньше 10.

int compare(int side)
{
	if (side < 10)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	//Объявление массива
	int a[6];

	//Ввод
	printf("Размеры сторон: ");
	scanf_s("%d %d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5]);

	//Вывод
	printf("%d", compare(a[0]) + compare(a[1]) + compare(a[2]) + compare(a[3]) + compare(a[4]) + compare(a[5]));

	return 0;
}