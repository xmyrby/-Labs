using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SIAOD1
{
    internal class Student
    {
        public string Surname { get; set; }
        public string Name { get; set; }
        public string MiddleName { get; set; }

        public int RecordNum { get; set; }
        public int MyProperty { get; set; }

        public int[] Rates = new int[5];
        public double Average { get; set; }

        public double AverageRate()
        {
            int sum = 0;
            for (int i = 0; i < 5; i++)
                sum += Rates[i];

            Average = (double)sum / 5.0;

            return Average;
        }
    }
}
