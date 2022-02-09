#include <iostream>

int main()
{
	system("chcp 1251 > nul");
	int a[100], n;
	double pr, srg;
	printf("¬ведите длину массива = ");
	scanf_s("%d", &n);
	printf("¬ведите элементы массива:\n");
	for (int i = 0; i < n; i++)
	{
		printf("Ёлемент массива a[%d] = ", i);
		scanf_s("%d", &a[i]);
	}
	pr = 1;
	for (int i = 0; i < n; i++)
	{
		pr *= a[i];
	}
	srg = pow(pr, 1.0 / n);
	printf("—реднее геометрическое элементов массива = %lf", srg);
	return 0;
}