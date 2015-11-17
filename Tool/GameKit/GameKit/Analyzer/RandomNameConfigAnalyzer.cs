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
    public class RandomNameConfigAnalyzer : IAnalyzer
    {
        public const string TableName = "RandomName";

       
        public void PrevProcess()
        {

        }

        public void PostCheck()
        {

        }

        public void Analyze()
        {
            Logger.LogAllLine("Analyze RandomName================>");
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


                RandomNameConfig config=new RandomNameConfig();
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

                            RandomNameConfigItem item=new RandomNameConfigItem();
                            item.Position = Convert.ToUInt32(row["Position"]);
                            item.Value= Convert.ToString(row["Value"]);
                            item.Value = ExcelHelper.ConvertToUTF8(item.Value);
                            config.Items.Add(item);
                            
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
                if ((PublishTarget.Current.PublishInfo.Language & packageInfo.Language) == packageInfo.Language)
                {
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