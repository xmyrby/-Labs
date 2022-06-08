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

