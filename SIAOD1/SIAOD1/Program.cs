using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SIAOD1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            InputController inputController = new InputController();
            OutputController outputController = new OutputController();

            List<Student> students = inputController.ReadFile();

            outputController.PrintStudents(students);

            Console.ReadLine();

            outputController.SortStudents(students);

            outputController.PrintStudents(students);

            outputController.FilterByAverage(students);

            outputController.PrintStudentsWithAverageOnly(students, double.Parse(Console.ReadLine()));

            Console.ReadLine();
        }
    }
}
