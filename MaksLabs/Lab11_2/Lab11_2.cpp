#include <iostream>
//((x-5)^(i+1))/((i+1)!)
int main()
{
	int fact = 6, i = 1;
	double s = 0, power = 0, e = 0, x = 0, last = 0;
	system("chcp 1251 > nul");

	printf("������� e = ");
	scanf_s("%lf", &e);

	printf("������� x = ");
	scanf_s("%lf", &x);
	power = (x - 5);
	do
	{
		power *= (x - 5);
		fact *= (i + 3);
		last = power / fact;
		s += last;
		printf("%.3lf\n",last);
		i++;
	} while (last >= e);


	printf("�������� ��������� = %.3lf", s);

	return 0;
}