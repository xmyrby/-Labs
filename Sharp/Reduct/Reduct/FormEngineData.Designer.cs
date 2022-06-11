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
            this.Name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Power = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RotorSpeed = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RangeSpeed = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewEngines)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewEngines
            // 
            this.dataGridViewEngines.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewEngines.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewEngines.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Name,
            this.Power,
            this.RotorSpeed,
            this.RangeSpeed});
            this.dataGridViewEngines.Location = new System.Drawing.Point(12, 12);
            this.dataGridViewEngines.Name = "dataGridViewEngines";
            this.dataGridViewEngines.Size = new System.Drawing.Size(776, 264);
            this.dataGridViewEngines.TabIndex = 0;
            // 
            // Name
            // 
            this.Name.HeaderText = "Имя";
            this.Name.Name = "Name";
            this.Name.ReadOnly = true;
            // 
            // Power
            // 
            this.Power.HeaderText = "Мощность";
            this.Power.Name = "Power";
            this.Power.ReadOnly = true;
            // 
            // RotorSpeed
            // 
            this.RotorSpeed.HeaderText = "Частота вращения на входном валу";
            this.RotorSpeed.Name = "RotorSpeed";
            this.RotorSpeed.ReadOnly = true;
            // 
            // RangeSpeed
            // 
            this.RangeSpeed.HeaderText = "Номинальная частота вращения";
            this.RangeSpeed.Name = "RangeSpeed";
            this.RangeSpeed.ReadOnly = true;
            // 
            // FormEngineData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.dataGridViewEngines);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.ShowIcon = false;
            this.Text = "Engines";
            this.Load += new System.EventHandler(this.FormEngineData_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewEngines)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewEngines;
        private System.Windows.Forms.DataGridViewTextBoxColumn Name;
        private System.Windows.Forms.DataGridViewTextBoxColumn Power;
        private System.Windows.Forms.DataGridViewTextBoxColumn RotorSpeed;
        private System.Windows.Forms.DataGridViewTextBoxColumn RangeSpeed;
    }
}