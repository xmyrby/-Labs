#include<iostream>

void RandomArray(int* arr)
{
	for (int i = 1; i < 15; i++)
	{
		arr[i] = (rand() % 201 - 100) / 10;
		printf("%i\n", arr[i]);
	}
}

void SumArray(int* arr, int sum)
{
	for (int i = 1; i < 14; i += 2)
	{
		sum += arr[i] + arr[i + 1] * arr[i + 1];
	}
	sum += arr[14];
	printf("\n%i", sum);
}

int main()
{
	srand(time(0));
	system("chcp 1251");

	int arr[15], sum = 0;

	RandomArray(arr);

	SumArray(arr, sum);
}