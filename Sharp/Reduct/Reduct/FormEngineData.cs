using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Reduct
{
    public partial class FormEngineData : Form
    {
        List<Engine> engines;

        public FormEngineData()
        {
            InitializeComponent();
        }

        private void FormEngineData_Load(object sender, EventArgs e)
        {
            EngineManager eManager = new EngineManager();
            engines = eManager.InitEngines();
            for (int i = 0; i < engines.Count; i++)
            {
                dataGridViewEngines.Rows.Add(engines[i].Name, engines[i].Power, engines[i].RotorSpeed, engines[i].SpeedRange);
            }
        }
    }
}
