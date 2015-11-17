// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Windows.Forms;
using GameKit.Publish;

namespace GameKit
{
    public static class SystemTool
    {
        public static string GetRelativePath(string path)
        {
            return System.Environment.CurrentDirectory + path;
        }

        public static List<FileInfo> GetDirectoryFiles(DirectoryInfo path, bool isRecursively = true)
        {
            var files = path.GetFiles();
            var result = files.ToList();

            if (isRecursively)
            {
                var dirs = path.GetDirectories();
                foreach (var dir in dirs)
                {
                    result.AddRange(GetDirectoryFiles(dir, isRecursively));
                }
            }

            return result;
        }


        public static void ClearDirectory(DirectoryInfo path, bool isRecursively = true)
        {
            //Directory.Delete(path,true);

            if (!path.Exists)
            {
                return;
            }
            var files = path.GetFiles();
            foreach (var file in files)
            {
                file.Delete();
            }

            if (isRecursively)
            {
                var dirs = path.GetDirectories();
                foreach (var dir in dirs)
                {
                    ClearDirectory(dir);
                    bool isSuccess = false;
                    while (!isSuccess)
                    {
                        try
                        {
                            dir.Delete();
                            isSuccess = true;
                        }
                        catch (Exception)
                        {
                            isSuccess = false;
                        }
                        Thread.Sleep(1);
                    }
                }
            }
        }

        public static void ClearEmptyDirectory(DirectoryInfo path)
        {
            var dirs = path.GetDirectories();
            foreach (var dir in dirs)
            {
                ClearEmptyDirectory(dir);
            }

            dirs = path.GetDirectories();
            if (path.GetFiles().Length == 0 && dirs.Length == 0)
            {
                path.Delete();
            }
        }

        public static void CopyDirectoryTree(DirectoryInfo sourcePath, DirectoryInfo destPath, List<string> excludeDirs = null)
        {
            if (!destPath.Exists)
            {
                destPath.Create();
            }

            var dirs = sourcePath.GetDirectories();
            foreach (var dir in dirs)
            {
                if (excludeDirs != null && excludeDirs.Contains(dir.Name))
                {
                    continue;
                }
                string pathName = dir.FullName.Replace(sourcePath.FullName, string.Empty);
                string newDestPath = destPath.FullName + pathName;
                CopyDirectoryTree(dir, new DirectoryInfo(newDestPath));
            }
        }

        public static void CopyDirectory(DirectoryInfo sourcePath, DirectoryInfo destPath,bool isClearDestPath=false,List<string> excludeFiles=null )
        {
            if (!destPath.Exists)
            {
                destPath.Create();
            }

            var files = sourcePath.GetFiles();
            foreach (var file in files)
            {
                string newPath = String.Format("{0}/{1}", destPath.FullName, file.Name);
                if (excludeFiles==null||!excludeFiles.Contains(file.Name))
                {
                    //FastCopy(file.FullName, newPath);
                    file.CopyTo(newPath, true);
                }
            }

            var dirs = sourcePath.GetDirectories();
            foreach (var dir in dirs)
            {
                string pathName = dir.FullName.Replace(sourcePath.FullName, string.Empty);
                string newDestPath = destPath.FullName + pathName;
                DirectoryInfo destDirInfo = new DirectoryInfo(newDestPath);
                if (isClearDestPath)
                {
                    ClearDirectory(destDirInfo, true);
                }
                CopyDirectory(dir, destDirInfo);
            }
        }

        public static void FastCopy(string fromPath, string outputFilePath)
        {
            int bufferSize = 1024 * 1024;
            using (FileStream inStream = new FileStream(fromPath, FileMode.Open, FileAccess.Read))
            {
                using (FileStream fileStream = new FileStream(outputFilePath, FileMode.OpenOrCreate, FileAccess.Write))
                {
                    fileStream.SetLength(inStream.Length);
                    int bytesRead = -1;
                    byte[] bytes = new byte[bufferSize];

                    while ((bytesRead = inStream.Read(bytes, 0, bufferSize)) > 0)
                    {
                        fileStream.Write(bytes, 0, bytesRead);
                    }
                }
            }
           
        }

        public static Medusa.CoreProto.Version ToProtoVersion(this Version val)
        {
            return new Medusa.CoreProto.Version()
            {
                Major = (uint)val.Major,
                Minor = (uint)val.Minor,
                Build = (uint)val.Build,
                Revision = (uint)val.Revision
            };
        }

        public static System.Version ToSystemVersion(this Medusa.CoreProto.Version val)
        {
            return new Version((int) val.Major, (int) val.Minor, (int) val.Build, (int) val.Revision);
        }
    }

     
}