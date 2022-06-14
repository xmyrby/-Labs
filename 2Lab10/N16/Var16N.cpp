#include <stdio.h>
#include <string.h>
#include <iostream>
//16
char* RemoveSpaces(char* str)
{
	char newStr[80];
	int ln = 0;
	int count = 1;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
			count++;
		else
			count = 0;

		if (count < 2)
		{
			newStr[ln] = str[i];
			ln++;
		}
	}
	newStr[ln] = '\0';
	return newStr;
}

int main()
{
	system("chcp 1251 > nul");
	char str[80];
	gets_s(str);
	printf("Итог: %s", RemoveSpaces(str));

	return 0;
}