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
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        EngineManager eManager = new EngineManager();
        List<Engine> engines = new List<Engine>();

        private void FormMain_Load(object sender, EventArgs e)
        {
            engines = eManager.InitEngines();
        }

        private void buttonCalc_Click(object sender, EventArgs e)
        {
            Engine engine = eManager.GetEngineByParams(engines,new Engine()
            {
                Power = (float)numericUpDownPower.Value,
                SpeedRange = (int)numericUpDownSpeed.Value
            }) ;
        }
    }
}
