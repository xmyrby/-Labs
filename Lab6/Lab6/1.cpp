#include<math.h>
#include<iostream>
//7.    Введено пять оценок у студента по программированию. Вывести текстовое описание среднего балла по предмету («отлично», «хорошо», «удовлетворительно», «неудовлетворительно»).

int main()
{
	system("chcp 1251");
	//Объявление массива
	int a[5];

	printf("Оценки: ");
	//Ввод
	scanf_s("%d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4]);
	//Подсчёт
	int average = (a[0] + a[1] + a[2] + a[3] + a[4]) / 5;
	//Проверка оценки и вывод
	switch (average)
	{
	case 2: printf("неудовлетворительно"); break;
	case 3: printf("удовлетворительно"); break;
	case 4: printf("хорошо"); break;
	case 5: printf("отлично"); break;
	default: break;
	}
	return 0;
}