#include <conio.h>
#include <stdio.h>

int main()
{
	int x, *p;
	x = 10;
	for (int i = 0; i < x;)
	{
		p = &i;
		*p += 1;
		printf("%d\n",*p);
	}
	return 1;
}