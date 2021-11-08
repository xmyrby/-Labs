#include <stdio.h>
#include <math.h>

int main()
{
	int input = 0;
	//Ввод миллиметров
	scanf_s("%d", &input);

	int x, y, z;

	//Получение миллиметров
	z = input % 10;

	//Получение сантиметров
	y = ceil(input / 10);

	//Перевод в метры
	x = ceil(y / 100);

	//Получение оставшихся сантиметров
	y %= 100;

	//Вывод
	printf("%d m %d cm %d mm", x, y, z);

	return 0;
}