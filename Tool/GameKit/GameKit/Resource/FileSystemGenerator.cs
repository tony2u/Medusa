// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using System.IO;
using System.Linq;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using Medusa.CoreProto;
using ProtoBuf;

namespace GameKit.Resource
{
    public static class FileSystemGenerator
    {
        public static readonly Dictionary<PublishInfo, FileSystemTagItem> TagItems = new Dictionary<PublishInfo, FileSystemTagItem>();
        public static FileSystem FileSystem = new FileSystem();

        public static FileListGenerator FileListGenerator = new FileListGenerator();

        public static void Clear()
        {
            TagItems.Clear();
            FileSystem = new FileSystem();
            FileListGenerator.Clear();

        }

        public static void CopyFileToOutput(ImageFile imageFile)
        {
            string tempFilePath = imageFile.FileInfo.FullName;
            tempFilePath = tempFilePath.Replace(PathManager.InputPath.FullName,
                                                PathManager.OutputResPath.FullName);

            if (imageFile.IsOptimzed && imageFile.ResultImage != null)
            {
                imageFile.ResultImage.Save(tempFilePath);
            }
            else
            {
                //SystemTool.FastCopy(imageFile.FileInfo.FullName, tempFilePath);
                imageFile.FileInfo.CopyTo(tempFilePath);
            }

            if (imageFile.IsPVREnabled)
            {
                tempFilePath = Resource.ImageFile.TryConvertToPVR(new FileInfo(tempFilePath), imageFile.Md5);
                imageFile.UpdateFileInfo(new FileInfo(tempFilePath));
                AddFileAndTag(imageFile);
            }
            else
            {
                FileListFile fileListFile=new FileListFile(new FileInfo(tempFilePath),imageFile.EnablePacking,imageFile.IsCoded);
                AddFileAndTag(fileListFile);
            }
           

        }


        public static void CopyFileToOutput(FileListFile imageFile)
        {
            string tempFilePath = imageFile.FileInfo.FullName;
            tempFilePath = tempFilePath.Replace(PathManager.InputPath.FullName,
                                                PathManager.OutputResPath.FullName);

            FileInfo tempFileInfo = new FileInfo(tempFilePath);
            if (!tempFileInfo.Directory.Exists)
            {
                tempFileInfo.Directory.Create();
            }

            //if (imageFile.IsCoded)
            //{
            //    using (var file = imageFile.FileInfo.OpenRead())
            //    {
            //        var resultStream=mFileListGenerator.Code(file);
            //        StreamWriter sw=new StreamWriter(tempFilePath);
            //        resultStream.CopyTo(sw.BaseStream);
            //        sw.Close();

            //    }
            //    //imageFile.FileInfo.CopyTo(tempFilePath, true);
            //}
            //else
            //{
            //    imageFile.FileInfo.CopyTo(tempFilePath, true);
            //}
            imageFile.FileInfo.CopyTo(tempFilePath, true);

            var resourceFile = new FileListFile(new FileInfo(tempFilePath), imageFile.EnablePacking, imageFile.IsCoded);
            AddFileAndTag(resourceFile);

        }

        public static uint AddFileAndTag(FileListFile file)
        {
            uint id = AddFile(file);
            if (id != uint.MaxValue)
            {
                AddFileTagItem(file, id);
            }
            return id;
        }


        public static uint AddFileAndTag(ImageFile file)
        {
            uint id = AddFile(file);
            if (id != uint.MaxValue)
            {
                AddFileTagItem(file, id);
            }
            return id;
        }

        public static uint AddFile(FileListFile file)
        {
            return FileListGenerator.AddFile(file);
        }

        public static void AddImageTagItem(ImageFile imageFile, uint fileId)
        {
            var orderItem = AddFileTagItem(imageFile, fileId);

            if (orderItem != null)
            {
                if (imageFile.TextureRect.HasValue)
                {
                    orderItem.TextureRect = new RectU
                    {
                        Origin = new PointU
                        {
                            X = (uint)imageFile.TextureRect.Value.X,
                            Y = (uint)imageFile.TextureRect.Value.Y
                        },
                        Size = new SizeU
                        {
                            Width = (uint)imageFile.TextureRect.Value.Width,
                            Height = (uint)imageFile.TextureRect.Value.Height
                        }
                    };
                }

                if (imageFile.Offset.HasValue)
                {
                    orderItem.Offset = new PointU
                    {
                        X = (uint)imageFile.Offset.Value.X,
                        Y = (uint)imageFile.Offset.Value.Y
                    };

                    if (!imageFile.OriginalSize.IsEmpty)
                    {
                        orderItem.OriginalSize = new SizeU
                        {
                            Width = (uint)imageFile.OriginalSize.Width,
                            Height = (uint)imageFile.OriginalSize.Height
                        };
                    }
                }
            }
        }


        private static FileSystemOrderItem AddFileTagItem(FileListFile originalFile, uint fileId)
        {
            //find tag item
            var publishInfo = PublishInfo.GetPublishInfo(originalFile.FileInfo);
            FileSystemTagItem tagItem;
            if (TagItems.ContainsKey(publishInfo))
            {
                tagItem = TagItems[publishInfo];
            }
            else
            {
                tagItem = new FileSystemTagItem
                {
                    Tag = publishInfo.Tag
                };
                TagItems.Add(publishInfo, tagItem);
                FileSystem.TagItems.Add(tagItem);
            }

            //find name item
            string resourceName = originalFile.ResourceName;

            if (tagItem != null)
            {
                var nameItems = tagItem.NameItems;
                var nameItem = nameItems.FirstOrDefault(resourceMapNameItem => resourceMapNameItem.Name == resourceName);

                if (nameItem == null)
                {
                    nameItem = new FileSystemNameItem { Name = resourceName };
                    nameItems.Add(nameItem);
                }

                //find order item
                uint order = originalFile.Order;
                var orderItems = nameItem.OrderItems;
                var orderItem = orderItems.FirstOrDefault(resourceMapOrderItem => resourceMapOrderItem.Order == order);
                if (orderItem == null)
                {
                    orderItem = new FileSystemOrderItem
                    {
                        Order = order,
                        FileId = fileId
                    };
                    orderItems.Add(orderItem);
                    return orderItem;
                }
                else
                {
                    var prevItem = FileListGenerator.GetFileName(orderItem.FileId);
                    Logger.LogAll("\tDuplicate tag item:{0} in {1} & {2}\r\n", resourceName,originalFile, prevItem);
                }
            }
            return null;
        }

        public static void Save()
        {
            //save
            using (var file = File.Open(PathManager.OutputFileSystemPath.FullName, FileMode.Create, FileAccess.ReadWrite))
            {
                Serializer.Serialize(file, FileSystem);
            }
            //FileListGenerator.CodeFile(PathManager.OutputFileSystemPath);
            AddFile(new FileListFile(PathManager.OutputFileSystemPath, true, true));

            Logger.LogAllLine("Generate:\t{0}", PathManager.OutputFileSystemPath.FullName);

            //add resource map to file system also

            FileListGenerator.Save();




            /*
            ListItems.Clear();
            TagItems.Clear();
            ResourceMap.fileItems.Clear();
            ResourceMap.tagItems.Clear();

            ResourceMap.version = PublishTarget.Current.ResourceMapVersion;

            Logger.LogAllLine("Generate resource map");

            //get file list
            Logger.LogAllLine("Generate file list");
            ResourceMap.fileItems.AddRange(ResourceFileMap.ResourceMapFileList.Values);
            Logger.LogAllLine("Generate tag list");

            ResourceMap.tagItems.AddRange(ResourceFileMap.TagItems.Values);

            string mapOutputPath = PathManager.TempPath + PathManager.ResourceMapFileName;
            using (var file = File.Open(mapOutputPath, FileMode.Create, FileAccess.ReadWrite))
            {
                Serializer.Serialize(file, ResourceMap);
            }
            Logger.LogAllLine("Generate:\t{0}", mapOutputPath);


            //CopyResource("\t");
             * */
        }

        public static void Print()
        {
            FileListGenerator.PrintDirectory(string.Empty);

            Logger.LogInfoLine("FileSystem TagList:");
            foreach (var resourceTagItem in FileSystem.TagItems)
            {
                var info = new PublishInfo(resourceTagItem.Tag);
                Logger.LogInfoLine("\t{0}", info);
                foreach (var resourceMapNameItem in resourceTagItem.NameItems)
                {
                    Logger.LogInfoLine("\t\t{0}", resourceMapNameItem.Name);
                    foreach (var resourceMapOrderItem in resourceMapNameItem.OrderItems)
                    {
                        if (resourceMapOrderItem.TextureRect != null && resourceMapOrderItem.Offset != null &&
                            resourceMapOrderItem.OriginalSize != null)
                        {
                            Logger.LogInfoLine("\t\t\tOrder:{0} in {1} ({2},{3})=>({4},{5},{6},{7})+({8},{9})",
                                               resourceMapOrderItem.Order, resourceMapOrderItem.FileId,
                                               resourceMapOrderItem.OriginalSize.Width,
                                               resourceMapOrderItem.OriginalSize.Height,
                                               resourceMapOrderItem.TextureRect.Origin.X,
                                               resourceMapOrderItem.TextureRect.Origin.Y,
                                               resourceMapOrderItem.TextureRect.Size.Width,
                                               resourceMapOrderItem.TextureRect.Size.Height,
                                               resourceMapOrderItem.Offset.X, resourceMapOrderItem.Offset.Y);
                        }
                        else
                        {
                            Logger.LogInfoLine("\t\t\tOrder:{0} in {1}", resourceMapOrderItem.Order,
                                               resourceMapOrderItem.FileId);
                        }
                    }
                }
            }
        }
    }
}