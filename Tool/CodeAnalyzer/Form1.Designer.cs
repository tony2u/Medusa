// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
namespace CodeAnalyzer
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
            this.mPreDeclareButton = new System.Windows.Forms.Button();
            this.mHeaderButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // mPreDeclareButton
            // 
            this.mPreDeclareButton.Location = new System.Drawing.Point(37, 27);
            this.mPreDeclareButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.mPreDeclareButton.Name = "mPreDeclareButton";
            this.mPreDeclareButton.Size = new System.Drawing.Size(100, 28);
            this.mPreDeclareButton.TabIndex = 0;
            this.mPreDeclareButton.Text = "PreDeclare";
            this.mPreDeclareButton.UseVisualStyleBackColor = true;
            this.mPreDeclareButton.Click += new System.EventHandler(this.mPreDeclareButton_Click);
            // 
            // mHeaderButton
            // 
            this.mHeaderButton.Location = new System.Drawing.Point(180, 31);
            this.mHeaderButton.Name = "mHeaderButton";
            this.mHeaderButton.Size = new System.Drawing.Size(75, 23);
            this.mHeaderButton.TabIndex = 1;
            this.mHeaderButton.Text = "Header";
            this.mHeaderButton.UseVisualStyleBackColor = true;
            this.mHeaderButton.Click += new System.EventHandler(this.mHeaderButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(379, 322);
            this.Controls.Add(this.mHeaderButton);
            this.Controls.Add(this.mPreDeclareButton);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button mPreDeclareButton;
        private System.Windows.Forms.Button mHeaderButton;
    }
}

