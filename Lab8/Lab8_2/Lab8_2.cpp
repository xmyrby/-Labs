#include<iostream>
//???? ?? ?????? ???? ?????????, ?????????? ??? ??????? ?????? 2 ???????????? ?????? ?7, ?????????? ??, ??????????? ???????? ???????????? ?????????? ???????? ? ??????? ????? ? ????????????.
int main()
{
	//?????????? ??????????
	int a, m = 0;

	//????
	do
	{
		system("cls");
		printf("Print number = ");
		scanf_s("%d", &a);
	} while (a < 1000 || a>9999);

	//????????? ?????
	while (a > 0)
	{
		m = m < a % 10 ? a % 10 : m;
		a /= 10;
	}

	//?????
	printf("Max = %d", m);

	return 0;
}