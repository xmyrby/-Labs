//25.Даны два предложения. Для каждого слова первого
//предложения определить количество его вхождений во второе
//предложение.

#include<iostream>
#include<string.h>

struct String
{
	int count = 0;
	char words[30][30] = { NULL };
	int ct_ch[30] = { NULL };
};

int len(char* s)
{
	int l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	return l;
}

bool CompWords(char* word1, int count1, char* word2, int count2)
{
	if (count1 != count2)
		return false;
	for (int i = 0; i < count1; i++)
	{
		if (word1[i] != word2[i])
			return false;
	}
	return true;
}

void findWord(char* str, int& count_word, char word[30][30], int* ct_ch)
{
	int count_ch = 0;
	int ln = len(str);
	for (int i = 0; i < ln; i++)
	{
		char w = str[i];
		if (w != ' ' && w != ',' && w != '.' && i != ln - 1)
		{
			word[count_word][count_ch++] = str[i];
		}
		else
		{
			if (i == ln - 1)
			{
				word[count_word][count_ch++] = str[i];
			}
			ct_ch[count_word++] = count_ch;
			count_ch = 0;
		}
	}
}

void Compare(char word[30], int count, String string)
{
	int countIn = 0;
	for (int i = 0; i < string.count; i++)
	{
		if (CompWords(word, count, string.words[i], string.ct_ch[i]))
			countIn++;
	}
	printf("%s встретилось %d раз\n", word, countIn);
}

int main()
{
	system("chcp 1251 > nul");
	String string1;
	String string2;

	printf("Введите первую строку: ");
	char str1[256];
	gets_s(str1, 256);
	findWord(str1, string1.count, string1.words, string1.ct_ch);

	printf("\n\nВведите вторую строку ");
	char str2[256];
	gets_s(str2, 256);
	findWord(str2, string2.count, string2.words, string2.ct_ch);

	for (int i = 0; i < string1.count; i++)
		Compare(string1.words[i], string1.ct_ch[i], string2);

	return 0;
}