using System;
using System.Collections.Generic;
using System.IO;

namespace SIAOD1
{
    internal class InputController
    {
        private int[] GetRates(string[] rtLine)
        {
            int[] rates = new int[5];

            int count = rtLine.Length;

            for (int i = 4; i < count; i++)
                rates[i - 4] = Int32.Parse(rtLine[i]);

            return rates;
        }
        public List<Student> ReadFile()
        {
            List<Student> students = new List<Student>();

            StreamReader reader = new StreamReader("students.txt");

            while (reader.Peek() != -1)
            {
                string[] st = reader.ReadLine().Split(' ');
                students.Add(new Student()
                {
                    Surname = st[0],
                    Name = st[1],
                    MiddleName = st[2],
                    RecordNum = Int32.Parse(st[3]),
                    Rates = GetRates(st),
                });
            }

            reader.Close();

            return students;
        }
    }
}
