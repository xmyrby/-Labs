#include <iostream>
//���� ����� ����� n. �������� ���������� ����� ���� 2r, ������������� n(r - �����������).
int main()
{
	int n, r = 0, power = 1;
	system("chcp 1251 > nul");

	printf("������� n  = ");
	scanf_s("%d", &n);

	while (power <= n)
	{
		r++;
		power *= 2;
	}

	printf("r = %d",r);

	return 0;
}