#include <iostream>
//S(m,j=1)P(n,i=1)(a*i-b*j)
int main()
{
	int m = 0, n = 0;
	double a = 0, b = 0, s = 0, p;
	system("chcp 1251 > nul");

	do
	{
		system("cls");
		printf("������� m = ");
		scanf_s("%d", &m);
		printf("������� n = ");
		scanf_s("%d", &n);
	} while (m <= 1 || n <= 1);

	printf("������� a = ");
	scanf_s("%lf", &a);
	printf("������� b = ");
	scanf_s("%lf", &b);

	for (int j = 1; j <= m; j++)
	{
		p = 1;
		for (int i = 1; i <= n; i++)
		{
			p *= (a * i - b * j);
		}
		s += p;
	}

	printf("�������� ��������� = %.3lf", s);

	return 0;
}