using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Reduct
{
    internal class EngineManager
    {
        StreamReader reader = new StreamReader("engines.txt");
        public List<Engine> InitEngines()
        {
            List<Engine> engines = new List<Engine>();
            while (reader.ReadLine() != null)
            {
                string[] Line = reader.ReadLine().Split(' ');
                engines.Add(new Engine()
                {
                    Name = Line[0],
                    Power = float.Parse(Line[3]),
                    RotorSpeed = int.Parse(Line[6]),
                    SpeedRange = int.Parse(Line[9])
                });
            }
            return engines;
        }

        public Engine GetEngineByParams(List<Engine> engines, Engine engine)
        {
            for (int i = 0; i < engines.Count; i++)
                if (engine.Power <= engines[i].Power && engine.SpeedRange * 5 >= engines[i].SpeedRange)
                    return engines[i];
            return null;
        }
    }
}
