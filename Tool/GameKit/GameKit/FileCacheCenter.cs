// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using GameKit.Resource;
using Medusa.CoreProto;
using ProtoBuf;

namespace GameKit
{
    public enum FileCacheOperation
    {
        ImageOptimzed,
        Encoded,
        PVR
    }

    public static class FileCacheCenter
    {
        static FileCacheCenter()
        {
            ImageOptimzedFiles = new Dictionary<string, FileCacheItem>();
            EncodedFiles = new Dictionary<string, FileCacheItem>();
            PVRFiles = new Dictionary<string, FileCacheItem>();

            mFileCache = new FileCache();
            mFileSystem = new FileSystem();
        }
        public static string FileCacheLogFileName = "FileCacheLog.txt";


        public static DirectoryInfo ImageOptimzedPath
        {
            get { return new DirectoryInfo(Path.Combine(PathManager.TempPath.FullName, FileCacheOperation.ImageOptimzed.ToString())); }
        }

        public static DirectoryInfo EncodedPath
        {
            get { return new DirectoryInfo(Path.Combine(PathManager.TempPath.FullName, FileCacheOperation.Encoded.ToString())); }
        }
        public static DirectoryInfo PVRPath
        {
            get { return new DirectoryInfo(Path.Combine(PathManager.TempPath.FullName, FileCacheOperation.PVR.ToString())); }
        }

        public static FileInfo ImageOptimzedLogPath
        {
            get { return new FileInfo(Path.Combine(ImageOptimzedPath.FullName, FileCacheLogFileName)); }
        }

        public static Dictionary<String, FileCacheItem> ImageOptimzedFiles { get; private set; }
        public static Dictionary<String, FileCacheItem> EncodedFiles { get; private set; }
        public static Dictionary<String, FileCacheItem> PVRFiles { get; private set; }

        public static FileCache mFileCache { get; set; }
        public static FileSystem mFileSystem { get; set; }


        public static void Clear()
        {
            ImageOptimzedFiles.Clear();
            EncodedFiles.Clear();
            PVRFiles.Clear();

        }

        public static Dictionary<String, FileCacheItem> GetFileCacheItems(FileCacheOperation operation)
        {
            switch (operation)
            {
                case FileCacheOperation.ImageOptimzed:
                    return ImageOptimzedFiles;
                case FileCacheOperation.Encoded:
                    return EncodedFiles;
                case FileCacheOperation.PVR:
                    return PVRFiles;

            }
            return null;
        }

        public static DirectoryInfo GetTempDirectoryInfo(FileCacheOperation operation)
        {
            switch (operation)
            {
                case FileCacheOperation.ImageOptimzed:
                    return ImageOptimzedPath;
                case FileCacheOperation.Encoded:
                    return EncodedPath;
                case FileCacheOperation.PVR:
                    return PVRPath;

            }
            return null;
        }

        public static void Initialize()
        {
            if (!PathManager.TempPath.Exists)
            {
                PathManager.TempPath.Create();
            }

            if (!ImageOptimzedPath.Exists)
            {
                ImageOptimzedPath.Create();
            }

            if (!EncodedPath.Exists)
            {
                EncodedPath.Create();
            }

            if (!PVRPath.Exists)
            {
                PVRPath.Create();
            }

            Clear();
            mFileCache.items.Clear();


            if (File.Exists(PathManager.TempFileCachePath.FullName))
            {
                //add resource map to file system also
                using (var file = File.Open(PathManager.TempFileCachePath.FullName, FileMode.Open, FileAccess.Read))
                {
                    mFileCache = Serializer.Deserialize<FileCache>(file);
                }
            }

            List<FileCacheItem> removeItems = new List<FileCacheItem>();
            foreach (var fileCacheItem in mFileCache.items)
            {
                var fileDict = GetFileCacheItems((FileCacheOperation)fileCacheItem.Operation);
                //Hack
                //FileInfo info = new FileInfo(fileCacheItem.OriginalName);
                //fileCacheItem.OriginalName = info.Name;

                //if (fileCacheItem.OriginalName.EndsWith(".pvr"))
                //{
                //    fileCacheItem.OriginalName = fileCacheItem.OriginalName.Replace(".pvr", ".png");
                //}
                //Hack

                if (!fileDict.ContainsKey(fileCacheItem.OriginalName))
                {
                    fileDict.Add(fileCacheItem.OriginalName, fileCacheItem);
                }
                else
                {
                    var oldItem = fileDict[fileCacheItem.OriginalName];
                    if (fileCacheItem.TextureRect != null)
                    {
                        oldItem.TextureRect = fileCacheItem.TextureRect;
                    }

                    if (fileCacheItem.Offset != null)
                    {
                        oldItem.Offset = fileCacheItem.Offset;
                    }

                    if (fileCacheItem.OriginalName != null)
                    {
                        oldItem.OriginalName = fileCacheItem.OriginalName;
                    }
                    Logger.LogInfoLine("FileCache FileSystem Duplicate:{0}", fileCacheItem.path);

                    removeItems.Add(fileCacheItem);
                }


            }

            foreach (var fileCacheItem in removeItems)
            {
                mFileCache.items.Remove(fileCacheItem);
                var dir = GetTempDirectoryInfo((FileCacheOperation)fileCacheItem.Operation);

                var fileDict = GetFileCacheItems((FileCacheOperation)fileCacheItem.Operation);
                if (!fileDict.ContainsKey(fileCacheItem.OriginalName))
                {
                    var curPath = Path.Combine(dir.FullName, fileCacheItem.path);
                    File.Delete(curPath);
                }
               

            }


            if (File.Exists(PathManager.TempFileSystemPath.FullName))
            {
                //add resource map to file system also
                using (var file = File.Open(PathManager.TempFileSystemPath.FullName, FileMode.Open, FileAccess.Read))
                {
                    mFileSystem = Serializer.Deserialize<FileSystem>(file);
                }
            }

            Save();

        }

        public static void End()
        {
            Save();
            SaveLog();
        }

        public static void SaveLog()
        {
            using (var file = File.Open(ImageOptimzedLogPath.FullName, FileMode.Create, FileAccess.ReadWrite))
            {
                using (StreamWriter sw = new StreamWriter(file))
                {
                    foreach (var fileCacheItem in mFileCache.items)
                    {
                        if (fileCacheItem.TextureRect != null || fileCacheItem.Offset != null)
                        {
                            StringBuilder sb = new StringBuilder();
                            sb.AppendFormat("{0}", fileCacheItem.path);

                            if (fileCacheItem.TextureRect != null)
                            {
                                sb.AppendFormat("\tTexture:{0},{1},{2},{3}", fileCacheItem.TextureRect.Origin.X, fileCacheItem.TextureRect.Origin.Y, fileCacheItem.TextureRect.Size.Width, fileCacheItem.TextureRect.Size.Height);
                            }

                            if (fileCacheItem.Offset != null)
                            {
                                sb.AppendFormat("\tOffset:{0},{1}", fileCacheItem.Offset.X, fileCacheItem.Offset.Y);
                            }

                            sw.WriteLine(sb.ToString());
                        }
                    }
                }
            }
        }

        public static void Save()
        {
            mFileCache.items.Sort((l, r) => System.String.Compare(l.path, r.path, System.StringComparison.Ordinal));
            //save
            using (var file = File.Open(PathManager.TempFileCachePath.FullName, FileMode.Create, FileAccess.ReadWrite))
            {
                Serializer.Serialize(file, mFileCache);
            }
        }

        public static void TryUpdate(FileCacheItem item)
        {
            if (mFileSystem == null)
            {
                return;
            }
            var resourceName = FileListFile.GetResourceName(item.path);
            var resourceOrder = FileListFile.GetResourceOrder(item.path);

            FileSystemOrderItem orderItem = null;
            foreach (var tagItems in mFileSystem.TagItems)
            {
                foreach (var fileSystemNameItem in tagItems.NameItems)
                {
                    if (fileSystemNameItem.Name == resourceName)
                    {
                        foreach (var fileSystemOrderItem in fileSystemNameItem.OrderItems)
                        {
                            if (fileSystemOrderItem.Order == resourceOrder)
                            {
                                if (orderItem == null)
                                {
                                    orderItem = fileSystemOrderItem;
                                }
                                else
                                {
                                    return;
                                }
                            }
                        }
                    }
                }
            }

            if (orderItem != null)
            {
                item.TextureRect = orderItem.TextureRect;
                item.Offset = orderItem.Offset;
                Logger.LogInfoLine("FileCache FileSystem Hit:{0}", item.path);
            }
        }

        public static bool IsInCacheWithoutMd5(FileInfo originalInfo, FileCacheOperation operation)
        {
            var fileDict = GetFileCacheItems(operation);

            if (fileDict.ContainsKey(originalInfo.Name))
            {
                return true;
            }


            return false;
        }


        public static void RemoveCacheWithoutMd5(FileInfo originalInfo, FileCacheOperation operation)
        {
            var fileDict = GetFileCacheItems(operation);
            if (fileDict.ContainsKey(originalInfo.Name))
            {
                var item= fileDict[originalInfo.Name];
                fileDict.Remove(originalInfo.Name);
                mFileCache.items.Remove(item);
            }

        }


        public static bool IsInCache(FileInfo originalInfo, string md5, FileCacheOperation operation)
        {
            var fileDict = GetFileCacheItems(operation);

            if (fileDict.ContainsKey(originalInfo.Name))
            {
                var file = fileDict[originalInfo.Name];
                if (file.md5 == md5)
                {
                    return true;
                }
            }


            return false;
        }

        public static FileCacheItem GetCacheFileItemHelperWithoutMd5(FileInfo originalInfo, FileCacheOperation operation)
        {
            var fileDict = GetFileCacheItems(operation);

            if (fileDict.ContainsKey(originalInfo.Name))
            {
                var file = fileDict[originalInfo.Name];
                return file;
            }

            return null;
        }

        public static FileCacheItem GetCacheFileItemHelper(FileInfo originalInfo, string md5, FileCacheOperation operation)
        {
            var fileDict = GetFileCacheItems(operation);

            if (fileDict.ContainsKey(originalInfo.Name))
            {
                var file = fileDict[originalInfo.Name];
                if (file.md5 == md5)
                {
                    return file;
                }
            }

            return null;
        }


        public static FileCacheItem GetCacheFileItem(FileInfo originalInfo, string md5, FileCacheOperation operation)
        {

            if (IsInCache(originalInfo, md5, operation))
            {
                var curItem = GetCacheFileItemHelper(originalInfo, md5, operation);
                TryUpdate(curItem);
                return curItem;
            }

            return null;
        }

        public static FileInfo GetCacheFileInfo(FileInfo originalInfo, string md5, FileCacheOperation operation)
        {

            if (IsInCache(originalInfo, md5, operation))
            {
                var curItem = GetCacheFileItemHelper(originalInfo, md5, operation);
                var dir = GetTempDirectoryInfo(operation);
                var curPath = Path.Combine(dir.FullName, curItem.path);
                return new FileInfo(curPath);
            }

            return null;

        }

        public static FileInfo GetCacheNewFileInfo(string path, FileCacheOperation operation)
        {
            FileInfo info = new FileInfo(path);
            var dir = GetTempDirectoryInfo(operation);
            var curPath = Path.Combine(dir.FullName, info.Name);
            return new FileInfo(curPath);
        }

        public static string CopyCacheToDirectory(FileInfo originalInfo, string md5, DirectoryInfo path, FileCacheOperation operation)
        {


            if (IsInCache(originalInfo, md5, operation))
            {
                var curItem = GetCacheFileItemHelper(originalInfo, md5, operation);
                var dir = GetTempDirectoryInfo(operation);
                var curPath = Path.Combine(dir.FullName, curItem.path);
                string newPath = Path.Combine(path.FullName, curItem.path);
                File.Copy(curPath, newPath, true);
                return newPath;
            }
            else
            {
                Logger.LogAllLine("Invalid copy {0} to path", md5, path);
                return string.Empty;
            }


        }

        public static void AddToCache(string md5, FileInfo path, FileCacheOperation operation)
        {
            var fileDict = GetFileCacheItems(operation);
            var dir = GetTempDirectoryInfo(operation);

            if (IsInCache(path, md5, operation))
            {
                var curItem = GetCacheFileItemHelper(path, md5, operation);
                var curPath = Path.Combine(dir.FullName, curItem.path);
                File.Delete(curPath);
                mFileCache.items.Remove(curItem);
                fileDict.Remove(path.Name);
            }

            RemoveCacheWithoutMd5(path, operation);

            FileCacheItem item = new FileCacheItem { path = path.Name, Operation = (uint)operation, OriginalName = path.Name };
            item.md5 = md5;

            mFileCache.items.Add(item);
            fileDict.Add(item.OriginalName, item);

            string newPath = Path.Combine(dir.FullName, path.Name);
            File.Copy(path.FullName, newPath, true);
            Save();
        }

        public static void AddToCacheWithoutCopy(string md5, FileInfo path, FileCacheOperation operation)
        {
            var fileDict = GetFileCacheItems(operation);

            FileCacheItem item = new FileCacheItem { md5 = md5, path = path.Name, Operation = (uint)operation, OriginalName = path.Name };
            if (IsInCache(path, md5, operation))
            {
                fileDict.Remove(item.OriginalName);
                var curItem = GetCacheFileItemHelper(path, md5, operation);
                mFileCache.items.Remove(curItem);
            }

            mFileCache.items.Add(item);
            RemoveCacheWithoutMd5(path, operation);
            fileDict.Add(item.OriginalName, item);

            Save();
        }

        public static void AddToCacheWithoutCopy(string md5, FileInfo path, Rectangle? textureRect, Point? offset, FileCacheOperation operation)
        {
            var fileDict = GetFileCacheItems(operation);

            FileCacheItem item = new FileCacheItem { md5 = md5, path = path.Name, Operation = (uint)operation, OriginalName = path.Name };
            if (textureRect.HasValue)
            {
                item.TextureRect = new RectU();
                item.TextureRect.Origin = new PointU();
                item.TextureRect.Origin.X = (uint)textureRect.Value.X;
                item.TextureRect.Origin.Y = (uint)textureRect.Value.Y;

                item.TextureRect.Size = new SizeU();
                item.TextureRect.Size.Width = (uint)textureRect.Value.Size.Width;
                item.TextureRect.Size.Height = (uint)textureRect.Value.Size.Height;

            }

            if (offset.HasValue)
            {
                item.Offset = new PointU();
                item.Offset.X = (uint)offset.Value.X;
                item.Offset.Y = (uint)offset.Value.Y;

            }

            if (IsInCache(path, md5, operation))
            {
                fileDict.Remove(item.OriginalName);
                var curItem = GetCacheFileItemHelper(path, md5, operation);
                mFileCache.items.Remove(curItem);
            }

            mFileCache.items.Add(item);
            RemoveCacheWithoutMd5(path, operation);
            fileDict.Add(item.OriginalName, item);

            Save();
        }

    }
}