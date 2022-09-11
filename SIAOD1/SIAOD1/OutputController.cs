using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SIAOD1
{
    internal class OutputController
    {
        private void PrintRates(int[] rates)
        {
            int count = rates.Length;
            for (int i = 0; i < count; i++)
                Console.WriteLine($"Предмет №{i} : {rates[i]}");
        }
        public void PrintStudents(List<Student> students)
        {
            int count = students.Count;
            for (int i = 0; i < count; i++)
            {
                for (int j = 0; j < 35; j++)
                    Console.Write("-");
                Console.WriteLine($"\n{students[i].Surname} {students[i].Name} {students[i].MiddleName} №{students[i].RecordNum}");
                PrintRates(students[i].Rates);
                Console.WriteLine($"Средняя оценка: {students[i].AverageRate()}");
            }
        }
    }
}
