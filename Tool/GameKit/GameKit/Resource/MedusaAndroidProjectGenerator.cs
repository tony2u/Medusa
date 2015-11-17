// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using System.IO;
using System.Text;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using Medusa.CoreProto;
using ProtoBuf;

namespace GameKit.Resource
{
    public class MedusaAndroidProjectGenerator
    {
        public const string ProjectName = "Medusa";
        public static List<FileInfo> GetSrcFiles(DirectoryInfo path)
        {
            List<string> acceptExtensions = new List<string>() { ".cc", ".c", ".cpp", ".S" };
            List<FileInfo> srcFiles = new List<FileInfo>();
            var files = SystemTool.GetDirectoryFiles(path);
            foreach (var fileInfo in files)
            {
                if (acceptExtensions.Contains(fileInfo.Extension))
                {
                    srcFiles.Add(fileInfo);
                }
            }

            return srcFiles;
        }


        public static void Generate()
        {
            if (!PathManager.IsDevAvailable)
            {
                return;
            }

            DirectoryInfo projectPath = PathManager.RootPath.CreateSubdirectory("Medusa/" + ProjectName);
            FileInfo mkPath=new FileInfo(Path.Combine(projectPath.FullName,"Android.mk"));
            Logger.LogAllLine("Generate {0} Android project================>", ProjectName);
           

            List<FileInfo> srcFiles = new List<FileInfo>();
            //srcFiles.AddRange(GetSrcFiles(projectPath));

            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Application")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Audio")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Content")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Game")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Graphics")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Platform")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Rendering")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Resource")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Scene")));

            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Lib/Common/libjpeg")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Lib/Common/libpng")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Lib/Common/libtiff")));
            srcFiles.AddRange(GetSrcFiles(projectPath.CreateSubdirectory("Lib/Common/PVR")));


            var text = File.ReadAllText(mkPath.FullName);
            string  newText = GenerateSrcFiles(text, srcFiles, projectPath,string.Empty);
            if (text!=newText)
            {
                File.WriteAllText(mkPath.FullName, newText);
            }

            //#BEGIN_AUTO_GENERATE_SRC_FILES
            //#END_AUTO_GENERATE_SRC_FILES

            Logger.LogAllLine("Create {0} Android project!", ProjectName);
        }

        public static string GenerateSrcFiles(string text, List<FileInfo> srcFiles, DirectoryInfo projectPath, string dirPrefix)
        {
            const string begin = "#BEGIN_AUTO_GENERATE_SRC_FILES";
            const string end = "#END_AUTO_GENERATE_SRC_FILES";

            int beginIndex = text.IndexOf(begin) + begin.Length;
            int endIndex = text.IndexOf(end);

            text = text.Remove(beginIndex, endIndex - beginIndex);
            StringBuilder result = new StringBuilder();
            result.AppendLine();
            result.AppendLine(@"LOCAL_SRC_FILES :=\");
            result.AppendLine(@"MedusaVersion.cpp \");
            result.AppendLine(@"MedusaPreCompiled.cpp \");



            int i = srcFiles.Count;
            foreach (var fileInfo in srcFiles)
            {
                --i;
                string fileName = dirPrefix + fileInfo.FullName.Replace(projectPath.FullName, string.Empty).Remove(0, 1);
                fileName = fileName.Replace('\\', '/');
                if (i!=0)
                {
                    fileName += " \\";
                }

                result.AppendLine(fileName);
            }



            text = text.Insert(beginIndex, result.ToString());
            return text;
        }
    }
}