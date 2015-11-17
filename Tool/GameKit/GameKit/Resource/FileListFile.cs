// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using GameKit.Packing;
using GameKit.Publish;
using Medusa.CoreProto;

namespace GameKit.Resource
{
    public class FileListFile
    {
        public FileListFile(FileInfo filePath, bool enablePacking = true,bool isCoded=false)
        {
            FileInfo = filePath;
            ResourceName = GetResourceName(FileInfo.Name);
            Order = GetResourceOrder(FileInfo.Name);
            IsPacked = false;
            IsPVREnabled = false;
            EnablePacking = enablePacking;
            PublishGroup = PublishGroup.GetPublishGroup(FileInfo);
            Usage = FileInfo.DirectoryName.Replace(PathManager.InputImagesPath.FullName, string.Empty).TrimStart(new[] { '/', '\\' });
            IsCoded = isCoded;
        }

        public bool IsCoded { get; set; }

        public bool IsPacked { get; set; }
        public bool IsPVREnabled { get; set; }
        public bool IsPOT { get; set; }
        public bool IsSquare { get; set; }


        public string Usage { get; private set; }

        public FileInfo OriginalFileInfo { get; private set; }
        public FileInfo FileInfo { get; private set; }
        public string ResourceName { get; private set; }
        public uint Order { get; set; }
        private string mMd5;

        public string Md5
        {
            get
            {
                if (mMd5 == null)
                {
                    var buffer = File.ReadAllBytes(FileInfo.FullName);
                    MD5 md5 = new MD5CryptoServiceProvider();
                    var output = md5.ComputeHash(buffer);
                    mMd5 = BitConverter.ToString(output).Replace("-", string.Empty);
                }
                return mMd5;
            }
            set { mMd5 = value; }
        }

        public void UpdateSubPublishGroup(PublishGroup publishGroup)
        {
            if (PublishGroup == null || publishGroup == null)
            {
                PublishGroup = publishGroup;
            }
            else
            {
                if (PublishGroup.SubGroupName != publishGroup.GroupName) //when assign one file to multi group, it means to be a "Common" group.
                {
                    //Logger.LogAllLine("Merge to group Common from {0},{1}", mPublishGroup.GroupName, value.GroupName);
                    if (!PublishGroup.SubGroupName.Contains(publishGroup.GroupName))
                    {
                        PublishGroup.SubGroupName += publishGroup.GroupName;
                    }
                }

                //Don't change path
                //PublishGroup.PublishInfo.Merge(publishGroup.PublishInfo);
            }
        }

        public PublishGroup PublishGroup { get; set; }
       
        public bool EnablePacking { get; set; }

        /// <summary>
        /// Used when self are changed
        /// </summary>
        /// <param name="filePath"></param>
        public void UpdateMd5(string filePath)
        {
            var buffer = File.ReadAllBytes(filePath);
            MD5 md5 = new MD5CryptoServiceProvider();
            var output = md5.ComputeHash(buffer);
            mMd5 = BitConverter.ToString(output).Replace("-", string.Empty);
        }

        public static string GetResourceName(string filePath)
        {
            filePath= Path.GetFileName(filePath);

            int index = filePath.IndexOf('-');
            if (index < 0)
            {
                return filePath;
            }

            int index2 = filePath.IndexOf('.');
            if (index2 < 0)
            {
                return filePath.Remove(index);
            }
            return filePath.Remove(index, index2 - index);
        }

        public static uint GetResourceOrder(string resPath)
        {
            var versionNames = Enum.GetNames(typeof(PublishVersions));
            var deviceNames = Enum.GetNames(typeof(PublishDevices));
            var languageNames = Enum.GetNames(typeof(PublishLanguages));
            resPath = versionNames.Aggregate(resPath,
                                             (current, versionName) => current.Replace("-" + versionName, String.Empty));
            resPath = deviceNames.Aggregate(resPath,
                                            (current, deviceName) => current.Replace("-" + deviceName, String.Empty));
            resPath = languageNames.Aggregate(resPath,
                                              (current, languageName) =>
                                              current.Replace("-" + languageName, String.Empty));

            int preIndex = resPath.IndexOf('-');
            if (preIndex >= 0)
            {
                int index = resPath.IndexOf('.');
                string numberStr = resPath.Substring(preIndex + 1, index - preIndex - 1);
                return Convert.ToUInt32(numberStr);
            }
            return 0;
        }

        public override int GetHashCode()
        {
            return FileInfo.GetHashCode();
        }

        public override string ToString()
        {
            return string.Format("{0}:{1}", ResourceName, FileInfo);
        }

        public override bool Equals(object obj)
        {
            var file = obj as FileListFile;
            return file != null && FileInfo.Equals(file.FileInfo);
        }

        public void UpdateFileInfo(FileInfo newFileInfo)
        {
            if (OriginalFileInfo==null)
            {
                OriginalFileInfo = FileInfo;
            }
            FileInfo = newFileInfo;
            ResourceName = GetResourceName(FileInfo.Name);
            Order = GetResourceOrder(FileInfo.Name);
            PublishGroup = PublishGroup.GetPublishGroup(FileInfo);
            Usage = FileInfo.DirectoryName.Replace(PathManager.InputImagesPath.FullName, string.Empty).TrimStart(new[] { '/', '\\' });
            Md5 = null;

        }

        public void MakeGuidName()
        {
            var guid= Guid.NewGuid();
            string str=guid.ToString().Replace("-","");
            string newPath = Path.Combine(FileInfo.DirectoryName,str+FileInfo.Extension);
            FileInfo.MoveTo(newPath);
            UpdateFileInfo(new FileInfo(newPath));
            //File.Move();
        }
    }
}