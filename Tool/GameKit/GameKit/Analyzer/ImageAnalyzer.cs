// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using System.IO;
using System.Linq;
using GameKit.Log;
using GameKit.Packing;
using GameKit.Publish;
using GameKit.Resource;

namespace GameKit.Analyzer
{
    enum ImageUsage
    {
        UI,
        RoleAnimation,
        EffectAnimation,
        Mission,
        Monster,
        Other,
        Storm
    }

    public class ImageAnalyzer : IAnalyzer
    {
        private List<string> mPVREnabledDirectoryNames = new List<string>();
        public static Dictionary<uint, bool> AuraIcons = new Dictionary<uint, bool>();
        public static Dictionary<uint, bool> EquipIcons = new Dictionary<uint, bool>();
        public static Dictionary<uint, bool> HeroIcons = new Dictionary<uint, bool>();
        public static Dictionary<uint, bool> ItemIcons = new Dictionary<uint, bool>();
        public static Dictionary<uint, bool> MonsterIcons = new Dictionary<uint, bool>();
        public static Dictionary<uint, bool> PetIcons = new Dictionary<uint, bool>();
        public static Dictionary<uint, bool> RuneIcons = new Dictionary<uint, bool>();
        public static Dictionary<uint, bool> SkillIcons = new Dictionary<uint, bool>();
        public static Dictionary<string, FileInfo> UIImages = new Dictionary<string, FileInfo>();

        public ImageAnalyzer()
        {
            mPVREnabledDirectoryNames.Add(@"Art\Images\Mission");
            mPVREnabledDirectoryNames.Add(@"Art\Images\MonsterAnimation");
            mPVREnabledDirectoryNames.Add(@"Art\Images\RoleAnimation");
            mPVREnabledDirectoryNames.Add(@"Art\Images\EffectAnimation");
            mPVREnabledDirectoryNames.Add(@"Art\Images\UI\Map\Map1");
        }


        public void PrevProcess()
        {
            AuraIcons.Clear();
            EquipIcons.Clear();
            HeroIcons.Clear();
            ItemIcons.Clear();
            MonsterIcons.Clear();
            PetIcons.Clear();
            RuneIcons.Clear();
            SkillIcons.Clear();
            UIImages.Clear();


            Logger.LogAllLine("Analyze images================>");
            GetImagesRecursively(PathManager.InputImagesPath, "\t");
        }

        public void Analyze()
        {

        }

        public void PostCheck()
        {
            CheckUsage();

            ImagePacker.Pack(PublishTarget.Current);
        }

        private void GetImagesRecursively(DirectoryInfo dirPath, string prefix)
        {
            var files = SystemTool.GetDirectoryFiles(dirPath);
            foreach (var file in files)
            {
                if (!file.Name.EndsWith(".png"))
                {
                    Logger.LogInfoLine("{0}Only accept png image:{1}", prefix, file);
                    continue;
                }
                var imageFile = new ImageFile(file,true,true);
                //Logger.LogInfoLine("{0}File:\t{1}", prefix, file.FullName.Replace(PathManager.InputImagesPath.FullName, string.Empty));
                bool isPacked = !file.Directory.FullName.Contains(PathManager.InputImageOtherPath.FullName);

                bool isPVREnabled = false;
                if (PublishTarget.Current.IsPVR)
                {
                    isPVREnabled = mPVREnabledDirectoryNames.Any(pvrEnabledDirectoryName => file.Directory.FullName.Contains(pvrEnabledDirectoryName));
                }
                //bool isEffectAnimation = file.Directory.FullName.Contains("EffectAnimation");
                //isPacked &= !isEffectAnimation;
                //bool isOptimzed = !isEffectAnimation;
                if (!PublishTarget.Current.IsPack)
                {
                    isPacked = false;
                }

                bool isOptimzed = PublishTarget.Current.IsOptimzed;
                bool isPOT = PublishTarget.Current.IsPOT;
                bool isSquare = PublishTarget.Current.IsSquare;
                if (isPVREnabled)
                {
                    isPOT = true;
                    isSquare = true;
                }

                ImagePacker.AddImage(imageFile, PublishTarget.Current, isPacked, isOptimzed, isPVREnabled, isPOT, isSquare);
                FilterImage(file);
            }
        }

        public void FilterImage(FileInfo info)
        {
            string dirName = info.Directory.Name;
            uint id = FileListFile.GetResourceOrder(info.Name);
            var resourceName = FileListFile.GetResourceName(info.Name);
            resourceName = resourceName.Replace(".png", string.Empty);

            if (info.FullName.Contains("Icon") && info.Directory.FullName.Contains("Art\\Images\\Other"))
            {
                if (dirName == resourceName)
                {
                    var icons = GetIconDict(dirName);
                    if (icons != null)
                    {
                        if (!icons.ContainsKey(id))
                        {
                            icons.Add(id, false);
                        }
                    }
                }
            }
            else if (info.Directory.FullName.Contains("Art\\Images\\UI"))
            {
                if (!UIImages.ContainsKey(info.Name))
                {
                    UIImages.Add(info.Name, info);
                }
            }


        }

        private static Dictionary<uint, bool> GetIconDict(string iconName)
        {
            switch (iconName)
            {
                case "AuraIcon":
                    return AuraIcons;
                case "EquipIcon":
                    return EquipIcons;
                case "HeroIcon":
                    return HeroIcons;
                case "ItemIcon":
                    return ItemIcons;
                case "MonsterIcon":
                    return MonsterIcons;
                case "PetIcon":
                    return PetIcons;
                case "RuneIcon":
                    return RuneIcons;
                case "SkillIcon":
                    return SkillIcons;
            }
            return null;
        }

        public static bool UseUIImage(string name)
        {
            if (UIImages.ContainsKey(name))
            {
                UIImages[name] = null;
                return true;
            }
            return false;

        }
        public static void UseIcon(string iconName, uint id)
        {
            var icons = GetIconDict(iconName);
            if (icons != null)
            {
                if (!icons.ContainsKey(id))
                {
                    Logger.LogErrorLine("Cannot find {0}:{1}", iconName, id);
                }
                else
                {
                    icons[id] = true;
                }
            }
        }

        public static void CheckUsage(string iconName)
        {
            var icons = GetIconDict(iconName);
            if (icons != null)
            {
                foreach (var auraIcon in AuraIcons)
                {
                    if (!auraIcon.Value)
                    {
                        Logger.LogErrorLine("{0}-{1}.png not Used!", iconName, auraIcon.Key);
                    }
                }
            }
        }

        public void CheckUsage()
        {
            CheckUsage("HeroIcon");
            CheckUsage("EquipIcon");
            CheckUsage("HeroIcon");
            CheckUsage("ItemIcon");
            CheckUsage("MonsterIcon");
            CheckUsage("PetIcon");
            CheckUsage("RuneIcon");
            CheckUsage("SkillIcon");


            foreach (var uiImage in UIImages)
            {
                if (uiImage.Value!=null)
                {
                    string str = uiImage.Value.FullName;
                    str=str.Replace(PathManager.InputImagesPath.FullName, string.Empty);
                    str=str.Replace("\\UI\\", string.Empty);
                    Logger.LogErrorLine("\tUI image:{0} not used.", str);
                }
            }

            //foreach (var uiImage in ImagePacker.Images)
            //{
            //    if (!uiImage.Value)
            //    {
            //        Logger.LogErrorLine("\tUI image:{0} not used.", uiImage.Key.FileInfo.Name);
            //    }
            //}
        }


        private void CopyImage(ImageFile imageFile)
        {

            /*
            var packageInfo = PackingInfo.GetPackingInfo(imageFile.OriginalFile.FileInfo.FullName);
            if (packageInfo.IsPackage(PublishTarget.Current))
            {
                string tempFilePath = imageFile.OriginalFile.FileInfo.FullName;
                tempFilePath = tempFilePath.Replace(PathManager.InputPath,
                                                    PathManager.TempPath);

                imageFile.ResultImage.Save(tempFilePath);

                ResourceMapGenerator.AddFileAndTag(imageFile, PublishTarget.Current);
            }
             */
        }
    }
}