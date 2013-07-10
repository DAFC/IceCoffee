namespace ProCon2013.Client
{
    partial class Form1
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
            this.buttonSubmit = new System.Windows.Forms.Button();
            this.labelToken = new System.Windows.Forms.Label();
            this.textBoxToken = new System.Windows.Forms.TextBox();
            this.labelAns = new System.Windows.Forms.Label();
            this.textBoxAnswer = new System.Windows.Forms.TextBox();
            this.labelServerAddress = new System.Windows.Forms.Label();
            this.textBoxServerAddress = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // buttonSubmit
            // 
            this.buttonSubmit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSubmit.Location = new System.Drawing.Point(197, 226);
            this.buttonSubmit.Name = "buttonSubmit";
            this.buttonSubmit.Size = new System.Drawing.Size(75, 23);
            this.buttonSubmit.TabIndex = 6;
            this.buttonSubmit.Text = "Submit(&S)";
            this.buttonSubmit.UseVisualStyleBackColor = true;
            this.buttonSubmit.Click += new System.EventHandler(this.buttonSubmit_Click);
            // 
            // labelToken
            // 
            this.labelToken.AutoSize = true;
            this.labelToken.Location = new System.Drawing.Point(12, 41);
            this.labelToken.Name = "labelToken";
            this.labelToken.Size = new System.Drawing.Size(51, 13);
            this.labelToken.TabIndex = 2;
            this.labelToken.Text = "Token(&T)";
            // 
            // textBoxToken
            // 
            this.textBoxToken.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxToken.Location = new System.Drawing.Point(76, 38);
            this.textBoxToken.Name = "textBoxToken";
            this.textBoxToken.Size = new System.Drawing.Size(196, 20);
            this.textBoxToken.TabIndex = 3;
            // 
            // labelAns
            // 
            this.labelAns.AutoSize = true;
            this.labelAns.Location = new System.Drawing.Point(12, 63);
            this.labelAns.Name = "labelAns";
            this.labelAns.Size = new System.Drawing.Size(55, 13);
            this.labelAns.TabIndex = 4;
            this.labelAns.Text = "Answer(&A)";
            // 
            // textBoxAnswer
            // 
            this.textBoxAnswer.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxAnswer.Location = new System.Drawing.Point(12, 79);
            this.textBoxAnswer.Multiline = true;
            this.textBoxAnswer.Name = "textBoxAnswer";
            this.textBoxAnswer.Size = new System.Drawing.Size(260, 141);
            this.textBoxAnswer.TabIndex = 5;
            // 
            // labelServerAddress
            // 
            this.labelServerAddress.AutoSize = true;
            this.labelServerAddress.Location = new System.Drawing.Point(12, 15);
            this.labelServerAddress.Name = "labelServerAddress";
            this.labelServerAddress.Size = new System.Drawing.Size(51, 13);
            this.labelServerAddress.TabIndex = 0;
            this.labelServerAddress.Text = "Server(&S)";
            // 
            // textBoxServerAddress
            // 
            this.textBoxServerAddress.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxServerAddress.Location = new System.Drawing.Point(76, 12);
            this.textBoxServerAddress.Name = "textBoxServerAddress";
            this.textBoxServerAddress.Size = new System.Drawing.Size(196, 20);
            this.textBoxServerAddress.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.textBoxServerAddress);
            this.Controls.Add(this.labelServerAddress);
            this.Controls.Add(this.textBoxAnswer);
            this.Controls.Add(this.labelAns);
            this.Controls.Add(this.textBoxToken);
            this.Controls.Add(this.labelToken);
            this.Controls.Add(this.buttonSubmit);
            this.Name = "Form1";
            this.Text = "Procon24.Client";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonSubmit;
        private System.Windows.Forms.Label labelToken;
        private System.Windows.Forms.TextBox textBoxToken;
        private System.Windows.Forms.Label labelAns;
        private System.Windows.Forms.TextBox textBoxAnswer;
        private System.Windows.Forms.Label labelServerAddress;
        private System.Windows.Forms.TextBox textBoxServerAddress;
    }
}

