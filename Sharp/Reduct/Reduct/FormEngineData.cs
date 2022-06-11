using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Reduct
{
    public partial class FormEngineData : Form
    {
        List<Engine> engines;
        int id = -1;

        public FormEngineData()
        {
            InitializeComponent();
        }
        void UpdateDGV()
        {
            dataGridViewEngines.Rows.Clear();
            EngineManager eManager = new EngineManager();
            engines = eManager.InitEngines();
            for (int i = 0; i < engines.Count; i++)
            {
                dataGridViewEngines.Rows.Add(engines[i].Name, engines[i].Power, engines[i].RotorSpeed, engines[i].SpeedRange);
            }
        }
        void Save()
        {
            StreamWriter writer = new StreamWriter("engines.txt");
            for (int i = 0; i < engines.Count; i++)
            {
                writer.WriteLine($"{engines[i].Name} P {engines[i].Power} na {engines[i].RotorSpeed} ns {engines[i].SpeedRange}");
            }
            writer.Close();
            UpdateDGV();
        }
        private void FormEngineData_Load(object sender, EventArgs e)
        {
            UpdateDGV();
        }

        private void dataGridViewEngines_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            id = e.RowIndex;
            if (id != -1)
            {
                textBoxName.Text = engines[id].Name;
                numericUpDownPower.Value = (decimal)engines[id].Power;
                numericUpDownSpeed.Value = engines[id].RotorSpeed;
                numericUpDownSpeedRange.Value = engines[id].SpeedRange;
                buttonDelete.Enabled = true;
                buttonEdit.Enabled = true;
            }
            else
            {
                buttonAdd.Enabled = false;
                buttonDelete.Enabled = false;
                buttonEdit.Enabled = false;
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            engines.RemoveAt(id);
            Save();
        }

        private void buttonEdit_Click(object sender, EventArgs e)
        {
            engines[id] = new Engine()
            {
                Name = textBoxName.Text,
                Power = (double)numericUpDownPower.Value,
                RotorSpeed = (int)numericUpDownSpeed.Value,
                SpeedRange = (int)numericUpDownSpeedRange.Value
            };

            Save();
        }

        private void textBoxName_TextChanged(object sender, EventArgs e)
        {
            if (textBoxName.Text != "")
            {
                buttonAdd.Enabled = true;
            }
            else
            {
                buttonAdd.Enabled = false;
            }
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            engines.Add(new Engine()
            {
                Name = textBoxName.Text,
                Power = (double)numericUpDownPower.Value,
                RotorSpeed = (int)numericUpDownSpeed.Value,
                SpeedRange = (int)numericUpDownSpeedRange.Value
            });

            Save();
        }
    }
}
