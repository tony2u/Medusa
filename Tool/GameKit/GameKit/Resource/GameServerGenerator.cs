// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using System.IO;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using Medusa.CoreProto;
using ProtoBuf;

namespace GameKit.Resource
{
    public class GameServerGenerator
    {
        public static void Generate()
        {
            Logger.LogAllLine("Generate game server================>");
            if (!PathManager.IsDevAvailable)
            {
                return;
            }

            List<string> excludeFiles=new List<string>();
            excludeFiles.Add("PaperConfig.bin");
            excludeFiles.Add("StringTable-zhcn.bin");
            excludeFiles.Add("StringTable-enus.bin");

            //copy all res to server!
            SystemTool.ClearDirectory(PathManager.GameServerPath);
            SystemTool.CopyDirectory(PathManager.OutputConfigPath, PathManager.GameServerPath,true,excludeFiles);

            Logger.LogAllLine("Copy all res to Game Server!");
        }
    }
}