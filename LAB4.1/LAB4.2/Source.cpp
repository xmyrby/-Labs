#include <stdio.h>
#include <math.h>

int main()
{
	int input = 0;

	//����
	scanf_s("%d", &input);

	//��������� �����
	int output = ceil(input / 10) + input % 10 * 10000;

	//�����
	printf("%d", output);

	return 0;
}