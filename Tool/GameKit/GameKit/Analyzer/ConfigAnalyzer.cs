// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.IO;
using GameKit.Log;
using GameKit.Publish;
using GameKit.Resource;

namespace GameKit.Analyzer
{
    public class ConfigAnalyzer : IAnalyzer
    {
        public void PrevProcess()
        {
        }

        public void Analyze()
        {
            Logger.LogAllLine("Analyze config================>");

            FileListFile fileListFile = new FileListFile(PathManager.InputConfigPaperConfigPath, true, true);
            FileSystemGenerator.CopyFileToOutput(fileListFile);

            fileListFile = new FileListFile(PathManager.InputConfigServerGameConfigPath, true, true);
            FileSystemGenerator.CopyFileToOutput(fileListFile);
        }

        public void PostCheck()
        {
            
        }
      
    }
}