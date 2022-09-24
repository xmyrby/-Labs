#include <iostream>

struct String
{
	char text[20][20];
	int count = 0;
};

void GetText(String& str, const char* file)
{
	FILE* ft;
	if (fopen_s(&ft, file, "rt") != 0)
	{
		exit(1);
	}
	while (!feof(ft))
	{
		fscanf_s(ft, "%s", &str.text[str.count], 200);
		str.count++;
	}

	fclose(ft);
}

int GetKCount(String& str)
{
	int kCount = 0;
	for (int i = 0; i < str.count; i++)
		if (str.text[i][0] == 'К' || str.text[i][0] == 'к')
			kCount++;

	return kCount;
}

int GetPCount(String& str)
{
	int pCount = 0;
	for (int i = 0; i < str.count; i++)
	{
		int j = 0;
		while (str.text[i][j] != '\0')
		{
			if (str.text[i][j] >= -64 && str.text[i][j] <= -33)
				pCount++;
			j++;
		}
	}


	return pCount;
}

void PrintText(String& str)
{
	printf("\n");
	for (int i = 0; i < str.count; i++)
		printf("%s ", str.text[i]);
}

void Remove(String& who, String& rem)
{
	bool removed = false;
	for (int i = 0; i < who.count; i++)
	{
		if (!removed)
		{
			int j = 0;
			while (who.text[i][j] != '\0')
			{
				if (who.text[i][j] != rem.text[0][j])
					break;
				j++;
				if (rem.text[0][j] == '\0')
				{
					removed = true;
					break;
				}
			}

			int count = 0;
			while (who.text[i][count] != '\0')
				count++;

			for (int k = 0; k < count; k++)
			{
				who.text[i][k] = who.text[i][k + j];
			}
		}
	}
}

int main()
{
	system("chcp 1251 > nul");
	
	String str1;
	String str2;

	GetText(str1, "text1.txt");
	GetText(str2, "text2.txt");
	PrintText(str1);

	int kCount = GetKCount(str1);
	int pCount = GetPCount(str1);

	printf("\nКоличество слов с буквы 'К' и 'к': %d\nКоличество прописных букв: %d", kCount, pCount);

	Remove(str1, str2);
	PrintText(str1);

	return 0;
}