#include<iostream>
//7.    ��������, �������� �� ����� � ������ �������������� ���������� � ����� � � ������ ������ �.
int main()
{
	//���������� ����������
	int a, b, c;

	//����
	printf("Print a = ");
	scanf_s("%d", &a);
	printf("Print b = ");
	scanf_s("%d", &b);
	printf("Print c = ");
	scanf_s("%d", &c);

	//����������
	while (c < a)
	{
		c += b;
	}

	//�������� � �����
	if (c == a)
	{
		printf("yes");
	}
	else
	{
		printf("no");
	}

	return 0;
}