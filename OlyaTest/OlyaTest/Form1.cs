﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OlyaTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            double KHV, KHB, oH, vH;
            double de2 = 165 * Math.Pow((KHV * KHB * (double)numericUpDown1.Value * (double)numericUpDown1.Value) / (oH * oH * vH), 1 / 3);
        }
    }
}
