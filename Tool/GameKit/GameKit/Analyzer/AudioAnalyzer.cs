// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.IO;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using GameKit.Resource;

namespace GameKit.Analyzer
{
    public class AudioAnalyzer : IAnalyzer
    {
        public void PrevProcess()
        {
            
        }

        public void Analyze()
        {
            Logger.LogAllLine("Analyze Audio================>");

            var files = SystemTool.GetDirectoryFiles(PathManager.InputAudioPath);

            foreach (var file in files)
            {
                if (file.Extension == ".wav" || file.Extension == ".mp3")
                {
                    var resourceFile = new FileListFile(file);
                    FileSystemGenerator.CopyFileToOutput(resourceFile);
                }
              

            }

        }

        public void PostCheck()
        {
            
        }

        private void GetFileList(string path, string prefix)
        {
            var files = Directory.GetFiles(path);
            foreach (string file in files)
            {
                var fileInfo = new FileInfo(file);
                var resourceFile = new FileListFile(fileInfo);

                FileSystemGenerator.AddFileAndTag(resourceFile);
                

                Logger.LogInfoLine("{0}File: {1}", prefix, fileInfo.FullName);
                CopyAudio(resourceFile);
            }

            var dirs = Directory.GetDirectories(path);
            foreach (string dir in dirs)
            {
                var directoryInfo = new DirectoryInfo(dir);
                Logger.LogInfoLine("{0}Dir:\t{1}", prefix, directoryInfo.Name);
                GetFileList(dir, prefix + "\t");
            }
        }

        private void CopyAudio(FileListFile audioFile)
        {
            var packageInfo = PublishInfo.GetPublishInfo(audioFile.FileInfo.FullName);
            if (packageInfo.IsPublish(PublishTarget.Current))
            {
                string tempFilePath = PathManager.OutputPath + Path.AltDirectorySeparatorChar.ToString() + PathManager.AudioDirectoryName + Path.AltDirectorySeparatorChar.ToString() + audioFile.FileInfo.Name;
                audioFile.FileInfo.CopyTo(tempFilePath);
            }
        }
    }
}