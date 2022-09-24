#include <iostream>

void GetText(char text[400], const char* file)
{
	FILE* ft;
	if (fopen_s(&ft, file, "rt") != 0)
	{
		exit(1);
	}

	gets_s(text, 300);

	fclose(ft);
}

int GetKCount(char text[400])
{
	int kCount = 0;

	char* ptr = strtok_s(text, " ", &text);

	while (ptr)
	{
		if (*ptr == 'К' || *ptr == 'к')
			kCount++;

		ptr = strtok_s(0, " ", &text);
	}

	return kCount;
}

int GetPCount(char text[400])
{
	int pCount = 0;
	int len = strlen(text);
	for (int i = 0; i < len; i++)
		if (text[i] >= -64 && text[i] <= -33)
			pCount++;


	return pCount;
}

void PrintText(char text[400])
{
	printf("\n%s ", text);
}

void Remove(char textWho[400], char textRem[400])
{
	char* p = strstr(textWho, textRem);
	strcpy_s(p, sizeof(p), p + strlen(textWho));
}

int main()
{
	char text1[400];
	char text2[400];
	system("chcp 1251 > nul");

	GetText(text1, "text1.txt");
	GetText(text2, "text2.txt");
	PrintText(text1);

	int kCount = GetKCount(text1);
	int pCount = GetPCount(text1);

	printf("\nКоличество слов с буквы 'К' и 'к': %d\nКоличество прописных букв: %d", kCount, pCount);

	Remove(text1, text2);
	PrintText(text1);

	return 0;
}