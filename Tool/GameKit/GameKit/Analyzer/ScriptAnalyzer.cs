// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using System.IO;
using GameKit.Log;

using GameKit.Publish;
using GameKit.Resource;
using Medusa.CoreProto;
using ProtoBuf;

namespace GameKit.Analyzer
{
    public class ScriptAnalyzer : IAnalyzer
    {
        public static Dictionary<string, bool> MissionScripts = new Dictionary<string, bool>();
        public static Dictionary<string, bool> HeroScripts = new Dictionary<string, bool>();
        public static Dictionary<string, bool> MonsterScripts = new Dictionary<string, bool>();
        public static Dictionary<string, bool> SkillScripts = new Dictionary<string, bool>();
        public static Dictionary<string, bool> BufferScripts = new Dictionary<string, bool>();


        public void PrevProcess()
        {

        }

        public void Analyze()
        {
            Logger.LogAllLine("Analyze Scripts================>");
            MissionScripts.Clear();
            HeroScripts.Clear();
            MonsterScripts.Clear();
            SkillScripts.Clear();
            BufferScripts.Clear();


            {
                var files = SystemTool.GetDirectoryFiles(PathManager.InputMissionScriptPath);
                foreach (var scriptFile in files)
                {
                    MissionScripts.Add(scriptFile.Name, false);
                }

            }

            {
                var files = SystemTool.GetDirectoryFiles(PathManager.InputHeroScriptPath);
                foreach (var scriptFile in files)
                {
                    HeroScripts.Add(scriptFile.Name, false);
                }

            }

            {
                var files = SystemTool.GetDirectoryFiles(PathManager.InputMonsterScriptPath);
                foreach (var scriptFile in files)
                {
                    MonsterScripts.Add(scriptFile.Name, false);
                }

            }

            {
                var files = SystemTool.GetDirectoryFiles(PathManager.InputSkillScriptPath);
                foreach (var scriptFile in files)
                {
                    SkillScripts.Add(scriptFile.Name, false);
                }

            }

            {
                var files = SystemTool.GetDirectoryFiles(PathManager.InputBufferScriptPath);
                foreach (var scriptFile in files)
                {
                    BufferScripts.Add(scriptFile.Name, false);
                }

            }

            //copy all scripts
            {
                var files = SystemTool.GetDirectoryFiles(PathManager.InputScriptPath);
                foreach (var scriptFile in files)
                {
                    var resourceFile = new FileListFile(scriptFile,true,true);
                    FileSystemGenerator.CopyFileToOutput(resourceFile);
                }

            }
        }

        public void PostCheck()
        {

        }
    }
}