#include"DnyArray.h"
#include<stdlib.h>
#include"stdio.h"
#include<conio.h>
//*******************************************************
int  main(void)
{
	double** pA = NULL; double** pF = NULL; double** pQ = NULL;
	Numbersforfile s[100];
	system("chcp 1251>nul");
	int m, n[100]; int ch;
	do
	{

		printf("Введите:\n   0-Выход\n   1-Создать массив самостоятельно\n   2-Создать массив из файла\n   3-Запиать в файл массив взятый из файла\n   4-Записать массив созданный самостоятельно\n   5-Отчистить текущие массивы\n   6-Отчистить массив взятый из файла\n   7-Отчистить массив созданный самостоятельно   8-Запись и сохранение в бинарный фай \n");
		scanf_s("%d", &ch);
		switch (ch)
		{
		case 1:HandsArray(m, n); pA = ConstructArray(m, n); PrintArray(pA); break;
		case 2:inputfile(m, n, s); pF = ConstructArrayfile(m, n, s); PrintArray(pF); break;
		case 3:outputfile(pF, m); break;
		case 4:outputfile(pA, m); break;
		case 5:DestructArray(pA); DestructArray(pF); break;
		case 6:DestructArray(pF); break;
		case 7:DestructArray(pA); break;
		case 8:inputfilebin(m, n, s); pQ = ConstructArrayfile(m, n, s); PrintArray(pQ); break;
		default:printf("Введите цифру из списка\n"); break;
		}

	} while (ch != 0);

	system("pause");

	return 0;
}
