#include <stdio.h>
#include <math.h>
//7.	���� ����� �����. ���������, �������� �� ��� ������������� ����������.
int main()
{
	int x;

	//���� �����
	scanf_s("%d", &x);

	//���������
	if (x < 0 && x / 100 == 0 && x / 10 <= -1)
	{
		printf("yes");
	}
	else
	{
		printf("no");
	}

	return 0;
}