#include <iostream>

int main()
{
	system("chcp 1251 > nul");

	//���� ������
	char string[100];
	printf("������� ������ : ");
	gets_s(string);

	/*������� ������ �����
	0 - ����� �� ��������
	1 - ������ �����
	2 - ����� �� �����
	*/
	int start = 0;
	//����� �������� � �����
	for (int i = 0; i < 100; i++)
	{
		if (string[i] == '\0')
			break;

		int letter = int(string[i]);

		if (letter != 32 && start == 0)
			start = 1;
		if (letter == 32 && start == 1)
			start = 2;

		//�������� ��������
		if (start != 1 || start == 1 && !(letter < 65 || letter > 90 && letter < 97 || letter > 122))
			printf("%c", string[i]);
	}

	return 0;
}