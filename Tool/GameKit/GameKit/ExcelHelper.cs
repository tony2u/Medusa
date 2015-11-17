// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using GameKit.Log;

namespace GameKit
{
    public class ExcelHelper
    {
        private static string GetConnectString(string filePath)
        {
            try
            {
                string strConn;
                if (filePath.EndsWith("xls", StringComparison.InvariantCultureIgnoreCase))
                {
                    strConn = @"Provider=Microsoft.Jet.OLEDB.4.0;" +
                              @"Data Source=" + filePath + ";" + "Extended Properties=\"Excel 8.0;HDR=YES;IMEX=1\"";
                }
                else if (filePath.EndsWith("xlsx", StringComparison.InvariantCultureIgnoreCase))
                {
                    //strConn = @"Data Source=" + _strExcelFilename +
                    //    ";Provider=Microsoft.ACE.OLEDB.12.0; Extended Properties=Excel 12.0;";
                    strConn = @"Provider=Microsoft.ACE.OLEDB.12.0;" +
                              @"Data Source=" + filePath + ";" +
                              "Extended Properties=\"Excel 12.0 Xml;HDR=YES;IMEX=1\"";
                }
                else
                    return string.Empty;
                return strConn;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return string.Empty;
            }
        }

        //??Excel 
        public static DataTable LoadDataFromExcel(string filePath, string tableName)
        {
            string strConn = GetConnectString(filePath);
            using (var oleConn = new OleDbConnection(strConn))
            {
                oleConn.Open();
                string sql = String.Format("SELECT * FROM  [{0}]", tableName); //????Sheet?????sheet2??? 

                var oleDaExcel = new OleDbDataAdapter(sql, oleConn);
                var result = new DataSet();
                oleDaExcel.Fill(result);
                return result.Tables[0];
            }
        }

        public static List<string> GetExcelTableNames(string filePath)
        {
            var tableNames = new List<string>();
            string strConn = GetConnectString(filePath);
            using (var oleConn = new OleDbConnection(strConn))
            {
                oleConn.Open();
                var dataTable = oleConn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, null);
                tableNames.AddRange(from DataRow row in dataTable.Rows select row["TABLE_NAME"].ToString());
            }
            return tableNames;
        }

        public static string PrintRow(DataRow row)
        {
            var sb = new StringBuilder();
            for (int i = 0; i < row.ItemArray.Length; i++)
            {
                sb.Append(row[i]);
                if (i != row.ItemArray.Length - 1)
                {
                    sb.Append(',');
                }
            }

            string str = sb.ToString();
            Logger.LogErrorLine(str);
            return str;
        }

        public static bool ParseBool(int data)
        {
            switch (data)
            {
                case 0:
                    return false;
                case 1:
                    return true;
                default:
                    Logger.LogAllLine("\tError bool value:{0}", data);
                    break;
            }

            return false;
        }




        public static List<uint> ParseUIntArray(string data)
        {
            var result = new List<uint>();
            string[] strs = data.Split(new[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var str in strs)
            {
                uint temp;
                if (!uint.TryParse(str, out temp))
                {
                    Logger.LogErrorLine("Error parse uint array:{0}", data);
                    result.Clear();
                    return result;
                }

                result.Add(temp);
            }

            return result;
        }

        public static List<int> ParseIntArray(string data)
        {
            var result = new List<int>();
            string[] strs = data.Split(new[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var str in strs)
            {
                int temp;
                if (!int.TryParse(str, out temp))
                {
                    Logger.LogErrorLine("Error parse uint array:{0}", data);
                    result.Clear();
                    return result;
                }

                result.Add(temp);
            }

            return result;
        }

        public static List<float> ParseFloatArray(string data)
        {
            var result = new List<float>();
            string[] strs = data.Split(new[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var str in strs)
            {
                float temp;
                if (!float.TryParse(str, out temp))
                {
                    Logger.LogErrorLine("Error parse uint array:{0}", data);
                    result.Clear();
                    return result;
                }

                result.Add(temp);
            }

            return result;
        }

        public static string ConvertToUTF8(string str)
        {
            Encoding fromEncoding = Encoding.Default;
            Encoding toEncoding = Encoding.UTF8;
            var fromBytes = fromEncoding.GetBytes(str);
            var toBytes = Encoding.Convert(fromEncoding, toEncoding, fromBytes);
            return toEncoding.GetString(toBytes);
        }
    }
}