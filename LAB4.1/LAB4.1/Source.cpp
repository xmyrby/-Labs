#include <stdio.h>
#include <math.h>

int main()
{
	int input = 0;
	//���� �����������
	scanf_s("%d", &input);

	int x, y, z;

	//��������� �����������
	z = input % 10;

	//��������� �����������
	y = ceil(input / 10);

	//������� � �����
	x = ceil(y / 100);

	//��������� ���������� �����������
	y %= 100;

	//�����
	printf("%d m %d cm %d mm", x, y, z);

	return 0;
}