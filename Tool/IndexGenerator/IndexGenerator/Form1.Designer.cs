// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
namespace IndexGenerator
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.mResultRichTextBox = new System.Windows.Forms.RichTextBox();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.mGenerateQuadUShortButton = new System.Windows.Forms.Button();
            this.mCountNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.mNameTextBox = new System.Windows.Forms.TextBox();
            this.mGenerateQuadUintButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mCountNumericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.mResultRichTextBox);
            this.splitContainer1.Size = new System.Drawing.Size(543, 399);
            this.splitContainer1.SplitterDistance = 103;
            this.splitContainer1.TabIndex = 0;
            // 
            // mResultRichTextBox
            // 
            this.mResultRichTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mResultRichTextBox.Location = new System.Drawing.Point(0, 0);
            this.mResultRichTextBox.Name = "mResultRichTextBox";
            this.mResultRichTextBox.Size = new System.Drawing.Size(543, 292);
            this.mResultRichTextBox.TabIndex = 0;
            this.mResultRichTextBox.Text = "";
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.mNameTextBox);
            this.splitContainer2.Panel1.Controls.Add(this.mCountNumericUpDown);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.mGenerateQuadUintButton);
            this.splitContainer2.Panel2.Controls.Add(this.mGenerateQuadUShortButton);
            this.splitContainer2.Size = new System.Drawing.Size(543, 103);
            this.splitContainer2.SplitterDistance = 349;
            this.splitContainer2.TabIndex = 0;
            // 
            // mGenerateQuadUShortButton
            // 
            this.mGenerateQuadUShortButton.Location = new System.Drawing.Point(2, 3);
            this.mGenerateQuadUShortButton.Name = "mGenerateQuadUShortButton";
            this.mGenerateQuadUShortButton.Size = new System.Drawing.Size(162, 23);
            this.mGenerateQuadUShortButton.TabIndex = 0;
            this.mGenerateQuadUShortButton.Text = "GenerateQuadUShort";
            this.mGenerateQuadUShortButton.UseVisualStyleBackColor = true;
            this.mGenerateQuadUShortButton.Click += new System.EventHandler(this.mGenerateQuadButton_Click);
            // 
            // mCountNumericUpDown
            // 
            this.mCountNumericUpDown.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mCountNumericUpDown.Location = new System.Drawing.Point(0, 0);
            this.mCountNumericUpDown.Maximum = new decimal(new int[] {
            10240,
            0,
            0,
            0});
            this.mCountNumericUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.mCountNumericUpDown.Name = "mCountNumericUpDown";
            this.mCountNumericUpDown.Size = new System.Drawing.Size(349, 20);
            this.mCountNumericUpDown.TabIndex = 0;
            this.mCountNumericUpDown.Value = new decimal(new int[] {
            1024,
            0,
            0,
            0});
            // 
            // mNameTextBox
            // 
            this.mNameTextBox.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.mNameTextBox.Location = new System.Drawing.Point(0, 83);
            this.mNameTextBox.Name = "mNameTextBox";
            this.mNameTextBox.Size = new System.Drawing.Size(349, 20);
            this.mNameTextBox.TabIndex = 1;
            this.mNameTextBox.Text = "PreGeneratedIndicesUShort";
            // 
            // mGenerateQuadUintButton
            // 
            this.mGenerateQuadUintButton.Location = new System.Drawing.Point(4, 33);
            this.mGenerateQuadUintButton.Name = "mGenerateQuadUintButton";
            this.mGenerateQuadUintButton.Size = new System.Drawing.Size(160, 23);
            this.mGenerateQuadUintButton.TabIndex = 1;
            this.mGenerateQuadUintButton.Text = "GenerateQuadUInt";
            this.mGenerateQuadUintButton.UseVisualStyleBackColor = true;
            this.mGenerateQuadUintButton.Click += new System.EventHandler(this.mGenerateQuadUintButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(543, 399);
            this.Controls.Add(this.splitContainer1);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "IndexGenerator";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel1.PerformLayout();
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.mCountNumericUpDown)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.RichTextBox mResultRichTextBox;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.Button mGenerateQuadUShortButton;
        private System.Windows.Forms.NumericUpDown mCountNumericUpDown;
        private System.Windows.Forms.TextBox mNameTextBox;
        private System.Windows.Forms.Button mGenerateQuadUintButton;
    }
}

