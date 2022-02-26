#include <iostream>

int main()
{
	system("chcp 1251 > nul");

	//Ввод строки
	char string[100];
	printf("Введите строку : ");
	scanf_s("%s\0", &string, 100);

	//Задание начального индекса
	int startpos = 0;
	do
	{
		printf("Введите начальный индекс : ");
		scanf_s("%d\0", &startpos);
	} while (startpos < 0 || startpos >= 100);

	//Смена символов и вывод
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