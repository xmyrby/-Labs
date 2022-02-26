#include <iostream>

int main()
{
	system("chcp 1251 > nul");

	//Ввод строки
	char string[100];
	printf("Введите строку : ");
	gets_s(string);

	/*Триггер начала слова
	0 - Слово не началось
	1 - Внутри слова
	2 - Выход из слова
	*/
	int start = 0;
	//Смена символов и вывод
	for (int i = 0; i < 100; i++)
	{
		if (string[i] == '\0')
			break;

		int letter = int(string[i]);

		if (letter != 32 && start == 0)
			start = 1;
		if (letter == 32 && start == 1)
			start = 2;

		//Проверка символов
		if (start != 1 || start == 1 && !(letter < 65 || letter > 90 && letter < 97 || letter > 122))
			printf("%c", string[i]);
	}

	return 0;
}