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

void GetStudentsKeyBoard(Student* students, int& count)
{
	do
	{
		printf("Введите количество студентов: ");
		scanf_s("%d", &count);
	} while (count <= 0 || count > 10);

	for (int i = 0; i < count; i++)
	{
		printf("Фамилия: ");
		scanf_s("%s", students[i].name, 100);
		printf("Дата рождения (день месяц год): ");
		scanf_s("%d %d %d", &students[i].date.day, &students[i].date.month, &students[i].date.year);
	}
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

void Chooser(Student* students, int& count)
{
	int type = 0;

	do
	{
		printf("0 - Ручной ввод\n1 - Ввод с файла\nВыбор: ");
		scanf_s("%d", &type);
	} while (type < 0 || type>1);

	switch (type)
	{
	case 0:
		GetStudentsKeyBoard(students, count);
		break;
	case 1:
		GetStudents(students, count);
		break;
	default:
		break;
	}
}

int main()
{
	system("chcp 1251 > nul");
	Student students[10];
	int count = 0;
	Chooser(students, count);
	Student oldest = GetOldest(students, count);
	printf("Старший студент: %s %d-%d-%d", oldest.name, oldest.date.day, oldest.date.month, oldest.date.year);

	return 0;
}