#include <iostream>

int main()
{
	system("chcp 1251 > nul");

	//���� ������
	char string[100];
	printf("������� ������ : ");
	gets_s(string);

	/*������� ������ �����
	0 - �� � �����
	1 - ������ �����
	*/
	int start = 0, max = 0, indexes[100], count = 0, maxcount = 0, startind = 0;

	for (int i = 0; i < 100; i++)
	{
		int letter = int(string[i]);
		//���� � �����
		if (letter != 32 && start == 0)
		{
			startind = i;
			start = 1;
		}
		//����� �� �����, �������� ����������� �� ���������� �������
		if ((letter == 32 || letter == 0) && start == 1)
		{
			if (count >= max)
			{
				max = count;
				if (count != max)
					maxcount = 0;
				else
				{
					indexes[maxcount] = startind;
					maxcount++;
				}
			}
			count = 0;
			start = 0;
		}

		if (string[i] == '\0')
			break;

		//�������� ��������
		if (start == 1 && (letter == 65 || letter == 97 || letter == 69 || letter == 101 || letter == 73 || letter == 105 || letter == 79 || letter == 111 || letter == 85 || letter == 117))
			count++;
			
	}

	printf("�������� �������: %d\n������ ����:\n",max);

	//����� ����
	for (int i = 0; i < maxcount; i++)
	{
		for (int j = indexes[i]; j < 100; j++)
		{
			int letter = int(string[j]);
			if (letter == 32 || string[j] == '\0')
				break;
			else
				printf("%c", string[j]);
		}
		printf("\n");
	}

	return 0;
}