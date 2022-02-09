#include<iostream>
//7. ¬вод€тс€ дес€ть натуральных чисел больше 2. ѕосчитать, сколько среди них простых чисел.
bool CheckPrime(int number)
{
	for (int i = 2; i <= number/2; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int count=0;

	for (int i = 0; i < 10; i++)
	{
		int input;
		do
		{
			printf("Print %d number: ",i+1);
			scanf_s("%d",&input);
		} while (input <= 2);
		if (CheckPrime(input))
		{
			count++;
		}
	}

	printf("%d", count);

	return 0;
}