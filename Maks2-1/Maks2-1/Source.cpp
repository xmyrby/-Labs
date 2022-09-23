#include <iostream>

struct Date
{
	int day = 0;
	int month = 0;
	int year = 10000;
};

struct Student
{
	char name[100];
	Date date;
};

void GetStudents(Student* students, int& count)
{
	FILE* ft;
	if (fopen_s(&ft, "Students.txt", "rt") != 0)
	{
		exit(1);
	}
	while (!feof(ft))
	{
		fscanf_s(ft, "%s %d-%d-%d", students[count].name, 100, &students[count].date.day, &students[count].date.month, &students[count].date.year);
		count++;
	}

	fclose(ft);
}

Student GetOldest(Student* students, int count)
{
	int id = 0;
	Date mDate;
	for (int i = 0; i < count; i++)
	{
		if (mDate.year > students[i].date.year)
		{
			mDate = students[i].date;
			id = i;
		}
		else if (mDate.year == students[i].date.year && mDate.month > students[i].date.month)
		{
			mDate = students[i].date;
			id = i;
		}
		else if (mDate.month == students[i].date.month && mDate.day > students[i].date.day)
		{
			mDate = students[i].date;
			id = i;
		}
	}

	return students[id];
}

int main()
{
	Student students[10];
	int count = 0;
	GetStudents(students, count);
	Student oldest = GetOldest(students, count);
	printf("%s %d-%d-%d", oldest.name, oldest.date.day, oldest.date.month, oldest.date.year);

	return 0;
}