using System;
using System.Windows.Forms;

namespace ProCon2013.Client
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonSubmit_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                ClientLib.SubmitAnswer(textBoxServerAddress.Text, textBoxToken.Text, textBoxAnswer.Text));
        }
    }
}
