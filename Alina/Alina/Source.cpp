#include <iostream>

int main()
{
	system("chcp 1251 > nul");
	int a[100], n;
	double pr, srg;
	printf("������� ����� ������� = ");
	scanf_s("%d", &n);
	printf("������� �������� �������:\n");
	for (int i = 0; i < n; i++)
	{
		printf("������� ������� a[%d] = ", i);
		scanf_s("%d", &a[i]);
	}
	pr = 1;
	for (int i = 0; i < n; i++)
	{
		pr *= a[i];
	}
	srg = pow(pr, 1.0 / n);
	printf("������� �������������� ��������� ������� = %lf", srg);
	return 0;
}