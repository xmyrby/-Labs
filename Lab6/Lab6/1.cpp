#include<math.h>
#include<iostream>
//7.    ������� ���� ������ � �������� �� ����������������. ������� ��������� �������� �������� ����� �� �������� (��������, �������, ������������������, ��������������������).

int main()
{
	system("chcp 1251");
	//���������� �������
	int a[5];

	printf("������: ");
	//����
	scanf_s("%d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4]);
	//�������
	int average = (a[0] + a[1] + a[2] + a[3] + a[4]) / 5;
	//�������� ������ � �����
	switch (average)
	{
	case 2: printf("�������������������"); break;
	case 3: printf("�����������������"); break;
	case 4: printf("������"); break;
	case 5: printf("�������"); break;
	default: break;
	}
	return 0;
}