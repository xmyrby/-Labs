#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define ERROR_FILE_OPEN -3

void main()
{
	FILE* output = NULL;
	int number;
	if (fopen_s(&output, "output.bin", "wb"))
	{
		printf("Error opening file");
		exit(ERROR_FILE_OPEN);
	}

	scanf_s("%d", &number);
	fwrite(&number, sizeof(int), 1, output);
	fclose(output);
}