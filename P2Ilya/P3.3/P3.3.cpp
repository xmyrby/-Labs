#include <iostream>
//(-1)^n*(x^(3n+n)/(n+1)!)
int main()
{
	system("chcp 1251 > nul");
	int n = 3;
	double s = 0, x, e, number, fact = 1, lastx, polar = -1;
	printf("������� x: ");
	scanf_s("%lf", &x);
	do
	{
		printf("������� e (e>0): ");
		scanf_s("%lf", &e);
	} while (e <= 0);

	//������� ��������� �������� ������� � ����������
	lastx = pow(x, 10);
	fact = 6;

	do
	{
		//������� � �����
		fact *= (n + 1);
		number = polar * (lastx / fact);
		printf("����� %d = %.3lf\n", n, number);
		s += number;
		lastx *= x * x * x;
		polar *= -1;
		n++;
	} while (fabs(number) > e); //��������
	
	//�����
	printf("%lf", s);

	return 1;
}
