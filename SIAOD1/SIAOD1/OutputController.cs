using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SIAOD1
{
    internal class OutputController
    {
        public List<Student> SortStudents(List<Student> students)
        {
            int count = students.Count;
            for (int i = 0; i < count - 1; i++)
            {
                for (int j = i + 1; j < count; j++)
                {
                    if (students[i].Surname[0] >= students[j].Surname[0])
                    {
                        Student student = students[j];
                        students[j] = students[i];
                        students[i] = student;
                    }
                }
            }
            return students;
        }

        public List<Student> FilterByAverage(List<Student> students)
        {
            int count = students.Count;
            for (int i = 0; i < count - 1; i++)
            {
                for (int j = i + 1; j < count; j++)
                {
                    if (students[i].Average <= students[j].Average)
                    {
                        Student student = students[j];
                        students[j] = students[i];
                        students[i] = student;
                    }
                }
            }
            return students;
        }
        private void PrintRates(int[] rates)
        {
            int count = rates.Length;
            for (int i = 0; i < count; i++)
                Console.WriteLine($"Предмет №{i} : {rates[i]}");
        }
        public void PrintStudents(List<Student> students)
        {
            Console.Clear();
            int count = students.Count;
            for (int i = 0; i < count; i++)
            {
                for (int j = 0; j < 35; j++)
                    Console.Write("-");
                Console.WriteLine($"\n{students[i].Surname} {students[i].Name} {students[i].MiddleName}\n------\nЗачетка №{students[i].RecordNum}\n------");
                PrintRates(students[i].Rates);
                Console.WriteLine($"------\nСредняя оценка: {students[i].AverageRate()}");
            }
        }

        public void PrintStudentsWithAverageOnly(List<Student> students, double min)
        {
            Console.Clear();
            int count = students.Count;
            for (int i = 0; i < count; i++)
                if (students[i].Average >= min)
                    Console.WriteLine($"\n{students[i].Surname} {students[i].Name} {students[i].MiddleName} Средняя оценка: {students[i].Average}");
        }
    }
}
