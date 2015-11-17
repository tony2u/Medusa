// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.IO;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using Medusa.CoreProto;
using ProtoBuf;

namespace GameKit.Resource
{
    public class ProjectCopier
    {
        public static void Generate()
        {
            if (!PathManager.IsDevAvailable)
            {
                return;
            }

           
            Logger.LogAllLine("Copy to project path");
            //copy all res to server!
            SystemTool.CopyDirectory(PathManager.OutputPath, PathManager.ProjectPath,true);

            Logger.LogAllLine("Copy all res to Project!");
        }
    }
}