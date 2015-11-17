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
    public class AndroidAssetGenerator
    {
        public static void Generate()
        {
            if (!PathManager.IsDevAvailable)
            {
                return;
            }

            Logger.LogAllLine("Generate Android asset================>");
           
            List<string> excludeFiles=new List<string>();

            //copy all res to server!
            SystemTool.ClearDirectory(PathManager.AndroidAssetPath);
            SystemTool.CopyDirectory(PathManager.OutputPath, PathManager.AndroidAssetPath, true, excludeFiles);

            Logger.LogAllLine("Copy all res to Android asset!");
        }
    }
}