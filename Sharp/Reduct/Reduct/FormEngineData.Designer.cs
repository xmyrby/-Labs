namespace Reduct
{
    partial class FormEngineData
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridViewEngines = new System.Windows.Forms.DataGridView();
            this.EngineName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Power = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RotorSpeed = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RangeSpeed = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.numericUpDownSpeed = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownPower = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDownSpeedRange = new System.Windows.Forms.NumericUpDown();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonEdit = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewEngines)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpeed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPower)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpeedRange)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewEngines
            // 
            this.dataGridViewEngines.AllowUserToAddRows = false;
            this.dataGridViewEngines.AllowUserToDeleteRows = false;
            this.dataGridViewEngines.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewEngines.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewEngines.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.EngineName,
            this.Power,
            this.RotorSpeed,
            this.RangeSpeed});
            this.dataGridViewEngines.Location = new System.Drawing.Point(12, 12);
            this.dataGridViewEngines.Name = "dataGridViewEngines";
            this.dataGridViewEngines.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.dataGridViewEngines.Size = new System.Drawing.Size(776, 264);
            this.dataGridViewEngines.TabIndex = 0;
            this.dataGridViewEngines.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewEngines_CellClick);
            // 
            // EngineName
            // 
            this.EngineName.HeaderText = "Имя";
            this.EngineName.Name = "EngineName";
            this.EngineName.ReadOnly = true;
            this.EngineName.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // Power
            // 
            this.Power.HeaderText = "Мощность";
            this.Power.Name = "Power";
            this.Power.ReadOnly = true;
            this.Power.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // RotorSpeed
            // 
            this.RotorSpeed.HeaderText = "Частота вращения на входном валу";
            this.RotorSpeed.Name = "RotorSpeed";
            this.RotorSpeed.ReadOnly = true;
            this.RotorSpeed.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // RangeSpeed
            // 
            this.RangeSpeed.HeaderText = "Номинальная частота вращения";
            this.RangeSpeed.Name = "RangeSpeed";
            this.RangeSpeed.ReadOnly = true;
            this.RangeSpeed.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // numericUpDownSpeed
            // 
            this.numericUpDownSpeed.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numericUpDownSpeed.Location = new System.Drawing.Point(454, 305);
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
            this.numericUpDownSpeed.Size = new System.Drawing.Size(150, 20);
            this.numericUpDownSpeed.TabIndex = 7;
            this.numericUpDownSpeed.ThousandsSeparator = true;
            this.numericUpDownSpeed.Value = new decimal(new int[] {
            150,
            0,
            0,
            0});
            // 
            // numericUpDownPower
            // 
            this.numericUpDownPower.DecimalPlaces = 2;
            this.numericUpDownPower.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownPower.Location = new System.Drawing.Point(267, 305);
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
            this.numericUpDownPower.Size = new System.Drawing.Size(150, 20);
            this.numericUpDownPower.TabIndex = 6;
            this.numericUpDownPower.ThousandsSeparator = true;
            this.numericUpDownPower.Value = new decimal(new int[] {
            120,
            0,
            0,
            65536});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(264, 289);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Мощность";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(451, 289);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(97, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Входные обороты";
            // 
            // numericUpDownSpeedRange
            // 
            this.numericUpDownSpeedRange.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numericUpDownSpeedRange.Location = new System.Drawing.Point(638, 305);
            this.numericUpDownSpeedRange.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownSpeedRange.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numericUpDownSpeedRange.Name = "numericUpDownSpeedRange";
            this.numericUpDownSpeedRange.Size = new System.Drawing.Size(150, 20);
            this.numericUpDownSpeedRange.TabIndex = 10;
            this.numericUpDownSpeedRange.ThousandsSeparator = true;
            this.numericUpDownSpeedRange.Value = new decimal(new int[] {
            150,
            0,
            0,
            0});
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(12, 304);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(213, 20);
            this.textBoxName.TabIndex = 11;
            this.textBoxName.TextChanged += new System.EventHandler(this.textBoxName_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 289);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 13);
            this.label3.TabIndex = 12;
            this.label3.Text = "Название";
            // 
            // buttonAdd
            // 
            this.buttonAdd.Enabled = false;
            this.buttonAdd.Location = new System.Drawing.Point(12, 341);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(213, 23);
            this.buttonAdd.TabIndex = 13;
            this.buttonAdd.Text = "Добавить";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Enabled = false;
            this.buttonDelete.Location = new System.Drawing.Point(12, 370);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(213, 23);
            this.buttonDelete.TabIndex = 14;
            this.buttonDelete.Text = "Удалить";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // buttonEdit
            // 
            this.buttonEdit.Enabled = false;
            this.buttonEdit.Location = new System.Drawing.Point(12, 399);
            this.buttonEdit.Name = "buttonEdit";
            this.buttonEdit.Size = new System.Drawing.Size(213, 23);
            this.buttonEdit.TabIndex = 15;
            this.buttonEdit.Text = "Изменить";
            this.buttonEdit.UseVisualStyleBackColor = true;
            this.buttonEdit.Click += new System.EventHandler(this.buttonEdit_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(635, 289);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(119, 13);
            this.label4.TabIndex = 16;
            this.label4.Text = "Номинальная частота";
            // 
            // FormEngineData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.buttonEdit);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.numericUpDownSpeedRange);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numericUpDownSpeed);
            this.Controls.Add(this.numericUpDownPower);
            this.Controls.Add(this.dataGridViewEngines);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormEngineData";
            this.ShowIcon = false;
            this.Text = "Engines";
            this.Load += new System.EventHandler(this.FormEngineData_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewEngines)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpeed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPower)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpeedRange)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewEngines;
        private System.Windows.Forms.DataGridViewTextBoxColumn EngineName;
        private System.Windows.Forms.DataGridViewTextBoxColumn Power;
        private System.Windows.Forms.DataGridViewTextBoxColumn RotorSpeed;
        private System.Windows.Forms.DataGridViewTextBoxColumn RangeSpeed;
        private System.Windows.Forms.NumericUpDown numericUpDownSpeed;
        private System.Windows.Forms.NumericUpDown numericUpDownPower;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numericUpDownSpeedRange;
        private System.Windows.Forms.TextBox textBoxName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonEdit;
        private System.Windows.Forms.Label label4;
    }
}