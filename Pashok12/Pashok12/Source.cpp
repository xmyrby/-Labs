#include <iostream>

int Rec(int s, int ind, int target)
{
	if (s == target)
		return ind;
	return Rec(s + ind, ind + 1, target);
}

int main()
{
	int s = 0;
	scanf_s("%d", &s);
	printf("%d", Rec(0, 1, s) - 1);
}