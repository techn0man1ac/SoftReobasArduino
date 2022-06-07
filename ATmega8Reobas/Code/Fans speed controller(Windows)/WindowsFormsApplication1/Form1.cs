using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        /* Bases on this example http://avr-start.ru/?p=550 */ 
        private void button1_Click(object sender, EventArgs e)
        {
         
            serialPort1.WriteLine("m");
        }

        private void button2_Click(object sender, EventArgs e)
        {
           
            serialPort1.WriteLine("s");

            
        }
        
        private void button4_Click(object sender, EventArgs e)
        {
            serialPort1.WriteLine("r");
        }

        private void button5_Click(object sender, EventArgs e)
        {

            string rstr;
            string gstr;
            string bstr;
            int r = trackBar1.Value;
            int g = trackBar2.Value;
            int b = trackBar3.Value;
            /* надо же как всё просто*/
            rstr = r.ToString();
            gstr = g.ToString();
            bstr = b.ToString();﻿
            serialPort1.Write("d");
            serialPort1.Write(rstr);
            serialPort1.Write(".");
            serialPort1.Write(gstr);
            serialPort1.Write(".");
            serialPort1.WriteLine(bstr);

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] myPort;

            myPort = System.IO.Ports.SerialPort.GetPortNames();
            comboBox1.Items.AddRange(myPort);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen == true)
            serialPort1.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            serialPort1.BaudRate = 9600;
            serialPort1.PortName = comboBox1.Text.ToString();
            if (serialPort1.IsOpen == false)
                serialPort1.Open();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = comboBox1.Text.ToString();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            /*one, two, three*/
            string one;
            string two;
            string three;
            int on = trackBar1.Value;
            int tw = trackBar2.Value;
            int th = trackBar3.Value;
            
            one = on.ToString();
            two = tw.ToString();
            three = th.ToString();﻿
            
            label6.Text = one;
            label5.Text = two;
            label7.Text = three;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://github.com/techn0man1ac/SoftReobasArduino");
        }
    }
}
