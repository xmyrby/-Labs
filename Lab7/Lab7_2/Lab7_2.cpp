#include<iostream>
//7.    ���� ����� ������������� �����.���������� ������������ ����� � ��� ������
int main()
{
	//���������� ����������
	int a, m = 0;

	//����
	printf("Print number = ");
	scanf_s("%d", &a);

	//��������� �����
	while (a > 0)
	{
		m = m < a % 10 ? a % 10 : m;
		a /= 10;
	}

	//�����
	printf("Max = %d", m);

	return 0;
}