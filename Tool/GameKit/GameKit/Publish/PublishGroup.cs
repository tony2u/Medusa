// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Drawing.Imaging;
using System.IO;
using GameKit.Resource;

namespace GameKit.Publish
{
    public class PublishGroup
    {
        private PublishGroup()
        {
        }

        public string GroupName { get; set; }
        public string SubGroupName { get; set; }

        public string Path { get; set; }

        public PublishInfo PublishInfo { get; set; }

        public override int GetHashCode()
        {
            int result = GroupName.GetHashCode() ^ SubGroupName.GetHashCode() ^ Path.GetHashCode() ^ PublishInfo.GetHashCode();
            return result;
        }

        public override string ToString()
        {
            if (string.IsNullOrEmpty(Path))
            {
                if (!string.IsNullOrEmpty(SubGroupName))
                {
                    return GroupName + System.IO.Path.AltDirectorySeparatorChar + SubGroupName + PublishInfo;
                }
                return GroupName + PublishInfo;
            }
            if (!string.IsNullOrEmpty(SubGroupName))
            {
                return Path + System.IO.Path.AltDirectorySeparatorChar + GroupName + System.IO.Path.AltDirectorySeparatorChar + SubGroupName + PublishInfo;
            }
            return Path + System.IO.Path.AltDirectorySeparatorChar + GroupName + PublishInfo;
        }

        public override bool Equals(object obj)
        {
            var item = obj as PublishGroup;
            bool result = item != null &&
                          (GroupName == item.GroupName && SubGroupName == item.SubGroupName && Path == item.Path && PublishInfo.Equals(item.PublishInfo));
            return result;
        }

        public static PublishGroup GetPublishGroup(FileInfo file)
        {
            var group = new PublishGroup();
            group.GroupName = file.Directory.Name;
            group.SubGroupName = string.Empty;
            group.Path = file.DirectoryName.Replace(PathManager.InputImagesPath.FullName, string.Empty);
            group.Path = group.Path.Replace(PathManager.OutputImagesPath.FullName, string.Empty);
            group.Path = group.Path.TrimStart(new[] { '/', '\\' });
            group.PublishInfo = PublishInfo.GetPublishInfo(file);
            return group;
        }

        public static PublishGroup GetPublishGroup(string groupName, string path)
        {
            var group = new PublishGroup();
            group.GroupName = groupName;
            group.Path = path;
            group.PublishInfo = PublishInfo.GetPublishInfo(new FileInfo(groupName));
            return group;
        }

        public string GenerateNewFileName(DirectoryInfo path, uint order)
        {
            string fileDir = String.Format("{0}/{1}", path, Path);
            if (!Directory.Exists(fileDir))
            {
                Directory.CreateDirectory(fileDir);
            }

            string groupName = !string.IsNullOrEmpty(SubGroupName) ? SubGroupName : GroupName;
            if (order != 0)
            {
                fileDir += String.Format("/{0}{1}{2}.{3}", groupName, order,PublishInfo,
                                         ImageFormat.Png.ToString().ToLower());
            }
            else
            {
                fileDir += String.Format("/{0}{1}.{2}", groupName, PublishInfo,
                                         ImageFormat.Png.ToString().ToLower());
            }

            return fileDir;
        }
    }
}