//25.Даны два предложения. Для каждого слова первого
//предложения определить количество его вхождений во второе
//предложение.
#include<iostream>

struct String
{
	int wordscount = 0;
	char words[25][35] = { NULL };
	int ct_ch[35] = { NULL };
};

void findWord(char* str, String string)
{
	int count_ch = 0;
	int ln = strlen(str);
	for (int i = 0; i < ln; i++)
	{
		char w = str[i];
		if (w != ' ' && w != ',' && w != '.' && i != ln - 1)
		{
			string.words[string.wordscount][count_ch++] = str[i];
		}
		else
		{
			if (i == ln - 1)
			{
				string.words[string.wordscount][count_ch++] = str[i];
			}
			string.ct_ch[string.wordscount++] = count_ch;
			count_ch = 0;
		}
	}
}

void Compare(String string1, String string2)
{
	int words_coincedence[25] = { NULL };
	int counter_coincedence = 0;
	for (int i = 0; i < string1.wordscount; i++)
	{
		counter_coincedence = 0;
		for (int j = 0; j < string2.wordscount; j++)
		{
			if (strcmp(string1.words[i], string2.words[j]) == 0)
			{
				words_coincedence[i] = ++counter_coincedence;
			}
			else
			{
				words_coincedence[i] = counter_coincedence;
			}
		}
		printf("\n%s Встретилось %i раз", string1.words[i], words_coincedence[i]);
	}
}

int main()
{
	system("chcp 1251");
	system("cls");

	String string1;
	String string2;

	printf("Введите первую строку: ");
	char str1[256];
	gets_s(str1, 256);
	findWord(str1, string1);

	printf("\nВведите вторую строку: ");
	char str2[256];
	gets_s(str2, 256);
	findWord(str2, string2);

	Compare(string1, string2);

	return 0;
}