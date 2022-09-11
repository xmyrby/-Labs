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
            Console.Clear();

            students = students.OrderBy(w => w.Surname).ToList();

            outputController.PrintStudents(students);

            Console.ReadLine();
        }
    }
}
