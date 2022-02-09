#include<iostream>
struct ats
{
	char name[100];
	int exam_1;
	int exam_2;
	int exam_3;
};
void print_Student_Exam(ats s)
{
	printf("%s \t| %i \t| %i \t| %i \t| \n", s.name, s.exam_1, s.exam_2, s.exam_3);
}

void scan_Student_Exam(ats& s)
{
	scanf_s("%s%i%i%i", &s.name, 100, &s.exam_1, &s.exam_2, &s.exam_3);
}

void student4_5(ats* s, int size)
{
	int sum = 0, sum1 = 0;
	for (int i = 0; i < size; i++) {
		if (s[i].exam_1 < 3 && s[i].exam_2 < 3 && s[i].exam_3 < 3)
			sum++;
	}
	printf("количество студентов%d", sum);
	sum1 = sum / size * 100;
	printf("процент успевающих %d", sum1);
}


int main()
{
	system("chcp 1251");
	ats mas[100];
	int size;

	printf("введите кол-во студентов");
	scanf_s("%d", &size);
	for (int i = 0; i < size; i++)
	{
		scan_Student_Exam(mas[i]);
	}
	for (int i = 0; i < size; i++)
	{
		print_Student_Exam(mas[i]);
	}
	student4_5(mas, size);
	return 0;
}