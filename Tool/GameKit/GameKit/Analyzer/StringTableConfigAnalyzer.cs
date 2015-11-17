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
    public class StringTableConfigAnalyzer : IAnalyzer
    {
        public const string TableName = "StringTable";
        //name,order-value
        public static Dictionary<PublishInfo, Dictionary<string, Dictionary<uint, KeyValuePair<string,bool>>>> StringTables = new Dictionary<PublishInfo, Dictionary<string, Dictionary<uint, KeyValuePair<string, bool>>>>();
        public static  Dictionary<string,bool> mNameGroups=new Dictionary<string, bool>();


        public Dictionary<string, Dictionary<uint, KeyValuePair<string, bool>>> GetOrCreateStringTable(PublishInfo packageInfo)
        {
            if (StringTables.ContainsKey(packageInfo))
            {
                return StringTables[packageInfo];
            }
            var result = new Dictionary<string, Dictionary<uint, KeyValuePair<string, bool>>>();
            StringTables.Add(packageInfo, result);
            return result;
        }

        public void PrevProcess()
        {

        }

        public void PostCheck()
        {
            foreach (var stringTable in StringTables)
            {
                if (stringTable.Key.IsPublish(PublishTarget.Current))
                {
                    foreach (var dict in stringTable.Value)
                    {
                        if (mNameGroups.ContainsKey(dict.Key))
                        {
                            foreach (var strPair in dict.Value)
                            {
                                if (!strPair.Value.Value)
                                {
                                    Logger.LogAllLine("StringTable {0}:{1}-{2}  Not used!", stringTable.Key, dict.Key,
                                        strPair.Key);
                                }
                            }
                            
                        }
                        
                    }

                }
            }


        }

        public void Analyze()
        {
            StringTables.Clear();
            mNameGroups.Clear();

            Logger.LogAllLine("Analyze StringTable================>");
            var reg = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Jet\4.0\Engines\Excel", true);
            reg.SetValue("TypeGuessRows", 0);

            var validNames = Enum.GetNames(typeof(PublishLanguages));
            var tabelNames = ExcelHelper.GetExcelTableNames(PathManager.InputConfigStringTablePath.FullName);
            foreach (string tableName in tabelNames)
            {
                string pureTableName = tableName.Replace("$", String.Empty).Replace("'", String.Empty).Replace(TableName, String.Empty);
                bool isValidTable = validNames.Any(pureTableName.Contains);
                if (!isValidTable || !tableName.Contains(TableName))
                {
                    continue;
                }

                var table = ExcelHelper.LoadDataFromExcel(PathManager.InputConfigStringTablePath.FullName, tableName);
                string resourceName = tableName.Replace("$", String.Empty);
                var packageInfo = PublishInfo.GetPublishInfo(resourceName);


                var stringTable = GetOrCreateStringTable(packageInfo);
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
                            string name = Convert.ToString(row["name"]);
                            uint order = Convert.ToUInt32(row["order"]);
                            string str = Convert.ToString(row["value"]);

                            string resultStr = ExcelHelper.ConvertToUTF8(str);


                            Add(stringTable, name, order, resultStr);
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

                //print
                var stringTableResult = Parse(stringTable);

                if ((PublishTarget.Current.PublishInfo.Language & packageInfo.Language) == packageInfo.Language)
                {
                    string tempPath = PathManager.OutputConfigPath + "/" + TableName +
                                      pureTableName + ".bin";
                    using (var file = File.Open(tempPath, FileMode.Create, FileAccess.ReadWrite))
                    {
                        Serializer.Serialize(file, stringTableResult);
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

        public void Add(Dictionary<string, Dictionary<uint, KeyValuePair<string, bool>>> stringTable, string name, uint order, string str)
        {
            Dictionary<uint, KeyValuePair<string, bool>> orderItems = null;
            if (stringTable.ContainsKey(name))
            {
                orderItems = stringTable[name];
            }
            else
            {
                orderItems = new Dictionary<uint, KeyValuePair<string, bool>>();
                stringTable.Add(name, orderItems);
            }

            if (orderItems.ContainsKey(order))
            {
                Logger.LogAllLine("Duplicate String order:\t[{0}:{1}:{2}] VS [{3}:{4}:{5}]", name, order, str, name,
                                  order, orderItems[order]);
            }
            else
            {
                orderItems.Add(order, new KeyValuePair<string, bool>(str,false));
            }
        }

        public StringTable Parse(Dictionary<string, Dictionary<uint, KeyValuePair<string, bool>>> stringMap)
        {
            var stringTable = new StringTable();
            foreach (var nameItemMap in stringMap)
            {
                var nameItem = new StringNameItem { name = nameItemMap.Key };
                //Logger.LogInfoLine("\t{0}:", nameItemMap.Key);

                foreach (var orderItemPair in nameItemMap.Value)
                {
                    var orderItem = new StringOrderItem { order = orderItemPair.Key, value = orderItemPair.Value.Key };
                    nameItem.orderItems.Add(orderItem);
                    //Logger.LogInfoLine("\t\t{0}:\t{1}", orderItem.order, orderItem.value);
                }

                stringTable.nameItems.Add(nameItem);
            }

            return stringTable;
        }

        public static void AssertHasName(string name, uint order)
        {
            if (!mNameGroups.ContainsKey(name))
            {
                mNameGroups.Add(name,false);
            }

            foreach (var stringTable in StringTables)
            {
                if (stringTable.Key.IsPublish(PublishTarget.Current))
                {
                    Dictionary<uint, KeyValuePair<string, bool>> outDictionary;
                    if (stringTable.Value.TryGetValue(name, out outDictionary))
                    {
                        KeyValuePair<string, bool> outStr;
                        if (outDictionary.TryGetValue(order, out outStr))
                        {
                            if (!string.IsNullOrEmpty(outStr.Key))
                            {
                                outDictionary[order]=new KeyValuePair<string, bool>(outStr.Key,true);
                                continue;
                            }
                        }
                    }
                    Logger.LogAllLine("StringTable {0}:Cannot find {1}-{2}", stringTable.Key, name, order);

                }

            }
        }
    }

}