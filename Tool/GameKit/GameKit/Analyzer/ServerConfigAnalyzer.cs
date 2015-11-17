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
    public class ServerConfigAnalyzer : IAnalyzer
    {
        public static Dictionary<uint, bool> AllItems = new Dictionary<uint, bool>();
        public void PrevProcess()
        {

        }

        public void Analyze()
        {
            AllItems.Clear();

            Logger.LogAllLine("Analyze ServerConfig================>");
            var reg = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Jet\4.0\Engines\Excel", true);
            reg.SetValue("TypeGuessRows", 0);

            ServerConfig config = new ServerConfig();

            var table = ExcelHelper.LoadDataFromExcel(PathManager.InputConfigServerConfigPath.FullName, PathManager.ServerConfigTableName);
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
                        var configItem = new ServerConfigItem();
                        configItem.Id = Convert.ToUInt32(row["Id"]);
                        configItem.Address = Convert.ToString(row["Address"]);
                        configItem.Port = Convert.ToUInt32(row["Port"]);

                        configItem.Type = (ServerConfigItem.ServerType)Convert.ToUInt32(row["Type"]);

                        if (!AllItems.ContainsKey(configItem.Id))
                        {
                            AllItems.Add(configItem.Id,false);
                            config.Items.Add(configItem);

                        }
                        else
                        {
                            Logger.LogErrorLine("Duplicate Server Config line:");
                            ExcelHelper.PrintRow(row);
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
                    Logger.LogErrorLine("Invalid Server Config line:");
                    ExcelHelper.PrintRow(row);
                }
            }


            using (var file = PathManager.OutputConfigServerConfigPath.OpenWrite())
            {
                Serializer.Serialize(file, config);
            }

            var resourceFile = new FileListFile(PathManager.OutputConfigServerConfigPath, true, true);
            FileSystemGenerator.AddFileAndTag(resourceFile);

            Logger.LogAllLine("Generate:\t{0}", PathManager.OutputConfigServerConfigPath);

        }

        public void PostCheck()
        {
            foreach (var allItem in AllItems)
            {
                if (!allItem.Value)
                {
                    Logger.LogInfoLine("Server:Useless server id:{0}",allItem.Key);
                    
                }
            }
        }



    }

}