#include <iostream>

using namespace std;

int main()
{
	int a = 2, b = 3, c = 6;

	a = 7;

	b = a * 2;

	c = a + b;

	b = (a + b) * c;

	a = b + a + c;

	cout << a;

	return 0;
}