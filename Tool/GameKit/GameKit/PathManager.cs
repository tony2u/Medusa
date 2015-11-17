// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace GameKit
{
    public static class PathManager
    {
        public static DirectoryInfo RootPath=new DirectoryInfo("E:\\");

        public static DirectoryInfo DataPath
        {
            get { return new DirectoryInfo(Path.Combine(RootPath.FullName,"Data")); }
        }

        public static DirectoryInfo DevPath
        {
            get { return new DirectoryInfo(Path.Combine(RootPath.FullName, "Project")); }
        }

        public static DirectoryInfo InputPath
        {
            get { return new DirectoryInfo(Path.Combine(DataPath.FullName,"Art")); }
        }


        public static DirectoryInfo TempPath
        {
            get { return new DirectoryInfo(Path.Combine(DataPath.FullName, "Temp")); }
        }

        public static DirectoryInfo OutputPath
        {
            get { return new DirectoryInfo(Path.Combine(DataPath.FullName,"Export")); }
        }

        public static DirectoryInfo UpdateServerPath
        {
            get { return new DirectoryInfo(Path.Combine(DataPath.FullName,"Server")); }
        }

        public static DirectoryInfo ProjectPath
        {
            get { return new DirectoryInfo(Path.Combine(DevPath.FullName, "Client/Test")); }
        }

        public static DirectoryInfo GameServerPath
        {
            get { return new DirectoryInfo(Path.Combine(DevPath.FullName, "Server/Test")); }
        }

        public static DirectoryInfo AndroidProjectPath
        {
            get { return new DirectoryInfo(Path.Combine(DevPath.FullName, "Client/Test/android")); }
        }

        public static string ResDirectoryName = "Res";

        public static string AnimationDirectoryName = "Animation";
        public static string AnimationEffectDirectoryName = "Effect";
        public static string AnimationRoleDirectoryName = "Role";
        public static string AnimationMonsterDirectoryName = "Monster";
        public static string AnimationSceneDirectoryName = "Scene";
        public static string AnimationMapDirectoryName = "Map";



        public static string ImagesDirectoryName = "Images";
        public static string AudioDirectoryName = "Audio";
        public static string ConfigDirectoryName = "Config";
        public static string EditorDirectoryName = "Editor";
        public static string FontDirectoryName = "Font";
        public static string ScriptDirectoryName = "Script";
        public static string FlashDirectoryName = "Flash";

        public static string OtherDirectoryName = "Other";
        public static string MissionDirectoryName = "Battle/Mission";
        public static string HeroDirectoryName = "Battle/Role/Hero";
        public static string MonsterDirectoryName = "Battle/Role/Monster";
        public static string SkillDirectoryName = "Battle/Skill";
        public static string BufferDirectoryName = "Battle/Buffer/Buffers";








        public static string UIDirectoryName = "UI";
        public static string FileListFileName = "FileList.bin";
        public static string FileSystemFileName = "FileSystem.bin";
        public static string ServerConfigFileName = "Server.bin";

        public static string FileCacheFileName = "FileCache.bin";


        public static string StringTableInputName = "StringTable.xlsx";

        public static string DataTableInputName = "Data.xlsx";
        public static string ServerConfigInputName = "ServerConfig.xlsx";

        

        public static string PaperConfigInputName = "PaperConfig.cs";
        public static string ServerGameConfigInputName = "ServerGameConfig.cs";



        public static string PVEConfigTableName = "PVE$";
        public static string MissionConfigTableName = "Mission$";
        public static string HeroConfigTableName = "Hero$";
        public static string PetConfigTableName = "Pet$";

        public static string MonsterConfigTableName = "Monster$";
        public static string EquipConfigTableName = "Equip$";
        public static string RuneConfigTableName = "Rune$";
        public static string RuneShopConfigTableName = "RuneShop$";
        public static string PVPLeaderboardScoreConfigTableName = "PVPLeaderboardScore$";
        public static string BloodLeaderboardConfigTableName = "BloodLeaderboard$";




        public static string BufferConfigTableName = "Buffer$";
        public static string SkillConfigTableName = "Skill$";
        public static string SkillEffectConfigTableName = "SkillEffect$";
        public static string AuraConfigTableName = "Aura$";
        public static string NPCConfigTableName = "NPC$";

        public static string LoveConfigTableName = "Love$";
        public static string ServerConfigTableName = "Server$";
        public static string ServerListTableName = "ServerList$";


        public static string FeatureConfigTableName = "Feature$";
        public static string PlayerLevelConfigTableName = "PlayerLevel$";
        public static string HeroLevelConfigTableName = "HeroLevel$";
        public static string PetLevelConfigTableName = "PetLevel$";
        public static string EquipLevelConfigTableName = "EquipLevel$";
        public static string RuneLevelConfigTableName = "RuneLevel$";


        public static string SkillLevelConfigTableName = "SkillLevel$";

        public static string VIPConfigTableName = "VIP$";
        public static string ItemConfigTableName = "Item$";




        public static string PVEConfigOutputName = "PVEConfig.bin";
        public static string MissionConfigOutputName = "MissionConfig.bin";
        public static string HeroConfigOutputName = "HeroConfig.bin";
        public static string PetConfigOutputName = "PetConfig.bin";
        public static string MonsterConfigOutputName = "MonsterConfig.bin";
        public static string EquipConfigOutputName = "EquipConfig.bin";
        public static string RuneConfigOutputName = "RuneConfig.bin";
        public static string RuneShopConfigOutputName = "RuneShopConfig.bin";
        public static string PVPLeaderboardScoreConfigOutputName = "PVPLeaderboardScoreConfig.bin";
        public static string BloodLeaderboardConfigOutputName = "BloodLeaderboardConfig.bin";


        

        public static string BufferConfigOutputName = "BufferConfig.bin";
        public static string SkillConfigOutputName = "SkillConfig.bin";
        public static string SkillEffectConfigOutputName = "SkillEffectConfig.bin";
        public static string AuraConfigOutputName = "AuraConfig.bin";
        public static string NPCConfigOutputName = "NPCConfig.bin";

        public static string LoveConfigOutputName = "LoveConfig.bin";

        public static string PaperConfigOutputName = "PaperConfig.bin";
        public static string ServerConfigOutputName = "ServerConfig.bin";
        public static string ServerListOutputName = "ServerList.bin";


        public static string FeatureConfigOutputName = "FeatureConfig.bin";
        public static string PlayerLevelConfigOutputName = "PlayerLevelConfig.bin";
        public static string HeroLevelConfigOutputName = "HeroLevelConfig.bin";
        public static string PetLevelConfigOutputName = "PetLevelConfig.bin";
        public static string EquipLevelConfigOutputName = "EquipLevelConfig.bin";
        public static string RuneLevelConfigOutputName = "RuneLevelConfig.bin";


        public static string SkillLevelConfigOutputName = "SkillLevelConfig.bin";

        public static string VIPConfigOutputName = "VIPConfig.bin";
        public static string ItemConfigOutputName = "ItemConfig.bin";



        public static string AndroidAssetDirectoryName = "assets";
        public static string AndroidMKDirectoryName = "jni/Android.mk";


        public static FileInfo TempFileCachePath
        {
            get { return new FileInfo(Path.Combine(TempPath.FullName, FileCacheFileName)); }
        }

       

        public static FileInfo TempFileSystemPath
        {
            get { return new FileInfo(Path.Combine(TempPath.FullName, FileSystemFileName)); }
        }

        public static DirectoryInfo AndroidAssetPath
        {
            get { return AndroidProjectPath.CreateSubdirectory(AndroidAssetDirectoryName); }
        }

        public static FileInfo AndroidMKPath
        {
            get { return new FileInfo(Path.Combine(AndroidProjectPath.FullName, AndroidMKDirectoryName)); }
        }

        public static DirectoryInfo InputAudioPath
        {
            get { return InputPath.CreateSubdirectory(AudioDirectoryName); }
        }

        public static DirectoryInfo InputImagesPath
        {
            get { return InputPath.CreateSubdirectory(ImagesDirectoryName); }
        }

        public static DirectoryInfo InputImagesUIPath
        {
            get { return InputImagesPath.CreateSubdirectory(UIDirectoryName); }
        }

        public static DirectoryInfo InputConfigPath
        {
            get { return InputPath.CreateSubdirectory(ConfigDirectoryName); }
        }

        public static DirectoryInfo InputFlashPath
        {
            get { return InputPath.CreateSubdirectory(FlashDirectoryName); }
        }

        public static DirectoryInfo InputEditorPath
        {
            get { return InputPath.CreateSubdirectory(EditorDirectoryName); }
        }

        public static DirectoryInfo InputImageOtherPath
        {
            get { return InputImagesPath.CreateSubdirectory(OtherDirectoryName); }
        }

        public static DirectoryInfo InputOtherPath
        {
            get { return InputPath.CreateSubdirectory(OtherDirectoryName); }
        }

        public static DirectoryInfo InputScriptPath
        {
            get { return InputPath.CreateSubdirectory(ScriptDirectoryName); }
        }

        public static DirectoryInfo InputMissionScriptPath
        {
            get { return InputScriptPath.CreateSubdirectory(MissionDirectoryName); }
        }

        public static DirectoryInfo InputHeroScriptPath
        {
            get { return InputScriptPath.CreateSubdirectory(HeroDirectoryName); }
        }

        public static DirectoryInfo InputMonsterScriptPath
        {
            get { return InputScriptPath.CreateSubdirectory(MonsterDirectoryName); }
        }

        public static DirectoryInfo InputBufferScriptPath
        {
            get { return InputScriptPath.CreateSubdirectory(BufferDirectoryName); }
        }

        public static DirectoryInfo InputSkillScriptPath
        {
            get { return InputScriptPath.CreateSubdirectory(SkillDirectoryName); }
        }

        public static DirectoryInfo InputEditorUIPath
        {
            get { return InputEditorPath.CreateSubdirectory(UIDirectoryName); }
        }


        public static DirectoryInfo InputEditorAnmationPath
        {
            get { return InputEditorPath.CreateSubdirectory(AnimationDirectoryName); }
        }

        public static DirectoryInfo InputEditorEffectAnmationPath
        {
            get { return InputEditorAnmationPath.CreateSubdirectory(AnimationEffectDirectoryName); }
        }

        public static DirectoryInfo InputEditorMonsterAnmationPath
        {
            get { return InputEditorAnmationPath.CreateSubdirectory(AnimationMonsterDirectoryName); }
        }
        public static DirectoryInfo InputEditorRoleAnmationPath
        {
            get { return InputEditorAnmationPath.CreateSubdirectory(AnimationRoleDirectoryName); }
        }
        public static DirectoryInfo InputEditorSceneAnmationPath
        {
            get { return InputEditorAnmationPath.CreateSubdirectory(AnimationSceneDirectoryName); }
        }
        public static DirectoryInfo InputEditorMapAnmationPath
        {
            get { return InputEditorAnmationPath.CreateSubdirectory(AnimationMapDirectoryName); }
        }

        public static DirectoryInfo OutputResPath
        {
            get { return OutputPath.CreateSubdirectory(ResDirectoryName); }
        }

        public static DirectoryInfo OutputImagesPath
        {
            get { return OutputResPath.CreateSubdirectory(ImagesDirectoryName); }
        }

        public static DirectoryInfo OutputImagesUIPath
        {
            get { return OutputImagesPath.CreateSubdirectory(UIDirectoryName); }
        }

        public static DirectoryInfo OutputConfigPath
        {
            get { return OutputResPath.CreateSubdirectory(ConfigDirectoryName); }
        }




        public static FileInfo OutputFileListPath
        {
            get { return new FileInfo(Path.Combine(OutputPath.FullName, FileListFileName)); }
        }

        public static FileInfo OutputFileSystemPath
        {
            get { return new FileInfo(Path.Combine(OutputPath.FullName, FileSystemFileName)); }
        }

        public static FileInfo InputConfigStringTablePath
        {
            get { return new FileInfo(Path.Combine(InputConfigPath.FullName, StringTableInputName)); }
        }

        public static FileInfo InputConfigDataTablePath
        {
            get { return new FileInfo(Path.Combine(InputConfigPath.FullName, DataTableInputName)); }
        }

        public static FileInfo InputConfigServerConfigPath
        {
            get { return new FileInfo(Path.Combine(InputConfigPath.FullName, ServerConfigInputName)); }
        }

        public static FileInfo InputConfigPaperConfigPath
        {
            get { return new FileInfo(Path.Combine(InputConfigPath.FullName, PaperConfigInputName)); }
        }

        public static FileInfo InputConfigServerGameConfigPath
        {
            get { return new FileInfo(Path.Combine(InputConfigPath.FullName, ServerGameConfigInputName)); }
        }

        public static FileInfo OutputConfigPVEConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, PVEConfigOutputName)); }
        }
        public static FileInfo OutputConfigMissionConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, MissionConfigOutputName)); }
        }
        public static FileInfo OutputConfigHeroConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, HeroConfigOutputName)); }
        }
        public static FileInfo OutputConfigPetConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, PetConfigOutputName)); }
        }
        public static FileInfo OutputConfigMonsterConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, MonsterConfigOutputName)); }
        }
        public static FileInfo OutputConfigEquipConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, EquipConfigOutputName)); }
        }
        public static FileInfo OutputConfigRuneConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, RuneConfigOutputName)); }
        }
        public static FileInfo OutputConfigRuneShopConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, RuneShopConfigOutputName)); }
        }
        public static FileInfo OutputConfigPVPLeaderboardScoreConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, PVPLeaderboardScoreConfigOutputName)); }
        }
        public static FileInfo OutputConfigBloodLeaderboardConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, BloodLeaderboardConfigOutputName)); }
        }

        public static FileInfo OutputConfigBufferConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, BufferConfigOutputName)); }
        }
        public static FileInfo OutputConfigSkillConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, SkillConfigOutputName)); }
        }
        public static FileInfo OutputConfigSkillEffectConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, SkillEffectConfigOutputName)); }
        }
        public static FileInfo OutputConfigAuraConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, AuraConfigOutputName)); }
        }
        public static FileInfo OutputConfigNPCConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, NPCConfigOutputName)); }
        }

        public static FileInfo OutputConfigLoveConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, LoveConfigOutputName)); }
        }

        public static FileInfo OutputConfigPaperConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, PaperConfigOutputName)); }
        }

        public static FileInfo OutputConfigServerConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, ServerConfigOutputName)); }
        }

        public static FileInfo OutputConfigServerListPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, ServerListOutputName)); }
        }

        public static FileInfo OutputConfigFeatureConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, FeatureConfigOutputName)); }
        }
        public static FileInfo OutputConfigVIPConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, VIPConfigOutputName)); }
        }
        public static FileInfo OutputConfigItemConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, ItemConfigOutputName)); }
        }

        public static FileInfo OutputConfigPlayerLevelConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, PlayerLevelConfigOutputName)); }
        }
        public static FileInfo OutputConfigHeroLevelConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, HeroLevelConfigOutputName)); }
        }
        public static FileInfo OutputConfigPetLevelConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, PetLevelConfigOutputName)); }
        }
        public static FileInfo OutputConfigEquipLevelConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, EquipLevelConfigOutputName)); }
        }
        public static FileInfo OutputConfigRuneLevelConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, RuneLevelConfigOutputName)); }
        }
        public static FileInfo OutputConfigSkillLevelConfigPath
        {
            get { return new FileInfo(Path.Combine(OutputConfigPath.FullName, SkillLevelConfigOutputName)); }
        }

        public static DirectoryInfo UpdateServerOutputPath
        {
            get { return UpdateServerPath.CreateSubdirectory(OutputPath.Name); }
        }

        public static FileInfo UpdateServerConfigPath
        {
            get { return new FileInfo(Path.Combine(UpdateServerPath.FullName, ServerConfigFileName)); }
        }

        public static void PrepareDirectory()
        {
            SystemTool.ClearDirectory(InputEditorAnmationPath);

            SystemTool.ClearDirectory(OutputPath);
            SystemTool.CopyDirectoryTree(InputPath, OutputResPath, new List<string> { FlashDirectoryName });
        }


        public  static bool IsDevAvailable
        {
            get { return DevPath.Exists; }
        }
        private static void ClearResConfigTempFiles()
        {

        }
    }
}