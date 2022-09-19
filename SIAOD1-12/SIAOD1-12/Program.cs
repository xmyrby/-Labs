using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace SIAOD1_12
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Введите первое слово: ");
            string oldValue = Console.ReadLine();
            Console.Write("Введите второе слово: ");
            string newValue = Console.ReadLine();
            StreamReader sr = new StreamReader("text.txt");
            string str = sr.ReadToEnd();
            sr.Close();
            str = str.Replace(oldValue, newValue);
            StreamWriter sw = new StreamWriter("text1.txt");
            sw.Write(str);
            sw.Close();
        }
    }
}
