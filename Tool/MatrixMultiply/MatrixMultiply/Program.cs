// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatrixMultiply
{
    class Program
    {
        class Matrix
        {
            public int[] M = new int[16];
            public int Type = 4;

            public void Set(int xy, int v)
            {
                int x = (int)(xy / 10 - 1);
                int y = xy % 10 - 1;
                M[x * 4 + y] = v;

            }
            public static Matrix Create4()
            {
                Matrix m = new Matrix();
                for (int i = 0; i < 16; i++)
                {
                    m.M[i] = 2;
                }
                return m;
            }

            public static Matrix Create43()
            {
                Matrix m = Create4();
                m.Set(14, 0);
                m.Set(24, 0);
                m.Set(34, 0);
                m.Set(44, 1);
                m.Type = 43;
                return m;
            }

            public static Matrix Create3()
            {
                Matrix m = Create43();
                m.Set(31, 0);
                m.Set(32, 0);
                m.Set(33, 1);
                m.Type = 3;

                //m.Set(13, 0);
                //m.Set(23, 0);
                //m.Set(33, 1);
                //m.Set(43, 0);

                //m.Set(41, 0);
                //m.Set(42, 0);
                //m.Set(43, 0);

                return m;
            }

            public static Matrix Create2()
            {
                Matrix m = Create3();
                m.Set(13, 0);
                m.Set(23, 0);
                m.Set(43, 0);


                m.Type = 2;

                //m.Set(13, 0);
                //m.Set(23, 0);
                //m.Set(33, 1);

                return m;
            }
        };

        private static string mFileContent;
        static void Main(string[] args)
        {
            string path = @"D:\Home\Engine\Medusa\MedusaCore\Core\Geometry\Matrix.cpp";
            mFileContent = File.ReadAllText(path);

            string text = mFileContent;

            string sb = AppendMulitplyAll();
            File.WriteAllText("AppendMulitplyAll.txt", sb);


            string sb2 = PrependMulitplyAll();
            File.WriteAllText("PrependMulitplyAll.txt", sb2);


            if (mFileContent != text)
            {
                File.WriteAllText(path, mFileContent, Encoding.UTF8);
            }
        }

        static void ReplaceFileAppend(int type1, int typ2, string result)
        {
            string begin = string.Format("//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_{0}_{1}]", type1, typ2);
            string end = string.Format("//[END_MATRIX_AUTO_GENERATE_APPEND_{0}_{1}]", type1, typ2);

            int index1 = mFileContent.IndexOf(begin);
            if (index1 < 0)
            {
                return;
            }
            index1 += begin.Length;
            int index2 = mFileContent.IndexOf(end);
            if (index2 < 0)
            {
                return;
            }
            int length = index2 - index1;
            mFileContent = mFileContent.Remove(index1, length);
            mFileContent = mFileContent.Insert(index1, result);

        }

        static void ReplaceFilePrepend(int type1, int typ2, string result)
        {
            string begin = string.Format("//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_{0}_{1}]", type1, typ2);
            string end = string.Format("//[END_MATRIX_AUTO_GENERATE_PREPEND_{0}_{1}]", type1, typ2);

            int index1 = mFileContent.IndexOf(begin);
            if (index1 < 0)
            {
                return;
            }
            index1 += begin.Length;
            int index2 = mFileContent.IndexOf(end);
            if (index2 < 0)
            {
                return;
            }
            int length = index2 - index1;
            mFileContent = mFileContent.Remove(index1, length);
            mFileContent = mFileContent.Insert(index1, result);


            ////[BEGIN_MATRIX_AUTO_GENERA_APPEND_4_4]
        }

        private static String AppendMulitplyAll()
        {
            Matrix m4 = Matrix.Create4();
            Matrix m43 = Matrix.Create43();
            Matrix m3 = Matrix.Create3();
            Matrix m2 = Matrix.Create2();

            Matrix n4 = Matrix.Create4();
            Matrix n43 = Matrix.Create43();
            Matrix n3 = Matrix.Create3();
            Matrix n2 = Matrix.Create2();

            StringBuilder all = new StringBuilder();

            all.AppendLine(AppendMulitply(m4, n4));
            all.AppendLine(AppendMulitply(m4, n43));
            all.AppendLine(AppendMulitply(m4, n3));
            all.AppendLine(AppendMulitply(m4, n2));

            all.AppendLine(AppendMulitply(m43, n4));
            all.AppendLine(AppendMulitply(m43, n43));
            all.AppendLine(AppendMulitply(m43, n3));
            all.AppendLine(AppendMulitply(m43, n2));

            all.AppendLine(AppendMulitply(m3, n4));
            all.AppendLine(AppendMulitply(m3, n43));
            all.AppendLine(AppendMulitply(m3, n3));
            all.AppendLine(AppendMulitply(m3, n2));

            all.AppendLine(AppendMulitply(m2, n4));
            all.AppendLine(AppendMulitply(m2, n43));
            all.AppendLine(AppendMulitply(m2, n3));
            all.AppendLine(AppendMulitply(m2, n2));

            return all.ToString();
        }

        private static String PrependMulitplyAll()
        {
            Matrix m4 = Matrix.Create4();
            Matrix m43 = Matrix.Create43();
            Matrix m3 = Matrix.Create3();
            Matrix m2 = Matrix.Create2();

            Matrix n4 = Matrix.Create4();
            Matrix n43 = Matrix.Create43();
            Matrix n3 = Matrix.Create3();
            Matrix n2 = Matrix.Create2();

            StringBuilder all = new StringBuilder();

            all.AppendLine(PrependMulitply(m4, n4));
            all.AppendLine(PrependMulitply(m4, n43));
            all.AppendLine(PrependMulitply(m4, n3));
            all.AppendLine(PrependMulitply(m4, n2));

            all.AppendLine(PrependMulitply(m43, n4));
            all.AppendLine(PrependMulitply(m43, n43));
            all.AppendLine(PrependMulitply(m43, n3));
            all.AppendLine(PrependMulitply(m43, n2));

            all.AppendLine(PrependMulitply(m3, n4));
            all.AppendLine(PrependMulitply(m3, n43));
            all.AppendLine(PrependMulitply(m3, n3));
            all.AppendLine(PrependMulitply(m3, n2));

            all.AppendLine(PrependMulitply(m2, n4));
            all.AppendLine(PrependMulitply(m2, n43));
            all.AppendLine(PrependMulitply(m2, n3));
            all.AppendLine(PrependMulitply(m2, n2));

            return all.ToString();
        }


        private static String AppendMulitply(Matrix m, Matrix n)
        {
            StringBuilder all = new StringBuilder();
            all.AppendLine();

            //all.AppendFormat("//***************{0} * {1}**************************\n", m.Type, n.Type);

            StringBuilder result = new StringBuilder();
            int outCount = 0;
            int maxCount = 0;
            result.Append(AppendMulitplyRow(m, n, 1, out outCount));
            maxCount = Math.Max(maxCount, outCount);
            result.Append(AppendMulitplyRow(m, n, 2, out outCount));
            maxCount = Math.Max(maxCount, outCount);
            result.Append(AppendMulitplyRow(m, n, 3, out outCount));
            maxCount = Math.Max(maxCount, outCount);
            result.Append(AppendMulitplyRow(m, n, 4, out outCount));
            maxCount = Math.Max(maxCount, outCount);

            switch (maxCount)
            {
                case 1:
                    all.AppendLine("float a;");
                    break;
                case 2:
                    all.AppendLine("float a,b;");
                    break;
                case 3:
                    all.AppendLine("float a,b,c;");

                    break;
                case 4:
                    all.AppendLine("float a,b,c,d;");

                    break;
            }

            all.Append(result);

            ReplaceFileAppend(m.Type, n.Type, all.ToString());
            return all.ToString();
        }

        private static String PrependMulitply(Matrix m, Matrix n)
        {
            StringBuilder all = new StringBuilder();
            all.AppendLine();
            //all.AppendFormat("//***************{0} * {1}**************************\n", m.Type, n.Type);

            StringBuilder result = new StringBuilder();

            int outCount = 0;
            int maxCount = 0;
            result.Append(PrependMulitplyRow(m, n, 1, out outCount));
            maxCount = Math.Max(maxCount, outCount);

            result.Append(PrependMulitplyRow(m, n, 2, out outCount));
            maxCount = Math.Max(maxCount, outCount);

            result.Append(PrependMulitplyRow(m, n, 3, out outCount));
            maxCount = Math.Max(maxCount, outCount);

            result.Append(PrependMulitplyRow(m, n, 4, out outCount));
            maxCount = Math.Max(maxCount, outCount);


            switch (maxCount)
            {
                case 1:
                    all.AppendLine("float a;");
                    break;
                case 2:
                    all.AppendLine("float a,b;");
                    break;
                case 3:
                    all.AppendLine("float a,b,c;");

                    break;
                case 4:
                    all.AppendLine("float a,b,c,d;");

                    break;
            }

            all.Append(result);
            ReplaceFilePrepend(m.Type, n.Type, all.ToString());
            return all.ToString();
        }

        private static String AppendMulitplyRow(Matrix m, Matrix n, int row, out int outCount)
        {
            outCount = 0;
            StringBuilder result = new StringBuilder();
            bool hasA, hasB, hasC, hasD;
            StringBuilder lineA = new StringBuilder();
            StringBuilder lineB = new StringBuilder();
            StringBuilder lineC = new StringBuilder();
            StringBuilder lineD = new StringBuilder();


            lineA.Append("a=");
            lineA.Append(AppendPrintItem(m, n, row * 10 + 1, 11, false));
            lineA.Append(AppendPrintItem(m, n, row * 10 + 2, 21));
            lineA.Append(AppendPrintItem(m, n, row * 10 + 3, 31));
            lineA.Append(AppendPrintItem(m, n, row * 10 + 4, 41));
            lineA.Append(";");
            lineA.Replace("=+", "=");
            hasA = lineA.Length > 3 && lineA.ToString().Contains('+');
            if (hasA)
            {
                result.AppendLine(lineA.ToString());
                ++outCount;
            }
            lineB.Clear();
            lineB.Append("b=");
            lineB.Append(AppendPrintItem(m, n, row * 10 + 1, 12, false));
            lineB.Append(AppendPrintItem(m, n, row * 10 + 2, 22));
            lineB.Append(AppendPrintItem(m, n, row * 10 + 3, 32));
            lineB.Append(AppendPrintItem(m, n, row * 10 + 4, 42));
            lineB.Append(";");
            lineB.Replace("=+", "=");
            hasB = lineB.Length > 3 && lineB.ToString().Contains('+');
            if (hasB)
            {
                result.AppendLine(lineB.ToString());
                ++outCount;

            }

            lineC.Clear();
            lineC.Append("c=");
            lineC.Append(AppendPrintItem(m, n, row * 10 + 1, 13, false));
            lineC.Append(AppendPrintItem(m, n, row * 10 + 2, 23));
            lineC.Append(AppendPrintItem(m, n, row * 10 + 3, 33));
            lineC.Append(AppendPrintItem(m, n, row * 10 + 4, 43));
            lineC.Append(";");
            lineC.Replace("=+", "=");
            hasC = lineC.Length > 3 && lineC.ToString().Contains('+');
            if (hasC)
            {
                result.AppendLine(lineC.ToString());
                ++outCount;

            }

            lineD.Clear();
            lineD.Append("d=");
            lineD.Append(AppendPrintItem(m, n, row * 10 + 1, 14, false));
            lineD.Append(AppendPrintItem(m, n, row * 10 + 2, 24));
            lineD.Append(AppendPrintItem(m, n, row * 10 + 3, 34));
            lineD.Append(AppendPrintItem(m, n, row * 10 + 4, 44));
            lineD.Append(";");
            lineD.Replace("=+", "=");
            hasD = lineD.Length > 3 && lineD.ToString().Contains('+');
            if (hasD)
            {
                result.AppendLine(lineD.ToString());
                ++outCount;

            }

            if (hasA)
            {
                result.AppendFormat("M{0} = a;", row * 10 + 1);
            }
            else
            {
                AddCopyItem(lineA, row, 1, result);
            }

            if (hasB)
            {
                result.AppendFormat("M{0} = b;", row * 10 + 2);
            }
            else
            {
                AddCopyItem(lineB, row, 2, result);
            }

            if (hasC)
            {
                result.AppendFormat("M{0} = c;", row * 10 + 3);
            }
            else
            {
                AddCopyItem(lineC, row, 3, result);
            }

            if (hasD)
            {
                result.AppendFormat("M{0} = d;", row * 10 + 4);
            }
            else
            {
                AddCopyItem(lineD, row, 4, result);
            }
            result.AppendLine();

            return result.ToString();
        }

        private static String PrependMulitplyRow(Matrix m, Matrix n, int row, out int outCount)
        {
            outCount = 0;
            StringBuilder result = new StringBuilder();
            bool hasA, hasB, hasC, hasD;
            StringBuilder lineA = new StringBuilder();
            StringBuilder lineB = new StringBuilder();
            StringBuilder lineC = new StringBuilder();
            StringBuilder lineD = new StringBuilder();


            lineA.Append("a=");
            lineA.Append(PrependPrintItem(m, n, 11, row * 10 + 1, false));
            lineA.Append(PrependPrintItem(m, n, 21, row * 10 + 2));
            lineA.Append(PrependPrintItem(m, n, 31, row * 10 + 3));
            lineA.Append(PrependPrintItem(m, n, 41, row * 10 + 4));
            lineA.Append(";");
            lineA.Replace("=+", "=");
            hasA = lineA.Length > 3 && lineA.ToString().Contains('+');
            if (hasA)
            {
                result.AppendLine(lineA.ToString());
                ++outCount;
            }
            lineB.Clear();
            lineB.Append("b=");
            lineB.Append(PrependPrintItem(m, n, 12, row * 10 + 1, false));
            lineB.Append(PrependPrintItem(m, n, 22, row * 10 + 2));
            lineB.Append(PrependPrintItem(m, n, 32, row * 10 + 3));
            lineB.Append(PrependPrintItem(m, n, 42, row * 10 + 4));
            lineB.Append(";");
            lineB.Replace("=+", "=");
            hasB = lineB.Length > 3 && lineB.ToString().Contains('+');
            if (hasB)
            {
                result.AppendLine(lineB.ToString());
                ++outCount;

            }

            lineC.Clear();
            lineC.Append("c=");
            lineC.Append(PrependPrintItem(m, n, 13, row * 10 + 1, false));
            lineC.Append(PrependPrintItem(m, n, 23, row * 10 + 2));
            lineC.Append(PrependPrintItem(m, n, 33, row * 10 + 3));
            lineC.Append(PrependPrintItem(m, n, 43, row * 10 + 4));
            lineC.Append(";");
            lineC.Replace("=+", "=");
            hasC = lineC.Length > 3 && lineC.ToString().Contains('+');
            if (hasC)
            {
                result.AppendLine(lineC.ToString());
                ++outCount;

            }

            lineD.Clear();
            lineD.Append("d=");
            lineD.Append(PrependPrintItem(m, n, 14, row * 10 + 1, false));
            lineD.Append(PrependPrintItem(m, n, 24, row * 10 + 2));
            lineD.Append(PrependPrintItem(m, n, 34, row * 10 + 3));
            lineD.Append(PrependPrintItem(m, n, 44, row * 10 + 4));
            lineD.Append(";");
            lineD.Replace("=+", "=");
            hasD = lineD.Length > 3 && lineD.ToString().Contains('+');
            if (hasD)
            {
                result.AppendLine(lineD.ToString());
                ++outCount;

            }

            if (hasA)
            {
                result.AppendFormat("M{0} = a;", row * 10 + 1);
            }
            else
            {
                AddCopyItem(lineA, row, 1, result);
            }

            if (hasB)
            {
                result.AppendFormat("M{0} = b;", row * 10 + 2);
            }
            else
            {
                AddCopyItem(lineB, row, 2, result);
            }

            if (hasC)
            {
                result.AppendFormat("M{0} = c;", row * 10 + 3);
            }
            else
            {
                AddCopyItem(lineC, row, 3, result);
            }

            if (hasD)
            {
                result.AppendFormat("M{0} = d;", row * 10 + 4);
            }
            else
            {
                AddCopyItem(lineD, row, 4, result);
            }

            result.AppendLine();

            return result.ToString();
        }

        private static void AddCopyItem(StringBuilder line, int row, int column, StringBuilder result)
        {
            if (line.Length > 3)
            {
                string tag = new string(new char[] { (char)('a' + (char)column-1 )});
                tag += "=";
                line.Replace(tag, string.Empty);
                line.Remove(line.Length - 1,1);
                string newStr;
                newStr = string.Format("M{0}", row * 10 + column);

                
                if (newStr != line.ToString())
                {
                    result.AppendFormat("{0}={1};", newStr, line);
                }
            }

        }

        private static String AppendPrintItem(Matrix m, Matrix n, int mxy, int nxy, bool isNext = true)
        {
            int mX = mxy / 10 - 1;
            int mY = mxy % 10 - 1;

            int nX = nxy / 10 - 1;
            int nY = nxy % 10 - 1;

            int a = m.M[mX * 4 + mY];
            int b = n.M[nX * 4 + nY];

            string prefix;
            if (isNext)
            {
                prefix = "+";
            }
            else
            {
                prefix = string.Empty;
            }

            if (a == 0 || b == 0)
            {
                return string.Empty;
            }

            if (a != 1)
            {
                if (b != 1)
                {
                    return prefix + String.Format("M{0}{1} * m.M{2}{3}", mX + 1, mY + 1, nX + 1, nY + 1);
                }
                return prefix + String.Format("M{0}{1}", mX + 1, mY + 1);
            }
            else
            {
                if (b != 1)
                {
                    return prefix + String.Format("m.M{0}{1}", nX + 1, nY + 1);
                }

                return string.Empty;
            }

        }

        private static String PrependPrintItem(Matrix m, Matrix n, int mxy, int nxy, bool isNext = true)
        {
            //n*m==m.xx*M
            int mX = mxy / 10 - 1;
            int mY = mxy % 10 - 1;

            int nX = nxy / 10 - 1;
            int nY = nxy % 10 - 1;

            int a = m.M[mX * 4 + mY];
            int b = n.M[nX * 4 + nY];

            string prefix;
            if (isNext)
            {
                prefix = "+";
            }
            else
            {
                prefix = string.Empty;
            }

            if (a == 0 || b == 0)
            {
                return string.Empty;
            }

            if (a != 1)
            {
                if (b != 1)
                {
                    return prefix + String.Format("m.M{0}{1} * M{2}{3}", nX + 1, nY + 1, mX + 1, mY + 1);
                }
                return prefix + String.Format("m.M{0}{1}", nX + 1, nY + 1);
            }
            else
            {
                if (b != 1)
                {
                    return prefix + String.Format("m.M{0}{1}", nX + 1, nY + 1);
                }

                return string.Empty;
            }

            /*
            int mX = mxy / 10 - 1;
            int mY = mxy % 10 - 1;

            int nX = nxy / 10 - 1;
            int nY = nxy % 10 - 1;

            int a = m.M[mX * 4 + mY];
            int b = n.M[nX * 4 + nY];

            string prefix;
            if (isNext)
            {
                prefix = "+";
            }
            else
            {
                prefix = string.Empty;
            }

            if (a == 0 || b == 0)
            {
                return string.Empty;
            }

            if (a != 1)
            {
                if (b != 1)
                {
                    return prefix + String.Format("m.M{0}{1} * M{2}{3}", nX + 1, nY + 1, mX + 1, mY + 1);
                }
                return prefix + String.Format("m.M{0}{1}", nX + 1, nY + 1);
            }
            else
            {
                if (b != 1)
                {
                    return prefix + String.Format("M{0}{1}", mX + 1, mY + 1);
                }

                return string.Empty;
            }
             * */

        }
    }
}
