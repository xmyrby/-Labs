using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mines
{
    internal class Mine
    {
        public int Id { get; set; }
        public long OwnerId { get; set; }
        public int Deep { get; set; }
        public double Income { get; set; }
    }
}
