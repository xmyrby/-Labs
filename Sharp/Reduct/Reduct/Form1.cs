using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using Kompas6API2D5COM;
using Kompas6API3D5COM;
using Kompas6API5;
using Kompas6Constants;
using Kompas6Constants3D;
using KompasAPI7;
using KompasLibrary;

namespace Reduct
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }


        int Z1 = 0;
        double Ob = 10; double U = 0; double M = 0;

        double com_eff = 0.8217; // Общий КПД редуктора CONST
        double com_eff_red = 0.813; // Средний кпд червячного редктора CONST
        double K = 1; // Коэффициент нагрузки 1-постоянная нагрузка CONST
        double perm_cont_press = 140;   // Допустимое контактное напряжение МПа ХЗ ЧТО ЭТО
        double P_work_machine = 0;// требуемая мощность на валу НАШ Power ВВОДИТ ПОЛЬЗОВАТЕЛЬ
        double w3 = 0;                //Частота вращения машины  (входное значение) вроде как наш SpeedRange ВВОДИТ ПОЛЬЗОВАТЕЛЬ?

        //не наши переменные
        double pow;        //Мощность
        double freq;    //Чстота вращения
        double amp;        // Ток при 380В
        double pow_factor; //Коэффициент мощности
        double efficiency;//:string; //КПД

        //RC: TRC;
        //   E:  Engine;
        double //P_work_machine,   //Мощность на валу машины (входное значение)
        P_necessary, //Необходимая мощнось двигателя
        P_engine,// НУЖНО ВЗЯТЬ ПО ДВИГАТЕЛЮ    //Мощность двигателя с учетом характеристик дигателя
        //U,УЖЕ ОБЪЯВЛЕНА           //Общее передатоное число привода  28...50// КОМБОБОКС
        n_nom,        //Номинальная частота вращения э.двигателя
        n_work_machine;//передаточное число ступеней редуктора
                       //Z2, УЖЕ ЗАДАНО            //Число зубъев червяного колеса		 !АНАЛОГИЧНО
                       //m,    УЖЕ ЗАДАНО          //Модуль зацепления  По ГОСТу 2144-66	//КОМБОБОКС ! хз может VGWCylS_1_M - Модуль червяка
        double Mpi = 0;
        double q = 0;              //Коэффициент диаметра червяка (соответствие с гост 19672-74 ) !VGWCylS_1_Da - &Диаметр D
        double T,
            Z2,// Общий вращающий момент 
         T2,               //Вращающий момент червячного колеса
   T1,                //Вращающий момент червяка
   w1,               // частота вращения входного вала
   w2,                // Чстота вращения вала червяного колеса

   aw,                //уточненное межосевое расстояние !		у нас W1 вроде
   d1,                // делительный диаметр червяка !	средний диаметр резьбы червяка d1=m(Модуль зацепления)*q(Коэффициент диаметра червяка)
   a,               // Предварительное межосевое расстояние !	не знаю чем отличается от aw
   da1,               //w
   df1,               //
   p,
   b1,                //
   d2,                // 
   da2,
   d_am2,

   //n_work_machine, //это вроде константа которую вводит пользователь            //
   df2,               //
   b2,
   b1_shaft,
   d1_shaft,                //
   l2_shaft,
   //Длина ступени зубчатого колеса !		хз
   d2_shaft,            //Диаметр ступени зубчатого колеса !	хз
   key2_h,             //высота шпонки чнрвячного колеса !	хз наверное нам не нужно
   w_b,                //Толщина стенок редуктора !	хз наверное оболочка? Ob
   alph; //это угол, хз как его обозначать

        private void buttonEditEngines_Click(object sender, EventArgs e)
        {

        }

        private void button2_Z1UMOb_Click(object sender, EventArgs e)
        {
            SaveInCompas();
        }

        private void numericUpDownPower_ValueChanged(object sender, EventArgs e)
        {
            textBoxInitialParams.Text = "";
            textBoxCalc.Text = "";
            groupBox_Z1UM.Enabled = false;
            groupBox_Calc.Enabled = false;
        }

        private void numericUpDownSpeed_ValueChanged(object sender, EventArgs e)
        {
            textBoxInitialParams.Text = "";
            textBoxCalc.Text = "";
            groupBox_Z1UM.Enabled = false;
            groupBox_Calc.Enabled = false;
        }

        void CheckZUMState()
        {
            groupBox_Calc.Enabled = false;
            if (comboBox_Z1.SelectedIndex != -1 && comboBox_M.SelectedIndex != -1 && comboBox_U.SelectedIndex != -1)
            {
                button_CalcReductor.Enabled = true;
            }
            else
            {
                button_CalcReductor.Enabled = false;
            }
        }

        private void comboBox_Z1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox_Z1.SelectedIndex != -1)
                Z1 = Convert.ToInt32(comboBox_Z1.SelectedItem.ToString());
            CheckZUMState();
        }

        private void numericUpDownOb_ValueChanged(object sender, EventArgs e)
        {
            Ob = Convert.ToDouble(numericUpDownOb.Value.ToString());
            CheckZUMState();
        }

        private void comboBox_M_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox_M.SelectedIndex != -1)
                M = Convert.ToDouble(comboBox_M.SelectedItem.ToString());
            CheckZUMState();
        }

        private void comboBox_U_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox_U.SelectedIndex != -1)
                U = Convert.ToDouble(comboBox_U.SelectedItem.ToString());
            CheckZUMState();
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
                Power = (float)numericUpDownPower.Value,
                SpeedRange = (int)numericUpDownSpeed.Value
            });
            if (engine != null)
            {
                inputShaftSpeed = Math.Round(((double)engine.RotorSpeed / 5), 2);

                textBoxInitialParams.Text = $"Требуемая мощность электродвигателя: {(float)numericUpDownPower.Value}, Квт{Environment.NewLine}Максимальная частота вращения ротора: {engine.SpeedRange} об/мин{Environment.NewLine}{Environment.NewLine}Выбираем электродвигатель: АИР{engine.Name}{Environment.NewLine}{Environment.NewLine}Его характеристики:{Environment.NewLine}Мощность: {engine.Power}, Квт{Environment.NewLine}Номинальная частота вращения ротора: {engine.RotorSpeed} об/мин";

                textBoxCalc.Text = $"Частота вращения на входном валу редуктора = {Math.Round(((double)engine.RotorSpeed / 2), 2) } об/мин\nЧастота вращения на выходном валу редуктора = {inputShaftSpeed} об/мин";

                groupBox_Z1UM.Enabled = true;
            }
            else
            {
                MessageBox.Show("Нет подходящего по параметрам двигателя");
                groupBox_Z1UM.Enabled = false;
                groupBox_Calc.Enabled = false;
            }
        }

        void RewriteCalcBox(Engine engine)
        {
            label7_Type_engine.Text = $"Тип двигателя: АИР{engine.Name}";
            label_Aw.Text = $"Межосевое расстояние: {aw}";
            label7_m.Text = $"Модуль зацепления: {M}";
            label7_alph.Text = $"Угол профиля: {alph}";
            label7_P.Text = $"Шаг зубьев: {p}";
            label8_DaM2.Text = $"Наибольший диаметр зубчатого колеса, DaM2: {0}"; // DaN2 чо за хуйня???????
            label9_d2.Text = $"Делительный диаметр зубчатого колеса: {d2}";
            label10_df2.Text = $"Диаметр впадин зубьев зубчатого колеса: {df2}";
            label11_b2.Text = $"Ширина венца зубчатого колеса: {b2}";
            label12_Z2.Text = $"Число зубьев зубчатого колеса: {Z2}";
            label14_da2.Text = $"Диаметр вершин зубьев зубчатого колеса: {da2}";
            label12_Z2.Text = $"Число заходов червяка: {Z1}";
            label17_df1.Text = $"Диаметр впадин витков червяка: {df1}";
            label18_b1.Text = $"Ширина витков червяка: {b1}";
            label19_d1.Text = $"Делительный диаметр червяка: {d1}";
            label20_da1.Text = $"Диаметр вершин витков червяка: {da1}";
        }

        void SaveInCompas()
        {
            try
            {
                KompasObject kompas = (KompasObject)Marshal.GetActiveObject("KOMPAS.Application.5"); //Возможно открытие апликации или что-то подобное... Не шарю за компас может прокатит
                ksDocument3D kompas_document_3d = (ksDocument3D)kompas.ActiveDocument3D();
                ksPart kPart = kompas_document_3d.GetPart((int)Part_Type.pTop_Part);
                ksVariableCollection varcoll = kPart.VariableCollection(); //Получаем коллекцию параметров
                varcoll.refresh();

                //Устанавливаем значение в проге на значение из коллекции (По имени)
                //Тут уже сам все переменные думаю разберешься как добавишь

                //ksVariable D1 = varcoll.GetByName("D1", true, true);
                //ksVariable D2 = varcoll.GetByName("D2", true, true);
                //ksVariable B1 = varcoll.GetByName("B1", true, true);
                //ksVariable B2 = varcoll.GetByName("B2", true, true);
                //ksVariable ShaftWidth2 = varcoll.GetByName("ShaftWidth2", true, true);
                //ksVariable centerDist = varcoll.GetByName("centerDist", true, true);

                //Далее задаём переменным из компаса значения переменных, которые мы рассчитали, после чего перестраиваем модель

                //ShaftWidth2.value = shaftWidth2;
                //D1.value = d1;
                //D2.value = d2;
                //B1.value = b1;
                //B2.value = b2;
                //centerDist.value = centerDistance;
                //kPart.RebuildModel();
            }
            catch
            {
                MessageBox.Show("Упсссс... Что-то пошло не так.");
            }
        }

        private void button_CalcReductor_Click(object sender, EventArgs e)
        {
            // int Z1;
            //Z1 = (int)numericUpDownPower.Value;
            Engine engine = eManager.GetEngineByParams(engines, new Engine()
            {
                SpeedRange = (int)numericUpDownSpeed.Value
            });


            Z1 = Convert.ToInt32(comboBox_Z1.SelectedItem.ToString());

            alph = 20;
            P_work_machine = Convert.ToDouble(numericUpDownPower.Value.ToString());
            n_work_machine = Convert.ToDouble(numericUpDownSpeed.Value.ToString());

            P_necessary = P_work_machine / com_eff;

            //E= EngineChoice(P_work_machine, n_work_machine);
            // выбор двигателя по необходимой мощности


            P_engine = Convert.ToDouble(numericUpDownPower.Value.ToString());

            n_nom = Convert.ToDouble(numericUpDownSpeed.Value.ToString());



            w1 = (Math.PI * n_nom) / 30;
            w3 = (Math.PI * n_work_machine) / 30;
            n_work_machine = (w3 * 30) / Math.PI;
            //U:= u_Gost(n_nom / n_work_machine);//У НАС УЖЕ ЕСТЬ. ИЗ КОМБОБОКСА ВЗЯЛИ


            T1 = (P_engine * 1000) / w1;
            T2 = T1 * U * com_eff_red;
            w2 = w1 / U;
            Z2 = U * Z1;

            T = Math.Exp(Math.Log(Math.Exp(Math.Log(perm_cont_press * Math.Exp(Math.Log(10) * 6)) * 2)) * (1 / 3));
            a = (6100 * ((Math.Exp(Math.Log(K * T2) * (1 / 3))) / T)) * 1000;

            //НАДО ПОСЧИТАТЬ НА ШАРПЕ t= exp(ln(exp(ln(perm_cont_press * exp(ln(10) * 6)) * 2)) * (1 / 3));
            //НАДО ПОСЧИТАТЬ НА ШАРПЕ  a= (6100 * ((exp(ln(K * T2) * (1 / 3))) / t)) * 1000;

            q = (Z2 / 4);


            aw = 0.5 * M * (q + Z2);
            q = ((2 * aw) / M) - Z2;
            p = Math.Abs(Math.Round(Math.PI * M, 2));

            d1 = M * q;
            da1 = d1 + 2 * M;
            df1 = d1 - 2.4 * M;
            b1 = M * (11 + 0.06 * Z2);
            b1_shaft = 50 + (1.5 * b1);
            if ((d1 / 2) > 10)
            {
                d1_shaft = (d1 / 2);
            }

            d2 = M * Z2;
            da2 = d2 + 2 * M;
            df2 = d2 - 2.4 * M;
            d_am2 = da2 + ((6 * M) / (Z1 + 2));
            b2 = 0.75 * da1;
            d2_shaft = /*bearing_GOST*/(d2 * 0.6);
            d1_shaft = /*bearing_GOST*/(d1 * 0.6);
            l2_shaft = b2 * 3;
            key2_h = (d_am2 / 15);
            w_b = Math.Abs(0.04 * aw + 2);
            if (d_am2 <= 500)
            {
                l2_shaft = 500 + w_b + (d2_shaft / 10) + 10;
            }
            else
            {
                l2_shaft = 1000 + w_b + (d2_shaft / 10) + 10;
            }

            groupBox_Calc.Enabled = true;

            RewriteCalcBox(engine);
        }

        private void button2_ClearZ1UMOb_Click(object sender, EventArgs e)
        {
            Z1 = 0; U = 0; M = 0;
            comboBox_Z1.SelectedIndex = -1;
            comboBox_U.SelectedIndex = -1;
            comboBox_M.SelectedIndex = -1;
        }
    }
}
