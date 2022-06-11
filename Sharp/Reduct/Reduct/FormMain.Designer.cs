/*namespace Reduct
{
    partial class FormMain
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBoxEngine = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDownPower = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.numericUpDownSpeed = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxInitialParams = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxCalc = new System.Windows.Forms.TextBox();
            this.buttonCalc = new System.Windows.Forms.Button();
            this.groupBoxEngine.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPower)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpeed)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxEngine
            // 
            this.groupBoxEngine.Controls.Add(this.buttonCalc);
            this.groupBoxEngine.Controls.Add(this.textBoxCalc);
            this.groupBoxEngine.Controls.Add(this.label5);
            this.groupBoxEngine.Controls.Add(this.textBoxInitialParams);
            this.groupBoxEngine.Controls.Add(this.label4);
            this.groupBoxEngine.Controls.Add(this.numericUpDownSpeed);
            this.groupBoxEngine.Controls.Add(this.label3);
            this.groupBoxEngine.Controls.Add(this.numericUpDownPower);
            this.groupBoxEngine.Controls.Add(this.label2);
            this.groupBoxEngine.Controls.Add(this.label1);
            this.groupBoxEngine.Location = new System.Drawing.Point(12, 12);
            this.groupBoxEngine.Name = "groupBoxEngine";
            this.groupBoxEngine.Size = new System.Drawing.Size(377, 340);
            this.groupBoxEngine.TabIndex = 0;
            this.groupBoxEngine.TabStop = false;
            this.groupBoxEngine.Text = "1. Выбор двигателя";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(159, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Требуемая мощность на валу";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(306, 28);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(26, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "КВт";
            // 
            // numericUpDownPower
            // 
            this.numericUpDownPower.DecimalPlaces = 2;
            this.numericUpDownPower.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownPower.Location = new System.Drawing.Point(197, 26);
            this.numericUpDownPower.Maximum = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.numericUpDownPower.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownPower.Name = "numericUpDownPower";
            this.numericUpDownPower.Size = new System.Drawing.Size(103, 20);
            this.numericUpDownPower.TabIndex = 3;
            this.numericUpDownPower.ThousandsSeparator = true;
            this.numericUpDownPower.Value = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 59);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(172, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Необходимая частота вращения";
            // 
            // numericUpDownSpeed
            // 
            this.numericUpDownSpeed.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numericUpDownSpeed.Location = new System.Drawing.Point(197, 57);
            this.numericUpDownSpeed.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownSpeed.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numericUpDownSpeed.Name = "numericUpDownSpeed";
            this.numericUpDownSpeed.Size = new System.Drawing.Size(103, 20);
            this.numericUpDownSpeed.TabIndex = 5;
            this.numericUpDownSpeed.ThousandsSeparator = true;
            this.numericUpDownSpeed.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(306, 59);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Об / Мин";
            // 
            // textBoxInitialParams
            // 
            this.textBoxInitialParams.Location = new System.Drawing.Point(18, 83);
            this.textBoxInitialParams.Multiline = true;
            this.textBoxInitialParams.Name = "textBoxInitialParams";
            this.textBoxInitialParams.ReadOnly = true;
            this.textBoxInitialParams.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxInitialParams.Size = new System.Drawing.Size(341, 124);
            this.textBoxInitialParams.TabIndex = 7;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(15, 219);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(184, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Кинематический расчёт двигателя";
            // 
            // textBoxCalc
            // 
            this.textBoxCalc.Location = new System.Drawing.Point(18, 235);
            this.textBoxCalc.Multiline = true;
            this.textBoxCalc.Name = "textBoxCalc";
            this.textBoxCalc.ReadOnly = true;
            this.textBoxCalc.ScrollBars = System.Windows.Forms.ScrollBars.Horizontal;
            this.textBoxCalc.Size = new System.Drawing.Size(341, 54);
            this.textBoxCalc.TabIndex = 9;
            // 
            // buttonCalc
            // 
            this.buttonCalc.Location = new System.Drawing.Point(18, 295);
            this.buttonCalc.Name = "buttonCalc";
            this.buttonCalc.Size = new System.Drawing.Size(341, 33);
            this.buttonCalc.TabIndex = 10;
            this.buttonCalc.Text = "Сделать расчёт двигателя";
            this.buttonCalc.UseVisualStyleBackColor = true;
            this.buttonCalc.Click += new System.EventHandler(this.buttonCalc_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.groupBoxEngine);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormMain";
            this.ShowIcon = false;
            this.Text = "Reduct";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.groupBoxEngine.ResumeLayout(false);
            this.groupBoxEngine.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPower)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpeed)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxEngine;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDownPower;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numericUpDownSpeed;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxInitialParams;
        private System.Windows.Forms.TextBox textBoxCalc;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button buttonCalc;
    }
}

*/
namespace Reduct
{
    partial class FormMain
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }
        #region Код, автоматически созданный конструктором форм Windows
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBoxEngine = new System.Windows.Forms.GroupBox();
            this.buttonEditEngines = new System.Windows.Forms.Button();
            this.buttonCalc = new System.Windows.Forms.Button();
            this.textBoxCalc = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxInitialParams = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.numericUpDownSpeed = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.numericUpDownPower = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox_Z1UM = new System.Windows.Forms.GroupBox();
            this.button_CalcReductor = new System.Windows.Forms.Button();
            this.numericUpDownOb = new System.Windows.Forms.NumericUpDown();
            this.button2_ClearZ1UMOb = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label6 = new System.Windows.Forms.Label();
            this.comboBox_M = new System.Windows.Forms.ComboBox();
            this.comboBox_U = new System.Windows.Forms.ComboBox();
            this.comboBox_Z1 = new System.Windows.Forms.ComboBox();
            this.label6_M = new System.Windows.Forms.Label();
            this.label6_U = new System.Windows.Forms.Label();
            this.label6_Z1 = new System.Windows.Forms.Label();
            this.button2_Z1UMOb = new System.Windows.Forms.Button();
            this.groupBox_Calc = new System.Windows.Forms.GroupBox();
            this.label20_da1 = new System.Windows.Forms.Label();
            this.label19_d1 = new System.Windows.Forms.Label();
            this.label17_df1 = new System.Windows.Forms.Label();
            this.label14_da2 = new System.Windows.Forms.Label();
            this.label13_Z1 = new System.Windows.Forms.Label();
            this.label12_Z2 = new System.Windows.Forms.Label();
            this.label11_b2 = new System.Windows.Forms.Label();
            this.label10_df2 = new System.Windows.Forms.Label();
            this.label8_DaM2 = new System.Windows.Forms.Label();
            this.label7_P = new System.Windows.Forms.Label();
            this.label7_alph = new System.Windows.Forms.Label();
            this.label7_m = new System.Windows.Forms.Label();
            this.label_Aw = new System.Windows.Forms.Label();
            this.label7_Type_engine = new System.Windows.Forms.Label();
            this.label18_b1 = new System.Windows.Forms.Label();
            this.label9_d2 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBoxEngine.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpeed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPower)).BeginInit();
            this.groupBox_Z1UM.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownOb)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox_Calc.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxEngine
            // 
            this.groupBoxEngine.Controls.Add(this.buttonEditEngines);
            this.groupBoxEngine.Controls.Add(this.buttonCalc);
            this.groupBoxEngine.Controls.Add(this.textBoxCalc);
            this.groupBoxEngine.Controls.Add(this.label5);
            this.groupBoxEngine.Controls.Add(this.textBoxInitialParams);
            this.groupBoxEngine.Controls.Add(this.label4);
            this.groupBoxEngine.Controls.Add(this.numericUpDownSpeed);
            this.groupBoxEngine.Controls.Add(this.label3);
            this.groupBoxEngine.Controls.Add(this.numericUpDownPower);
            this.groupBoxEngine.Controls.Add(this.label2);
            this.groupBoxEngine.Controls.Add(this.label1);
            this.groupBoxEngine.Location = new System.Drawing.Point(12, 12);
            this.groupBoxEngine.Name = "groupBoxEngine";
            this.groupBoxEngine.Size = new System.Drawing.Size(377, 405);
            this.groupBoxEngine.TabIndex = 0;
            this.groupBoxEngine.TabStop = false;
            this.groupBoxEngine.Text = "1. Выбор двигателя";
            // 
            // buttonEditEngines
            // 
            this.buttonEditEngines.Location = new System.Drawing.Point(18, 345);
            this.buttonEditEngines.Name = "buttonEditEngines";
            this.buttonEditEngines.Size = new System.Drawing.Size(341, 26);
            this.buttonEditEngines.TabIndex = 11;
            this.buttonEditEngines.Text = "База двигателей";
            this.buttonEditEngines.UseVisualStyleBackColor = true;
            this.buttonEditEngines.Click += new System.EventHandler(this.buttonEditEngines_Click);
            // 
            // buttonCalc
            // 
            this.buttonCalc.Location = new System.Drawing.Point(18, 295);
            this.buttonCalc.Name = "buttonCalc";
            this.buttonCalc.Size = new System.Drawing.Size(341, 33);
            this.buttonCalc.TabIndex = 10;
            this.buttonCalc.Text = "Сделать расчёт двигателя";
            this.buttonCalc.UseVisualStyleBackColor = true;
            this.buttonCalc.Click += new System.EventHandler(this.buttonCalc_Click);
            // 
            // textBoxCalc
            // 
            this.textBoxCalc.Location = new System.Drawing.Point(18, 235);
            this.textBoxCalc.Multiline = true;
            this.textBoxCalc.Name = "textBoxCalc";
            this.textBoxCalc.ReadOnly = true;
            this.textBoxCalc.ScrollBars = System.Windows.Forms.ScrollBars.Horizontal;
            this.textBoxCalc.Size = new System.Drawing.Size(341, 54);
            this.textBoxCalc.TabIndex = 9;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(15, 219);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(184, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Кинематический расчёт двигателя";
            // 
            // textBoxInitialParams
            // 
            this.textBoxInitialParams.Location = new System.Drawing.Point(18, 83);
            this.textBoxInitialParams.Multiline = true;
            this.textBoxInitialParams.Name = "textBoxInitialParams";
            this.textBoxInitialParams.ReadOnly = true;
            this.textBoxInitialParams.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxInitialParams.Size = new System.Drawing.Size(341, 124);
            this.textBoxInitialParams.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(306, 59);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Об / Мин";
            // 
            // numericUpDownSpeed
            // 
            this.numericUpDownSpeed.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numericUpDownSpeed.Location = new System.Drawing.Point(197, 57);
            this.numericUpDownSpeed.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownSpeed.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numericUpDownSpeed.Name = "numericUpDownSpeed";
            this.numericUpDownSpeed.Size = new System.Drawing.Size(103, 20);
            this.numericUpDownSpeed.TabIndex = 5;
            this.numericUpDownSpeed.ThousandsSeparator = true;
            this.numericUpDownSpeed.Value = new decimal(new int[] {
            150,
            0,
            0,
            0});
            this.numericUpDownSpeed.ValueChanged += new System.EventHandler(this.numericUpDownSpeed_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 59);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(172, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Необходимая частота вращения";
            // 
            // numericUpDownPower
            // 
            this.numericUpDownPower.DecimalPlaces = 2;
            this.numericUpDownPower.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownPower.Location = new System.Drawing.Point(197, 26);
            this.numericUpDownPower.Maximum = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.numericUpDownPower.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownPower.Name = "numericUpDownPower";
            this.numericUpDownPower.Size = new System.Drawing.Size(103, 20);
            this.numericUpDownPower.TabIndex = 3;
            this.numericUpDownPower.ThousandsSeparator = true;
            this.numericUpDownPower.Value = new decimal(new int[] {
            120,
            0,
            0,
            65536});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(306, 28);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(26, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "КВт";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(159, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Требуемая мощность на валу";
            // 
            // groupBox_Z1UM
            // 
            this.groupBox_Z1UM.Controls.Add(this.button_CalcReductor);
            this.groupBox_Z1UM.Controls.Add(this.numericUpDownOb);
            this.groupBox_Z1UM.Controls.Add(this.button2_ClearZ1UMOb);
            this.groupBox_Z1UM.Controls.Add(this.label9);
            this.groupBox_Z1UM.Controls.Add(this.label8);
            this.groupBox_Z1UM.Controls.Add(this.label7);
            this.groupBox_Z1UM.Controls.Add(this.pictureBox3);
            this.groupBox_Z1UM.Controls.Add(this.pictureBox2);
            this.groupBox_Z1UM.Controls.Add(this.pictureBox1);
            this.groupBox_Z1UM.Controls.Add(this.label6);
            this.groupBox_Z1UM.Controls.Add(this.comboBox_M);
            this.groupBox_Z1UM.Controls.Add(this.comboBox_U);
            this.groupBox_Z1UM.Controls.Add(this.comboBox_Z1);
            this.groupBox_Z1UM.Controls.Add(this.label6_M);
            this.groupBox_Z1UM.Controls.Add(this.label6_U);
            this.groupBox_Z1UM.Controls.Add(this.label6_Z1);
            this.groupBox_Z1UM.Enabled = false;
            this.groupBox_Z1UM.Location = new System.Drawing.Point(395, 12);
            this.groupBox_Z1UM.Name = "groupBox_Z1UM";
            this.groupBox_Z1UM.Size = new System.Drawing.Size(564, 170);
            this.groupBox_Z1UM.TabIndex = 1;
            this.groupBox_Z1UM.TabStop = false;
            this.groupBox_Z1UM.Text = "2. Ключевые параметры передачи";
            // 
            // button_CalcReductor
            // 
            this.button_CalcReductor.Enabled = false;
            this.button_CalcReductor.Location = new System.Drawing.Point(124, 141);
            this.button_CalcReductor.Name = "button_CalcReductor";
            this.button_CalcReductor.Size = new System.Drawing.Size(214, 23);
            this.button_CalcReductor.TabIndex = 11;
            this.button_CalcReductor.Text = "Сделать расчёт червячного редуктора";
            this.button_CalcReductor.UseVisualStyleBackColor = true;
            this.button_CalcReductor.Click += new System.EventHandler(this.button_CalcReductor_Click);
            // 
            // numericUpDownOb
            // 
            this.numericUpDownOb.DecimalPlaces = 2;
            this.numericUpDownOb.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownOb.Location = new System.Drawing.Point(152, 113);
            this.numericUpDownOb.Maximum = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.numericUpDownOb.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownOb.Name = "numericUpDownOb";
            this.numericUpDownOb.Size = new System.Drawing.Size(75, 20);
            this.numericUpDownOb.TabIndex = 11;
            this.numericUpDownOb.ThousandsSeparator = true;
            this.numericUpDownOb.Value = new decimal(new int[] {
            100,
            0,
            0,
            65536});
            this.numericUpDownOb.ValueChanged += new System.EventHandler(this.numericUpDownOb_ValueChanged);
            // 
            // button2_ClearZ1UMOb
            // 
            this.button2_ClearZ1UMOb.Location = new System.Drawing.Point(9, 141);
            this.button2_ClearZ1UMOb.Name = "button2_ClearZ1UMOb";
            this.button2_ClearZ1UMOb.Size = new System.Drawing.Size(109, 23);
            this.button2_ClearZ1UMOb.TabIndex = 25;
            this.button2_ClearZ1UMOb.Text = "Очистить";
            this.button2_ClearZ1UMOb.UseVisualStyleBackColor = true;
            this.button2_ClearZ1UMOb.Click += new System.EventHandler(this.button2_ClearZ1UMOb_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(479, 9);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 13);
            this.label9.TabIndex = 23;
            this.label9.Text = "Редуктор";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(373, 9);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(44, 13);
            this.label8.TabIndex = 22;
            this.label8.Text = "Колесо";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(264, 9);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(45, 13);
            this.label7.TabIndex = 21;
            this.label7.Text = "Червяк";
            // 
            // pictureBox3
            // 
            this.pictureBox3.Image = global::Reduct.Properties.Resources.img_Gear;
            this.pictureBox3.Location = new System.Drawing.Point(455, 25);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(105, 124);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox3.TabIndex = 20;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = global::Reduct.Properties.Resources.img_WormShaft;
            this.pictureBox2.Location = new System.Drawing.Point(233, 25);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(105, 124);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox2.TabIndex = 19;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::Reduct.Properties.Resources.img_Wheel;
            this.pictureBox1.Location = new System.Drawing.Point(344, 25);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(105, 124);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 18;
            this.pictureBox1.TabStop = false;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(19, 116);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(136, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "Толщина стенки (Ob), mm";
            // 
            // comboBox_M
            // 
            this.comboBox_M.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_M.FormattingEnabled = true;
            this.comboBox_M.Items.AddRange(new object[] {
            "2,5",
            "3,15",
            "4",
            "5",
            "6,3",
            "8",
            "10",
            "12,5",
            "16"});
            this.comboBox_M.Location = new System.Drawing.Point(176, 86);
            this.comboBox_M.Name = "comboBox_M";
            this.comboBox_M.Size = new System.Drawing.Size(51, 21);
            this.comboBox_M.TabIndex = 16;
            this.comboBox_M.SelectedIndexChanged += new System.EventHandler(this.comboBox_M_SelectedIndexChanged);
            // 
            // comboBox_U
            // 
            this.comboBox_U.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_U.FormattingEnabled = true;
            this.comboBox_U.Items.AddRange(new object[] {
            "8",
            "10",
            "12,5",
            "16",
            "20"});
            this.comboBox_U.Location = new System.Drawing.Point(176, 56);
            this.comboBox_U.Name = "comboBox_U";
            this.comboBox_U.Size = new System.Drawing.Size(51, 21);
            this.comboBox_U.TabIndex = 15;
            this.comboBox_U.SelectedIndexChanged += new System.EventHandler(this.comboBox_U_SelectedIndexChanged);
            // 
            // comboBox_Z1
            // 
            this.comboBox_Z1.DisplayMember = "1";
            this.comboBox_Z1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_Z1.FormattingEnabled = true;
            this.comboBox_Z1.Items.AddRange(new object[] {
            "1",
            "2",
            "4"});
            this.comboBox_Z1.Location = new System.Drawing.Point(176, 25);
            this.comboBox_Z1.Name = "comboBox_Z1";
            this.comboBox_Z1.Size = new System.Drawing.Size(51, 21);
            this.comboBox_Z1.TabIndex = 14;
            this.comboBox_Z1.SelectedIndexChanged += new System.EventHandler(this.comboBox_Z1_SelectedIndexChanged);
            // 
            // label6_M
            // 
            this.label6_M.AutoSize = true;
            this.label6_M.Location = new System.Drawing.Point(19, 86);
            this.label6_M.Name = "label6_M";
            this.label6_M.Size = new System.Drawing.Size(101, 13);
            this.label6_M.TabIndex = 13;
            this.label6_M.Text = "Модуль зубьев (М)";
            // 
            // label6_U
            // 
            this.label6_U.AutoSize = true;
            this.label6_U.Location = new System.Drawing.Point(19, 59);
            this.label6_U.Name = "label6_U";
            this.label6_U.Size = new System.Drawing.Size(128, 13);
            this.label6_U.TabIndex = 12;
            this.label6_U.Text = "Передаточное число (U)";
            // 
            // label6_Z1
            // 
            this.label6_Z1.AutoSize = true;
            this.label6_Z1.Location = new System.Drawing.Point(19, 28);
            this.label6_Z1.Name = "label6_Z1";
            this.label6_Z1.Size = new System.Drawing.Size(151, 13);
            this.label6_Z1.TabIndex = 11;
            this.label6_Z1.Text = "Количество зацеплений (Z1)";
            // 
            // button2_Z1UMOb
            // 
            this.button2_Z1UMOb.Location = new System.Drawing.Point(6, 191);
            this.button2_Z1UMOb.Name = "button2_Z1UMOb";
            this.button2_Z1UMOb.Size = new System.Drawing.Size(151, 32);
            this.button2_Z1UMOb.TabIndex = 24;
            this.button2_Z1UMOb.Text = "Перестроить модель";
            this.button2_Z1UMOb.UseVisualStyleBackColor = true;
            this.button2_Z1UMOb.Click += new System.EventHandler(this.button2_Z1UMOb_Click);
            // 
            // groupBox_Calc
            // 
            this.groupBox_Calc.Controls.Add(this.label10);
            this.groupBox_Calc.Controls.Add(this.label18_b1);
            this.groupBox_Calc.Controls.Add(this.button2_Z1UMOb);
            this.groupBox_Calc.Controls.Add(this.label20_da1);
            this.groupBox_Calc.Controls.Add(this.label19_d1);
            this.groupBox_Calc.Controls.Add(this.label17_df1);
            this.groupBox_Calc.Controls.Add(this.label14_da2);
            this.groupBox_Calc.Controls.Add(this.label13_Z1);
            this.groupBox_Calc.Controls.Add(this.label12_Z2);
            this.groupBox_Calc.Controls.Add(this.label11_b2);
            this.groupBox_Calc.Controls.Add(this.label10_df2);
            this.groupBox_Calc.Controls.Add(this.label9_d2);
            this.groupBox_Calc.Controls.Add(this.label8_DaM2);
            this.groupBox_Calc.Controls.Add(this.label7_P);
            this.groupBox_Calc.Controls.Add(this.label7_alph);
            this.groupBox_Calc.Controls.Add(this.label7_m);
            this.groupBox_Calc.Controls.Add(this.label_Aw);
            this.groupBox_Calc.Controls.Add(this.label7_Type_engine);
            this.groupBox_Calc.Enabled = false;
            this.groupBox_Calc.Location = new System.Drawing.Point(395, 188);
            this.groupBox_Calc.Name = "groupBox_Calc";
            this.groupBox_Calc.Size = new System.Drawing.Size(564, 229);
            this.groupBox_Calc.TabIndex = 17;
            this.groupBox_Calc.TabStop = false;
            this.groupBox_Calc.Text = "3. Параметры червячной передачи";
            // 
            // label20_da1
            // 
            this.label20_da1.AutoSize = true;
            this.label20_da1.Location = new System.Drawing.Point(320, 116);
            this.label20_da1.Name = "label20_da1";
            this.label20_da1.Size = new System.Drawing.Size(200, 13);
            this.label20_da1.TabIndex = 28;
            this.label20_da1.Text = "Диаметр вершин витков червяка, da1";
            // 
            // label19_d1
            // 
            this.label19_d1.AutoSize = true;
            this.label19_d1.Location = new System.Drawing.Point(320, 103);
            this.label19_d1.Name = "label19_d1";
            this.label19_d1.Size = new System.Drawing.Size(185, 13);
            this.label19_d1.TabIndex = 27;
            this.label19_d1.Text = "Делительный диаметр червяка, d1";
            // 
            // label17_df1
            // 
            this.label17_df1.AutoSize = true;
            this.label17_df1.Location = new System.Drawing.Point(320, 77);
            this.label17_df1.Name = "label17_df1";
            this.label17_df1.Size = new System.Drawing.Size(195, 13);
            this.label17_df1.TabIndex = 26;
            this.label17_df1.Text = "Диаметр впадин витков червяка, df1";
            // 
            // label14_da2
            // 
            this.label14_da2.AutoSize = true;
            this.label14_da2.Location = new System.Drawing.Point(8, 155);
            this.label14_da2.Name = "label14_da2";
            this.label14_da2.Size = new System.Drawing.Size(248, 13);
            this.label14_da2.TabIndex = 24;
            this.label14_da2.Text = "Диаметр вершин зубьев зубчатого колеса, da2";
            // 
            // label13_Z1
            // 
            this.label13_Z1.AutoSize = true;
            this.label13_Z1.Location = new System.Drawing.Point(320, 64);
            this.label13_Z1.Name = "label13_Z1";
            this.label13_Z1.Size = new System.Drawing.Size(146, 13);
            this.label13_Z1.TabIndex = 24;
            this.label13_Z1.Text = "Число заходов червяка, Z1";
            // 
            // label12_Z2
            // 
            this.label12_Z2.AutoSize = true;
            this.label12_Z2.Location = new System.Drawing.Point(9, 142);
            this.label12_Z2.Name = "label12_Z2";
            this.label12_Z2.Size = new System.Drawing.Size(188, 13);
            this.label12_Z2.TabIndex = 23;
            this.label12_Z2.Text = "Число зубьев зубчатого колеса, Z2";
            // 
            // label11_b2
            // 
            this.label11_b2.AutoSize = true;
            this.label11_b2.Location = new System.Drawing.Point(8, 129);
            this.label11_b2.Name = "label11_b2";
            this.label11_b2.Size = new System.Drawing.Size(189, 13);
            this.label11_b2.TabIndex = 22;
            this.label11_b2.Text = "Ширина венца зубчатого колеса, b2";
            // 
            // label10_df2
            // 
            this.label10_df2.AutoSize = true;
            this.label10_df2.Location = new System.Drawing.Point(7, 116);
            this.label10_df2.Name = "label10_df2";
            this.label10_df2.Size = new System.Drawing.Size(243, 13);
            this.label10_df2.TabIndex = 21;
            this.label10_df2.Text = "Диаметр впадин зубьев зубчатого колеса, df2";
            // 
            // label8_DaM2
            // 
            this.label8_DaM2.AutoSize = true;
            this.label8_DaM2.Location = new System.Drawing.Point(8, 90);
            this.label8_DaM2.Name = "label8_DaM2";
            this.label8_DaM2.Size = new System.Drawing.Size(244, 13);
            this.label8_DaM2.TabIndex = 19;
            this.label8_DaM2.Text = "Наибольший диаметр зубчатого колеса, DaM2";
            // 
            // label7_P
            // 
            this.label7_P.AutoSize = true;
            this.label7_P.Location = new System.Drawing.Point(9, 68);
            this.label7_P.Name = "label7_P";
            this.label7_P.Size = new System.Drawing.Size(78, 13);
            this.label7_P.TabIndex = 18;
            this.label7_P.Text = "Шаг зубьев, P";
            // 
            // label7_alph
            // 
            this.label7_alph.AutoSize = true;
            this.label7_alph.Location = new System.Drawing.Point(9, 55);
            this.label7_alph.Name = "label7_alph";
            this.label7_alph.Size = new System.Drawing.Size(105, 13);
            this.label7_alph.TabIndex = 17;
            this.label7_alph.Text = "Угол профиля, alph";
            // 
            // label7_m
            // 
            this.label7_m.AutoSize = true;
            this.label7_m.Location = new System.Drawing.Point(7, 42);
            this.label7_m.Name = "label7_m";
            this.label7_m.Size = new System.Drawing.Size(125, 13);
            this.label7_m.TabIndex = 16;
            this.label7_m.Text = "Модуль зацепления, m ";
            // 
            // label_Aw
            // 
            this.label_Aw.AutoSize = true;
            this.label_Aw.Location = new System.Drawing.Point(6, 29);
            this.label_Aw.Name = "label_Aw";
            this.label_Aw.Size = new System.Drawing.Size(151, 13);
            this.label_Aw.TabIndex = 15;
            this.label_Aw.Text = "Межосевое расстояние, aw ";
            // 
            // label7_Type_engine
            // 
            this.label7_Type_engine.AutoSize = true;
            this.label7_Type_engine.Location = new System.Drawing.Point(6, 16);
            this.label7_Type_engine.Name = "label7_Type_engine";
            this.label7_Type_engine.Size = new System.Drawing.Size(84, 13);
            this.label7_Type_engine.TabIndex = 14;
            this.label7_Type_engine.Text = "Тип двигателя:";
            // 
            // label18_b1
            // 
            this.label18_b1.AutoSize = true;
            this.label18_b1.Location = new System.Drawing.Point(320, 90);
            this.label18_b1.Name = "label18_b1";
            this.label18_b1.Size = new System.Drawing.Size(146, 13);
            this.label18_b1.TabIndex = 29;
            this.label18_b1.Text = "Ширина витков червяка, b1";
            // 
            // label9_d2
            // 
            this.label9_d2.AutoSize = true;
            this.label9_d2.Location = new System.Drawing.Point(8, 103);
            this.label9_d2.Name = "label9_d2";
            this.label9_d2.Size = new System.Drawing.Size(233, 13);
            this.label9_d2.TabIndex = 20;
            this.label9_d2.Text = "Делительный диаметр зубчатого колеса, d2";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label10.ForeColor = System.Drawing.Color.Brown;
            this.label10.Location = new System.Drawing.Point(174, 205);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(262, 9);
            this.label10.TabIndex = 30;
            this.label10.Text = "*НЕОБХОДИМО УБЕДИТЬСЯ, ЧТО ПРОЕКТ С МОДЕЛЬЮ ОТКРЫТ*";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(962, 421);
            this.Controls.Add(this.groupBox_Calc);
            this.Controls.Add(this.groupBox_Z1UM);
            this.Controls.Add(this.groupBoxEngine);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormMain";
            this.ShowIcon = false;
            this.Text = "Reduct";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.groupBoxEngine.ResumeLayout(false);
            this.groupBoxEngine.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpeed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPower)).EndInit();
            this.groupBox_Z1UM.ResumeLayout(false);
            this.groupBox_Z1UM.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownOb)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox_Calc.ResumeLayout(false);
            this.groupBox_Calc.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBoxEngine;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDownPower;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numericUpDownSpeed;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxInitialParams;
        private System.Windows.Forms.TextBox textBoxCalc;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button buttonCalc;
        private System.Windows.Forms.GroupBox groupBox_Z1UM;
        private System.Windows.Forms.Label label6_Z1;
        private System.Windows.Forms.Label label6_M;
        private System.Windows.Forms.Label label6_U;
        private System.Windows.Forms.ComboBox comboBox_Z1;
        private System.Windows.Forms.ComboBox comboBox_M;
        private System.Windows.Forms.ComboBox comboBox_U;
        private System.Windows.Forms.GroupBox groupBox_Calc;
        private System.Windows.Forms.Label label20_da1;
        private System.Windows.Forms.Label label19_d1;
        private System.Windows.Forms.Label label17_df1;
        private System.Windows.Forms.Label label14_da2;
        private System.Windows.Forms.Label label13_Z1;
        private System.Windows.Forms.Label label12_Z2;
        private System.Windows.Forms.Label label11_b2;
        private System.Windows.Forms.Label label10_df2;
        private System.Windows.Forms.Label label8_DaM2;
        private System.Windows.Forms.Label label7_P;
        private System.Windows.Forms.Label label7_alph;
        private System.Windows.Forms.Label label7_m;
        private System.Windows.Forms.Label label_Aw;
        private System.Windows.Forms.Label label7_Type_engine;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button button2_ClearZ1UMOb;
        private System.Windows.Forms.Button button2_Z1UMOb;
        private System.Windows.Forms.Button button_CalcReductor;
        private System.Windows.Forms.NumericUpDown numericUpDownOb;
        private System.Windows.Forms.Button buttonEditEngines;
        private System.Windows.Forms.Label label18_b1;
        private System.Windows.Forms.Label label9_d2;
        private System.Windows.Forms.Label label10;
    }
}
