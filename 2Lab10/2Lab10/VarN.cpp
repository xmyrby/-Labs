#include <stdio.h>
#include <string.h>
#include <iostream>
//7
char* RemoveNumbers(char* str)
{
	char newStr[80];
	int ln = 0;
	int dcount = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			newStr[ln++] = str[i];
		}
		else
			dcount++;
	}
	newStr[ln] = '\0';
	printf("Удалено %i цифр\n", dcount);
	return newStr;
}

int main()
{
	system("chcp 1251 > nul");
	char str[80];
	gets_s(str);
	printf("Итог: %s", RemoveNumbers(str));

	return 0;
}