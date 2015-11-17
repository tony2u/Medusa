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
    public class ServerListAnalyzer : IAnalyzer
    {
        private Dictionary<uint, bool> mUsedItemIds = new Dictionary<uint, bool>();

        public void PrevProcess()
        {
           
        }

        public void Analyze()
        {
            mUsedItemIds.Clear();

            Logger.LogAllLine("Analyze ServerList================>");
            var reg = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Jet\4.0\Engines\Excel", true);
            reg.SetValue("TypeGuessRows", 0);

            ServerList config = new ServerList();

            var table = ExcelHelper.LoadDataFromExcel(PathManager.InputConfigServerConfigPath.FullName, PathManager.ServerListTableName);
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
                        var configItem = new ServerListItem();
                        configItem.Id = Convert.ToUInt32(row["Id"]);
                        var serverUsages = ParseServerUsages(Convert.ToString(row["ServerUsages"]));
                        configItem.ServerUsages.AddRange(serverUsages);

                        foreach (var serverUsageItem in serverUsages)
                        {
                            if (!mUsedItemIds.ContainsKey(serverUsageItem.ServerId))
                            {
                                mUsedItemIds.Add(serverUsageItem.ServerId,false);
                            }
                        }
                        config.Items.Add(configItem);
                    }
                    catch (Exception ex)
                    {
                        Logger.LogErrorLine(ex.Message);
                        ExcelHelper.PrintRow(row);
                    }
                  
                }
                else if(!isAllNull)
                {
                    Logger.LogErrorLine("Invalid Server Config line:");
                    ExcelHelper.PrintRow(row);
                }
            }

           
            using (var file = PathManager.OutputConfigServerListPath.OpenWrite())
            {
                Serializer.Serialize(file, config);
            }

            var resourceFile = new FileListFile(PathManager.OutputConfigServerListPath, true, true);
            FileSystemGenerator.AddFileAndTag(resourceFile);

            Logger.LogAllLine("Generate:\t{0}", PathManager.OutputConfigServerListPath);

        }



        public void PostCheck()
        {
            foreach (var usedItemId in mUsedItemIds)
            {
                if (!ServerConfigAnalyzer.AllItems.ContainsKey(usedItemId.Key))
                {
                    Logger.LogErrorLine("ServerList:Cannot find server:{0} in Server table",usedItemId.Key);
                }
                else
                {
                    ServerConfigAnalyzer.AllItems[usedItemId.Key] = true;
                }
            }
        }


        public static List<ServerUsageItem> ParseServerUsages(string data)
        {
            List<ServerUsageItem> result = new List<ServerUsageItem>();
            if (string.IsNullOrEmpty(data) || data == "0")
            {
                return result;
            }

            string[] strs = data.Split(new[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var str in strs)
            {
                var keyValue = str.Split(new[] { ':' }, StringSplitOptions.RemoveEmptyEntries);
                if (keyValue.Length != 2)
                {
                    Logger.LogErrorLine("Error ServerUsageItem:{0}", data);
                    result.Clear();
                    return result;
                }

                uint idType;
                uint id;
                if (!uint.TryParse(keyValue[0], out idType) || !uint.TryParse(keyValue[1], out id) )
                {
                    Logger.LogErrorLine("Error ServerUsageItem:{0}", data);
                    result.Clear();
                    return result;
                }

                ServerUsageItem item = new ServerUsageItem();
                item.Usage = (ServerUsageType)idType;
                item.ServerId = id;


                result.Add(item);

            }

            return result;
        }


    }

}