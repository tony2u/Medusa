// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Linq;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using GameKit.Resource;

namespace GameKit
{
    public static class DataCenter
    {
        static DataCenter()
        {
            LayerFileDict = new Dictionary<string, FileListFile>();
            MissionDict = new Dictionary<uint, bool>();
        }


        public static Dictionary<String, FileListFile> LayerFileDict { get; private set; }
        public static Dictionary<uint, bool> MissionDict { get; private set; }
        public static Dictionary<uint, bool> HeroDict { get; private set; }



        public static void Clear()
        {
            LayerFileDict.Clear();
            MissionDict.Clear();
        }

        public static void AddLayerFile(FileListFile file)
        {
            if (!LayerFileDict.ContainsKey(file.FileInfo.Name))
            {
                LayerFileDict[file.FileInfo.Name] = file;
            }
        }

        public static FileListFile GetLayerFile(string modelName)
        {
            if (LayerFileDict.ContainsKey(modelName))
            {
                return LayerFileDict[modelName];
            }

            return null;
        }

     

       

        public static void AddMissionId(uint id)
        {
            if (MissionDict.ContainsKey(id))
            {
                Logger.LogErrorLine("Invalid mission id:{0}", id);
                return;
            }

            MissionDict.Add(id, false);
        }

        public static bool CheckAndUseMissionIdValid(uint id)
        {
            if (!MissionDict.ContainsKey(id))
            {
                Logger.LogErrorLine("Invalid mission id:{0}", id);
                return false;
            }

            MissionDict[id] = true;
            return true;
        }
    }
}