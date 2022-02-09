#include <iostream>
//Даны стороны шести квадратов. Площади скольки из этих квадратов меньше 10.
bool check(int side)
{
	if (side * side < 10)
	{
		return true;
	}
	return false;
}

int main()
{
	int count = 0, side = 0;
	system("chcp 1251 > nul");


	for (size_t i = 0; i < 6; i++)
	{
		printf("Введите сторону %d квадрата: ", i + 1);
		scanf_s("%d", &side);
		if (check(side))
			count++;
	}

	printf("Количество = %d", count);

	return 0;
}