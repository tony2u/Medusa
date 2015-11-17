// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GameKit.Common;
using GameKit.Log;
using GameKit.Publish;
using GameKit.Resource;

namespace GameKit.Packing
{
    public static class ImagePacker
    {
        public static Dictionary<PublishGroup, MySortedList<ImageFile>> ImageGroups = new Dictionary<PublishGroup, MySortedList<ImageFile>>();
        public static Dictionary<ImageFile, bool> Images { get; private set; }
        public static Dictionary<string, ImageFile> ImageFilePathDict { get; private set; }
        public static Dictionary<string, ImageFile> ImageFileNameDict { get; private set; }
        



        static ImagePacker()
        {
            Images=new Dictionary<ImageFile, bool>();
            ImageFilePathDict = new Dictionary<string, ImageFile>();
            ImageFileNameDict = new Dictionary<string, ImageFile>();
        }

        public static event Action<int> OptimzeProgressEvent;
        public static event Action<int> PackingProgressEvent;

        private static void OnPackingProgressEvent(int obj)
        {
            Action<int> handler = PackingProgressEvent;
            if (handler != null) handler(obj);
        }


        private static void OnOptimzeProgressEvent(int obj)
        {
            Action<int> handler = OptimzeProgressEvent;
            if (handler != null) handler(obj);
        }

        public static void Clear()
        {
            ImageGroups.Clear();
            Images.Clear();
            ImageFilePathDict.Clear();
            ImageFileNameDict.Clear();
        }

        public static ImageFile FindImage(string filePath)
        {
            ImageFile result;
            ImageFileNameDict.TryGetValue(filePath, out result);
            return result;
        }

        public static void AddImage(ImageFile imageFile, PublishTarget target,bool isPacked=true,bool isOptimzed=true,bool isPVREnabled=false,bool isPOT=false,bool isSquare=false)
        {
            if (!Images.ContainsKey(imageFile) && !ImageFilePathDict.ContainsKey(imageFile.FileInfo.FullName) && !ImageFileNameDict.ContainsKey(imageFile.FileInfo.Name))
            {
                Images.Add(imageFile, false);
                ImageFilePathDict.Add(imageFile.FileInfo.FullName,imageFile);
                ImageFileNameDict.Add(imageFile.FileInfo.Name, imageFile);
                imageFile.IsPacked = isPacked;
                imageFile.IsOptimzed = isOptimzed;
                imageFile.IsPVREnabled = isPVREnabled;
                imageFile.IsPOT = isPOT;
                imageFile.IsSquare = isSquare;
            }
            else
            {
                Logger.LogErrorLine("\tDuplicate File name: {0}\tVS\t{1}", imageFile,
                                    Images[imageFile]);
            }

            if (imageFile.PublishGroup != null && !imageFile.PublishGroup.PublishInfo.IsPublish(target))
            {
                //Logger.LogInfoLine("DON'T pack {0}", imageFile.FileInfo.Name);
                return;
            }

            if (!isPacked)
            {
                //Logger.LogInfoLine("DON'T pack {0}", imageFile.FileInfo.Name);
                return;
            }

            MySortedList<ImageFile> groupFiles;
            if (!ImageGroups.TryGetValue(imageFile.PublishGroup, out groupFiles))
            {
                groupFiles = new MySortedList<ImageFile>();
                ImageGroups.Add(imageFile.PublishGroup, groupFiles);
            }
            groupFiles.Add(imageFile);
        }

        public static void RemoveImageFromGroup(ImageFile imageFile)
        {
            MySortedList<ImageFile> groupFiles;
            if (ImageGroups.TryGetValue(imageFile.PublishGroup, out groupFiles))
            {
                groupFiles.Remove(imageFile);
            }
        }

        private static void Optimze()
        {
            Logger.LogInfoLine("Optimze Images:");
            
            foreach (var imageGroup in ImageGroups)
            {
                //Parallel.ForEach(imageGroup.Value, imageFile =>
                //{
                //    imageFile.Optimze();
                //    //Logger.LogInfoLine("\t{0}", imageFile);
                //    OnOptimzeProgressEvent(1);
                //});

                foreach (var imageFile in imageGroup.Value)
                {
                    imageFile.Optimze();
                    Logger.LogInfoLine("\t{0}", imageFile);
                    OnOptimzeProgressEvent(1);
                }
            }
            
        }

        public static void Pack(PublishTarget target)
        {
            if (target.IsOptimzed)
            {
                Optimze();
            }


            Logger.LogInfoLine("Packing:");
            var merger = new ImageMerger();
            foreach (var imageGroup in ImageGroups)
            {
                if (imageGroup.Value.Count>1||PublishTarget.Current.IsPVR)
                {
                    var resultImages = merger.Generate(imageGroup.Key, imageGroup.Value);
                    foreach (var resultImage in resultImages)
                    {
                        resultImage.Key.Save();
                        resultImage.Key.TryConvertSelfToPVR();

                        uint id=FileSystemGenerator.AddFileAndTag(resultImage.Key);
                        if (id!=uint.MaxValue)
                        {
                            foreach (var subImage in resultImage.Value.UsedImages)
                            {
                                FileSystemGenerator.AddImageTagItem(subImage,id);
                            }
                        }
                        
                    }
                }
                else
                {
                    if (imageGroup.Value.Count>0)
                    {
                        imageGroup.Value[0].IsPacked = false;
                    }
                    //FileSystemGenerator.AddFileAndTag(imageGroup.Value[0]);
                    
                }
               
                OnPackingProgressEvent(1);
            }


            foreach (var image in Images)
            {
                if (!image.Key.IsPacked)
                {
                    FileSystemGenerator.CopyFileToOutput(image.Key);
                }
                else
                {
                    if (!PublishTarget.Current.IsPack)
                    {
                        Logger.LogErrorLine("Lose file:{0}",image.Key.FileInfo.FullName);
                    }

                }
            }
        }

        public static void ShrinkUIMerge()
        {
            
            /*
            var allMergeImageNames = new Dictionary<string, ImageFile>();
            var duplicateMergeImageNames = new Dictionary<string, ImageFile>();
            Dictionary<string, ImageFile> commonMergeImageNames;

            var uiMerges =
                MergeImageNames.Where(mergeImageName => mergeImageName.Key.Path == PathManager.UIDirectory)
                               .ToDictionary(mergeImageName => mergeImageName.Key,
                                             mergeImageName => mergeImageName.Value);

            var commonMergeItem = PublishGroup.GetPackingGroup("Common", PathManager.UIDirectory);

            if (!MergeImageNames.ContainsKey(commonMergeItem))
            {
                commonMergeImageNames = new Dictionary<string, ImageFile>();
            }
            else
            {
                commonMergeImageNames = MergeImageNames[commonMergeItem];
                MergeImageNames.Remove(commonMergeItem);
            }

            //remove duplicate files in common
            foreach (var uiMerge in uiMerges)
            {
                foreach (var commonMergeImageName in commonMergeImageNames)
                {
                    if (uiMerge.Value.ContainsKey(commonMergeImageName.Key))
                    {
                        uiMerge.Value.Remove(commonMergeImageName.Key);
                    }
                }
            }


            //remove duplicate files in each other
            foreach (var mergeImageName in uiMerges)
            {
                foreach (var imageFile in mergeImageName.Value)
                {
                    if (!allMergeImageNames.ContainsKey(imageFile.Key))
                    {
                        allMergeImageNames.Add(imageFile.Key, imageFile.Value);
                    }
                    else
                    {
                        if (!duplicateMergeImageNames.ContainsKey(imageFile.Key))
                        {
                            duplicateMergeImageNames.Add(imageFile.Key, imageFile.Value);
                        }
                    }
                }
            }

            foreach (var duplicateMergeImageName in duplicateMergeImageNames)
            {
                foreach (var mergeImageName in MergeImageNames)
                {
                    mergeImageName.Value.Remove(duplicateMergeImageName.Key);
                }

                commonMergeImageNames.Add(duplicateMergeImageName.Key, duplicateMergeImageName.Value);
            }

            if (commonMergeImageNames.Count > 0)
            {
                MergeImageNames.Add(commonMergeItem, commonMergeImageNames);
            }
             * 
             */
        }
    }
}
