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
    public class UpdateServerGenerator
    {
        public static void Generate()
        {
            Logger.LogAllLine("Generate update server================>");

            //copy all res to server!
            SystemTool.ClearDirectory(PathManager.UpdateServerPath);
            SystemTool.CopyDirectory(PathManager.OutputPath, PathManager.UpdateServerPath);

            Logger.LogAllLine("Copy all res to UpdateServer!");

            var server = new UpdateServer
                {
                    Status = PublishTarget.Current.UpdateServerStatus,
                    MinVersion = PublishTarget.Current.UpdateServerMinClientVersion.ToProtoVersion(),
                    CurVersion = PublishTarget.Current.ClientVersion.ToProtoVersion(),
                    Description = PublishTarget.Current.UpdateServerDescription
                };

            //save
            using (var file = File.Open(PathManager.UpdateServerConfigPath.FullName, FileMode.Create, FileAccess.ReadWrite))
            {
                Serializer.Serialize(file, server);
            }

            //FileSystemGenerator.FileListGenerator.CodeFile(PathManager.UpdateServerConfigPath);
            Logger.LogAllLine("Generate:\t{0}", PathManager.UpdateServerConfigPath.FullName);
        }
    }
}