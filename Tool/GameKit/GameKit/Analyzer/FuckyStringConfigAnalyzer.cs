// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using GameKit.Log;
using GameKit.Publish;
using GameKit.Resource;
using Medusa.CoreProto;
using Microsoft.Win32;
using ProtoBuf;

namespace GameKit.Analyzer
{

    public class MyFuckyStringNode
    {
        public char Char;
        public bool IsFucky;
        public SortedDictionary<char, MyFuckyStringNode> Childs = new SortedDictionary<char, MyFuckyStringNode>();
        public void Print(string prefix)
        {
            Logger.LogInfoLine("{0}{1}{2}", prefix, Char, IsFucky ? "?" : string.Empty);
            prefix += "\t";
            foreach (var fuckyStringNode in Childs)
            {
                fuckyStringNode.Value.Print(prefix);
            }
        }
        public override string ToString()
        {
            if (IsFucky)
            {
                return Char + "?";
            }
            else
            {
                return Char.ToString();
            }
        }

        public void Fill(FuckyStringNode node)
        {
            node.charVal = Char;
            node.isFucky = IsFucky;
            foreach (var fuckyStringNode in Childs)
            {
                FuckyStringNode childNode = new FuckyStringNode();
                fuckyStringNode.Value.Fill(childNode);
                node.childs.Add(childNode);
            }
        }
    }


    public class FuckyStringConfigAnalyzer : IAnalyzer
    {
        public const string TableName = "FuckyString";

        public void PrevProcess()
        {

        }

        public void PostCheck()
        {

        }

        public void Analyze()
        {
            

            Logger.LogAllLine("Analyze FuckyString================>");
            var reg = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Jet\4.0\Engines\Excel", true);
            reg.SetValue("TypeGuessRows", 0);

            var validNames = Enum.GetNames(typeof(PublishLanguages));
            var tabelNames = ExcelHelper.GetExcelTableNames(PathManager.InputConfigStringTablePath.FullName);
            foreach (string tableName in tabelNames)
            {
                string pureTableName = tableName.Replace("$", String.Empty).Replace("'", String.Empty).Replace(TableName, String.Empty);
                bool isValidTable = validNames.Any(pureTableName.Contains);
                if (!isValidTable||!tableName.Contains(TableName))
                {
                    continue;
                }

                var table = ExcelHelper.LoadDataFromExcel(PathManager.InputConfigStringTablePath.FullName, tableName);
                string resourceName = tableName.Replace("$", String.Empty);
                var packageInfo = PublishInfo.GetPublishInfo(resourceName);

                SortedDictionary<char, MyFuckyStringNode> rootNodes = new SortedDictionary<char, MyFuckyStringNode>();

                foreach (DataRow row in table.Rows)
                {
                    bool isValid = true;
                    bool isAllNull = true;
                    for (int i = 0; i < row.ItemArray.Length; i++)
                    {
                        if (row.IsNull(i))
                        {
                            isValid = false;
                        }
                        else
                        {
                            isAllNull = false;
                        }
                    }


                    if (isValid)
                    {
                        try
                        {
                            string str = Convert.ToString(row["Value"]).Trim();
                            string resultStr = ExcelHelper.ConvertToUTF8(str);

                            SortedDictionary<char, MyFuckyStringNode> nodes = rootNodes;
                            var chars = resultStr.ToCharArray();
                            for (int i = 0; i < chars.Length; ++i)
                            {
                                MyFuckyStringNode node;
                                if (!nodes.TryGetValue(chars[i], out node))
                                {
                                    node = new MyFuckyStringNode { Char = chars[i], IsFucky = i == chars.Length - 1 };
                                    nodes.Add(chars[i], node);
                                }
                                nodes = node.Childs;
                                if (!node.IsFucky)
                                {
                                    node.IsFucky = i == chars.Length - 1;
                                }
                            }


                        }
                        catch (Exception ex)
                        {
                            Logger.LogErrorLine(ex.Message);
                            ExcelHelper.PrintRow(row);
                        }

                    }
                    else if (!isAllNull)
                    {
                        Logger.LogErrorLine("Invalid string table line:");
                        ExcelHelper.PrintRow(row);
                    }
                }

                if ((PublishTarget.Current.PublishInfo.Language & packageInfo.Language) == packageInfo.Language)
                {
                    var config = new FuckyString();
                    foreach (var fuckyStringNode in rootNodes)
                    {
                        FuckyStringNode node = new FuckyStringNode();
                        fuckyStringNode.Value.Fill(node);
                        config.rootNodes.Add(node);
                    }

                    string tempPath = PathManager.OutputConfigPath + "/" + TableName +
                                      pureTableName + ".bin";
                    using (var file = File.Open(tempPath, FileMode.Create, FileAccess.ReadWrite))
                    {
                        Serializer.Serialize(file, config);
                        Logger.LogAllLine("Generate:{0}", tempPath);
                    }

                    var resourceFile = new FileListFile(new FileInfo(tempPath), true, true);
                    FileSystemGenerator.AddFileAndTag(resourceFile);

                }
                else
                {
                    Logger.LogAllLine("Ignore:\t{0}", pureTableName);
                }

            }
        }

    }

}