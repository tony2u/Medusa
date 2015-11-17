// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace IndexGenerator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public List<uint> GenerateQuadData(uint quadCount)
        {
            List<uint> items = new List<uint>();
            for (uint i = 0; i < quadCount; i++)
            {
                uint k = i * 4;
                items.Add(k);
                items.Add(k + 1);
                items.Add(k + 2);
                items.Add(k + 2);
                items.Add(k + 3);
                items.Add(k);
            }
            return items;
        }


        public string GenerateQuadDataString(uint quadCount, string name,bool isShort=true)
        {
            StringBuilder sb = new StringBuilder();
            var items = GenerateQuadData(quadCount);
            sb.AppendLine("#ifdef MEDUSA_PRE_GENERATED_INDEX_ENABLED");

            
            //sb.AppendLine("#pragma region " + name);
            int size =  items.Count;
            string typeString;
            if (isShort)
            {
                size *= sizeof (ushort);
                typeString = "ushort";
            }
            else
            {
                size *= sizeof(uint);
                typeString = "uint";
            }

            sb.AppendFormat("//{0}B=={1}K", size, size / 1024);
            sb.AppendLine();

            sb.AppendFormat("const {2} {0}[{1}*6]=", name, quadCount, typeString);
            sb.AppendLine();
            sb.Append('{');

            uint lineCount = 160;
            StringBuilder line = new StringBuilder();
            for (int i = 0; i < items.Count; i++)
            {

                line.Append(items[i].ToString());
                if (i != items.Count - 1)
                {
                    line.Append(',');
                }

                if (line.Length >= lineCount)
                {
                    sb.AppendLine(line.ToString());
                    line.Clear();
                }

            }

            sb.Append("};");
            sb.AppendLine();

            //sb.AppendLine("#pragma endregion " + name);
            sb.AppendLine("#endif");

            return sb.ToString();
        }

        private void mGenerateQuadButton_Click(object sender, EventArgs e)
        {
            mResultRichTextBox.Text = GenerateQuadDataString(ushort.MaxValue / 6, mNameTextBox.Text);

            //mResultRichTextBox.Text = GenerateQuadDataString((uint)mCountNumericUpDown.Value,mNameTextBox.Text);
        }

        private void mGenerateQuadUintButton_Click(object sender, EventArgs e)
        {
            mResultRichTextBox.Text = GenerateQuadDataString(ushort.MaxValue / 6, mNameTextBox.Text,false);
        }
    }
}
