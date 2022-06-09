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
        public double inputShaftSpeed = 0;

        private void FormMain_Load(object sender, EventArgs e)
        {
            engines = eManager.InitEngines();
        }

        private void buttonCalc_Click(object sender, EventArgs e)
        {
            Engine engine = eManager.GetEngineByParams(engines, new Engine()
            {
                Power = (float)((double)numericUpDownPower.Value / 0.91),
                SpeedRange = (int)numericUpDownSpeed.Value * 5
            });

            if (engine != null)
            {
                inputShaftSpeed = Math.Round(((double)engine.RotorSpeed / 5), 2);

                textBoxInitialParams.Text = $"Требуемая мощность электродвигателя: {(float)numericUpDownPower.Value}, Квт{Environment.NewLine}Максимальная частота вращения ротора: {engine.SpeedRange} об/мин{Environment.NewLine}{Environment.NewLine}Выбираем электродвигатель: АИР{engine.Name}{Environment.NewLine}{Environment.NewLine}Его характеристики:{Environment.NewLine}Мощность: {engine.Power}, Квт{Environment.NewLine}Номинальная частота вращения ротора: {engine.RotorSpeed} об/мин";

                textBoxCalc.Text = $"Частота вращения на входном валу редуктора = {Math.Round(((double)engine.RotorSpeed / 2), 2) } об/мин\nЧастота вращения на выходном валу редуктора = {inputShaftSpeed} об/мин";
            }
            else
            {
                MessageBox.Show("Нет подходящего по параметрам двигателя");
            }
        }
    }
}
