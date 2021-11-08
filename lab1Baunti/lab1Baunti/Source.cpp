#include<iostream>

int main()
{
	//Объявление переменных
	double x, y, z;

#pragma region CalcYZ

#pragma region GetX
	//Ввод x
	printf("Print x = ");
	scanf_s("%lf", &x);
#pragma endregion

#pragma region CompYZ
	//Вычисление y
	y = (3.5 * pow(x,5) - 4 * pow(x, 3) + 5 * x + 7) / (2 * pow(x, 5) + 4.3 * pow(x, 3) - 1);

	//Вычисление z
	z = (1.8 * pow(x, 3) + 2 * x + 6) / (0.5 * pow(x, 5) + 4 * pow(x, 3) - 2);
#pragma endregion


#pragma region PutYZ
	//Вывод
	printf("y = %.3lf\nz = %.3lf", y, z);
#pragma endregion

#pragma endregion

	return 0;
}