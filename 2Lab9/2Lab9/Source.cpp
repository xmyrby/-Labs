#include"Rager.h"

void Switcher(int choose, RaggedArray& mas)
{
	do {
		printf("Прочитать массив:\n0-Создать\n1-текстовый файл\n2-бинарный файл\nВыбор: ");
		scanf_s("%i", &choose);
	} while (0 > choose or choose > 3);

	switch (choose)
	{
	case 0:
	{
		CreateArraySelf(mas);
		FillArray(mas);
		PrintArray(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	case 1:
	{
		ReadTxt(mas);
		PrintArray(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	case 2:
	{
		ReadBin(mas);
		PrintArray(mas);
		SaveTxt(mas);
		SaveBin(mas);
		FreeMas(mas);
		break;
	}
	break;
	}
}

int main()
{
	system("chcp 1251 > nul");
	system("cls");
	srand(time(NULL));

	int choose = NULL;
	RaggedArray mas{};
	Switcher(choose, mas);
	return 0;
}