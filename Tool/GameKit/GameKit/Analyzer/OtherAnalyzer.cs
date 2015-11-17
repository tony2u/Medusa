// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.IO;
using GameKit.Log;

using GameKit.Publish;
using GameKit.Resource;
using Medusa.CoreProto;
using ProtoBuf;

namespace GameKit.Analyzer
{
    public class OtherAnalyzer : IAnalyzer
    {
        public void PrevProcess()
        {

        }

        public void Analyze()
        {
            Logger.LogAllLine("Analyze Other================>");

            var files = SystemTool.GetDirectoryFiles(PathManager.InputOtherPath);

            foreach (var animationFile in files)
            {
                var resourceFile = new FileListFile(animationFile);
                FileSystemGenerator.CopyFileToOutput(resourceFile);

            }
        }

        public void PostCheck()
        {
            
        }
    }
}