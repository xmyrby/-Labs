#include <iostream>
//���� ����� ������������� �����. ���������� ������������ ����, ������� �� ������ ��������.
int main()
{
	int number = 0, out = 1;
	system("chcp 1251 > nul");
	do
	{
		system("cls");
		printf("������� ����� = ");
		scanf_s("%d", &number);
	} while (number <= 0);

	while (number != 0)
	{
		out *= number % 10;
		number /= 100;
	}

	printf("������������ = %d", out);

	return 0;
}