#include <iostream>

int main()
{
	system("chcp 1251 > nul");

	//���� ������
	char string[100];
	printf("������� ������ : ");
	scanf_s("%s\0", &string, 100);

	//������� ���������� �������
	int startpos = 0;
	do
	{
		printf("������� ��������� ������ : ");
		scanf_s("%d\0", &startpos);
	} while (startpos < 0 || startpos >= 100);

	//����� �������� � �����
	for (int i = 0; i < 100; i++)
	{
		if (string[i] == '\0')
			break;
		if (i >= startpos)
		{
			char letter = string[i];
			int letternumb = int(letter);
			if (letternumb >= 49 && letternumb <= 57)
				string[i] = char(97 + (letternumb - 49));
			else if (letternumb == 48)
				string[i] = 122;
		}
		
		printf("%c", string[i]);
	}

	return 0;
}