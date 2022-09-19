#include <iostream>

void ReadTxt(char lines[20][100], int& rows)
{
	FILE* f;
	if (fopen_s(&f, "text.txt", "r") != 0)
	{
		printf("Couldn't open file text.txt!\n");
		exit(1);
	}

	while (!feof(f))
	{
		fgets(lines[rows], 1000, f);
		rows++;
	}

	fclose(f);
}

void SaveTxt(char lines[20][100], int rows)
{
	FILE* f;
	if (fopen_s(&f, "text1.txt", "w") != 0)
	{
		printf("Couldn't open file text1.txt!\n");
		exit(1);
	}

	for (int i = 0; i < rows; i++)
		fprintf(f, "%s", lines[i]);

	fclose(f);
}

void AlignLine(char line[100], int len, int spaces)
{
	while (spaces)
	{
		int changed = false;
		for (int i = 0; i < len; i++)
		{
			bool space = false;
			if (line[i] == ' ' && !space && spaces > 0)
			{
				space = true;
				for (int j = len; j > i; j--)
					line[j] = line[j - 1];
				len++;
				i++;
				line[i] = ' ';
				spaces--;
				changed = true;
			}
			else
				space = false;
		}
		if (changed == false)
		{
			for (int j = len; j > 0; j--)
				line[j] = line[j - 1];
			len++;
			line[0] = ' ';
			spaces--;
		}
	}
	line[len] = '\0';
}

void Align(char lines[20][100], int rows)
{
	int max = 0;
	for (int i = 0; i < rows; i++)
	{
		int len = strlen(lines[i]);

		if (i == rows - 1)
			len++;

		if (len > max)
			max = len;
	}
	for (int i = 0; i < rows; i++)
	{
		int len = strlen(lines[i]);
		
		if (i == rows - 1)
			len++;

		if (len < max)
			AlignLine(lines[i], len, max - len);
	}
}

int main()
{
	char lines[20][100];
	int rows = 0;
	ReadTxt(lines, rows);
	Align(lines, rows);
	SaveTxt(lines, rows);

	return 0;
}