// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using GameKit.Coder;
using GameKit.Coder.LZMA;
using GameKit.Coder.XOR;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using Medusa.CoreProto;
using ProtoBuf;

namespace GameKit.Resource
{
    public class FileListGenerator
    {
        private readonly Dictionary<FileListFile, FileList.FileItem> mItemDict = new Dictionary<FileListFile, FileList.FileItem>();
        private readonly HashSet<string> mDirSet = new HashSet<string>();

        private FileList mFileList = new FileList();
        private uint mFileId;
        private readonly List<ICoder> mCoders = new List<ICoder>();
        private readonly List<FileList.FileCoder> mProtoCoders = new List<FileList.FileCoder>();

        public FileListGenerator()
        {
            Clear();
        }

        public void Clear()
        {
            mItemDict.Clear();
            mDirSet.Clear();
            mFileList = new FileList
            {
                CurVersion = PublishTarget.Current.ClientVersion.ToProtoVersion()
            };

            mFileId = 0;

            mCoders.Clear();
            mProtoCoders.Clear();
            if (PublishTarget.Current.IsCompress)
            {
                mCoders.Add(new LZMAEncoder(null));
                LZMADecoder decoder=new LZMADecoder(null);
                mProtoCoders.Add(decoder.CoderInfo);
            }

            if (PublishTarget.Current.IsEncrypt)
            {
                const string key = "{803CE8F2-8C0E-4159-96CB-921D89C08E13}{2519C077-1247-4AF5-8C71-C7367A481C2D}{975C6505-5494-4A36-9AD6-B4890B0E2F79}{B0DC6B72-83CC-4E81-8566-AD3AC306FE3A}{4B75FE65-1ADC-47AC-890A-293AD2A1968D}";
            
                var bytes = Encoding.UTF8.GetBytes(key);
                var keyBytes=BaseCoder.ByteArrayToString(bytes);
                mCoders.Add(new XOREncoder(bytes));

                XORDecoder decoder = new XORDecoder(null);
                mProtoCoders.Add(decoder.CoderInfo);
            }

            mProtoCoders.Reverse();
        }

        public uint AddFile(FileListFile file)
        {
            if (mItemDict.ContainsKey(file))
            {
                Logger.LogErrorLine("\tDuplicate File name: {0}\tVS\t{1}", file.FileInfo.Name,
                                   mItemDict[file]);
                return uint.MaxValue;
            }

            if (string.IsNullOrEmpty(file.FileInfo.Name))
            {
                Logger.LogErrorLine("Empty file item path:{0}", file);
                return uint.MaxValue;
            }

            string dirName = file.FileInfo.DirectoryName + Path.AltDirectorySeparatorChar;
            dirName = dirName.Replace(PathManager.InputPath.FullName, string.Empty);
            //dirName = dirName.Replace(PathManager.OutputResPath.FullName, string.Empty);
            dirName = dirName.Replace(PathManager.OutputPath.FullName, string.Empty);
            dirName = dirName.TrimStart(new[] { '\\', '/' });
            dirName = dirName.Replace(Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar);

            int dirIndex = -1;
            if (!string.IsNullOrEmpty(dirName))
            {
                if (!mDirSet.Contains(dirName))
                {
                    mDirSet.Add(dirName);
                    mFileList.Dirs.Add(dirName);
                    dirIndex = mFileList.Dirs.Count - 1;

                }
                else
                {
                    dirIndex = mDirSet.TakeWhile(dir => dir != dirName).Count();
                }
            }

            //if (file.IsCoded)
            //{
            //    file.IsCoded = file.FileInfo.Length > 1024 * 50;  //50K
            //}
            if (file.IsCoded)
            {
                CodeFile(file.FileInfo,file.Md5);
                file.UpdateFileInfo(file.FileInfo);
            }

            if (PublishTarget.Current.IsGuidName)
            {
                file.MakeGuidName();
            }

            var item = new FileList.FileItem
            {
                FileId = mFileId++,
                DirIndex = dirIndex,
                Name = file.FileInfo.Name,
                MD5 = file.Md5
            };

            if (file.IsCoded)
            {
                item.Coders.AddRange(mProtoCoders);
            }
            if (file.OriginalFileInfo!=null)
            {
                item.OriginalName = file.OriginalFileInfo.Name;
            }

            mFileList.Files.Add(item);
            return item.FileId;



        }

        public string GetFileName(uint fileId)
        {
            var fileItem= mFileList.Files.FirstOrDefault(file => file.FileId == fileId);
            if (fileItem!=null)
            {
                return mFileList.Dirs[fileItem.DirIndex] + fileItem.Name;
            }

            return string.Empty;
        }

        public void PrintDirectory(string prefix)
        {
            Logger.LogInfoLine("{0}{1}", prefix, "FileList Dirs:");
            string newPrefix = prefix + "\t";

            int index = 0;
            foreach (var dir in mFileList.Dirs)
            {
                Logger.LogInfoLine("{0}[{1}]\t{2}", newPrefix, index++, dir);
            }

            Logger.LogInfoLine("{0}{1}", prefix, "FileList Files:");
            foreach (var fileItem in mFileList.Files)
            {
                Logger.LogInfoLine("{0}[{1}]\t{2}\t({3})\t{4}", newPrefix, fileItem.DirIndex, fileItem.Name, fileItem.FileId, fileItem.MD5);

            }

        }

        public List<string> GetDirectories(string path)
        {
            var result = new Stack<string>();

            path = path.Replace(Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar);
            return path.Split(new[] { Path.AltDirectorySeparatorChar }, StringSplitOptions.RemoveEmptyEntries).ToList();
        }

        public MemoryStream Code(Stream ms)
        {
            var buffer = new byte[ms.Length];
            ms.Read(buffer, 0, (int)ms.Length);

            if (mCoders.Count != 0)
            {
                buffer = mCoders.Aggregate(buffer, (current, coder) => coder.Code(current));
            }
            
            return new MemoryStream(buffer);
        }

        public void CodeFile(FileInfo info,string md5)
        {
            if (PublishTarget.Current.IsCacheEnabled && !string.IsNullOrEmpty(md5) && FileCacheCenter.IsInCache(info,md5, FileCacheOperation.Encoded))
            {
                var cacheInfo = FileCacheCenter.GetCacheFileInfo(info,md5, FileCacheOperation.Encoded);
                cacheInfo.CopyTo(info.FullName, true);
            }
            else
            {
                MemoryStream ms;
                using (var tempFile = info.OpenRead())
                {
                    ms = Code(tempFile);
                }

                StreamWriter sw = new StreamWriter(info.FullName);
                ms.CopyTo(sw.BaseStream);
                sw.Close();

                if (PublishTarget.Current.IsCacheEnabled)
                {
                    FileCacheCenter.AddToCache(md5, info,FileCacheOperation.Encoded);
                }
            }

           
        }

        public void Save()
        {
            //add resource map to file system also
            using (var file = File.Open(PathManager.OutputFileListPath.FullName, FileMode.Create, FileAccess.ReadWrite))
            {
                Serializer.Serialize(file, mFileList);
            }

            CodeFile(PathManager.OutputFileListPath,string.Empty);

            Logger.LogAllLine("Generate:\t{0}", PathManager.OutputFileListPath.FullName);
        }
    }
}