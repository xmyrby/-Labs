#include<iostream>
#include<math.h>
//(x^2 * y^3)/(| x-5y |)
int main()
{
	//������� ����
	system("chcp 1251");

	//���������� ����������
	double x, y;

	//����
	printf("������� x: ");
	scanf_s("%lf", &x);

	printf("������� y: ");
	scanf_s("%lf", &y);

	//�����
	printf("�����: %.3lf",(x * x * y * y * y) / (abs(x - 5 * y)));

	return 0;
}