#include <iostream>
//(-1)^n*(x^(3n+n)/(n+1)!)
int main()
{
	system("chcp 1251 > nul");
	int k = 3;
	double s = 0, x, e, number, fact = 1, lastx, polar = 1;
	printf("������� x: ");
	scanf_s("%lf", &x);
	do
	{
		printf("������� e (e>0): ");
		scanf_s("%lf", &e);
	} while (e <= 0);

	//������� ��������� �������� ������� � ����������
	lastx = pow(4 * x, 8);
	fact = 1;

	do
	{
		//������� � �����
		fact *= (k - 1);
		number = polar * (lastx / fact);
		printf("����� %d = %.3lf\n", k, number);
		s += number;
		lastx *= 64 * x * x * x;
		polar *= -1;
		k++;
	} while (fabs(number) > e); //��������

	//�����
	printf("%lf", s);

	return 1;
}
