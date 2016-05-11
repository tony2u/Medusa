// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace CodeAnalyzer
{

    public partial class Form1 : Form
    {
        private string mSourcePath;
        private string mProjectPath;
        private string mProjectCorePath;
        private string mProjectExtensionPath;

        private const string mManualBegin = "//MANUAL_BEGIN";
        private const string mManualEnd = "//MANUAL_END";


        private void UpdatePaths(string sourcePath)
        {
            mSourcePath = sourcePath;
            mProjectPath = mSourcePath + @"Medusa\Medusa";
            mProjectCorePath = mSourcePath + @"Medusa\MedusaCore";
            mProjectExtensionPath = mSourcePath + @"Medusa\MedusaExtension";
        }





        public List<string> mIgnoreStrings = new List<string> { "=DefaultCompare<T>", 
            "=DefaultCompare<TKey>", "=false", "=Threading::NoThreadingLockPolicy", "=true",
            "=MEDUSA_CORE_ALLOCATOR_DEFAULT_CHUNK_SIZE", "=DefaultHashCoder<TKey>",
            "=MEDUSA_CORE_ALLOCATOR_MAX_SMALL_OBJECT_SIZE","=MEDUSA_CORE_ALLOCATOR_DEFAULT_OBJECT_ALIGNMENT","=DefaultNewerById<TId,TObject>","= DefaultNewerById<TId, TObject>" };

        public List<string> mTypedefStrings = new List<string>();

        public Form1()
        {
            InitializeComponent();
        }


        private void WriteToFile(string path, string str)
        {
            string old = File.ReadAllText(path);
            string manual=Extract(old, mManualBegin, mManualEnd);
            str += mManualBegin;
            str += manual;
            str += mManualEnd;

            if (old != str)
            {
                File.WriteAllText(path, str);
            }
        }

        public string Extract(string text, string begin, string end)
        {
            if (string.IsNullOrEmpty(text))
            {
                return "\n";
            }

            int index1 = text.IndexOf(begin);
            if (index1 < 0)
            {
                return "\n";
            }


            int index2 = text.IndexOf(end);
            if (index2 < 0 || index2 < index1)
            {
                return "\n";
            }

            return text.Substring(index1 + begin.Length, index2 - index1 - begin.Length);
        }

        public Encoding GetFileEncodeType(string filename)
        {
            using (var fs = new FileStream(filename, FileMode.Open,
                FileAccess.Read))
            {
                using (var br = new BinaryReader(fs))
                {
                    Byte[] buffer = br.ReadBytes(2);
                    if (buffer[0] >= 0xEF)
                    {
                        if (buffer[0] == 0xEF && buffer[1] == 0xBB)
                        {
                            return System.Text.Encoding.UTF8;
                        }
                        else if (buffer[0] == 0xFE && buffer[1] == 0xFF)
                        {
                            return System.Text.Encoding.BigEndianUnicode;
                        }
                        else if (buffer[0] == 0xFF && buffer[1] == 0xFE)
                        {
                            return System.Text.Encoding.Unicode;
                        }
                        else
                        {
                            return System.Text.Encoding.Default;
                        }
                    }
                    else
                    {
                        return System.Text.Encoding.Default;
                    }
                }

            }

        }



        private void RemoveMedusaCoreMedusaNamespace()
        {
            List<string> ignoreFiles = new List<string>();
            ignoreFiles.Add("CommonAssert.h");

            var path = mProjectCorePath + "\\Core";
            var files = GetDirectoryFiles2(path, true);

            foreach (var fileInfo in files)
            {
                if (fileInfo.Name.Contains(".pb"))
                {
                    continue;   //ignore proto files
                }
                if (!ignoreFiles.Contains(fileInfo.Name))
                {

                    var text = File.ReadAllText(fileInfo.FullName);
                    var newText = text.Replace("::Medusa::", string.Empty);
                    newText = newText.Replace("Medusa::", string.Empty);
                    if (text != newText)
                    {
                        var encoding = GetFileEncodeType(fileInfo.FullName);
                        File.WriteAllText(fileInfo.FullName, newText, encoding);
                    }
                }

            }
        }

        private void RemoveMedusaMedusaNamespace()
        {
            var path = mProjectPath;
            var files = GetDirectoryFiles2(path, true);

            foreach (var fileInfo in files)
            {
                if (fileInfo.DirectoryName.Contains("Lib") || fileInfo.DirectoryName.Contains("Content"))
                {
                    continue;//ignore lib file
                }
                if (fileInfo.Name.Contains(".pb"))
                {
                    continue;   //ignore proto files
                }


                var text = File.ReadAllText(fileInfo.FullName);
                var newText = text.Replace("::Medusa::", string.Empty);
                newText = newText.Replace("Medusa::", string.Empty);
                if (text != newText)
                {
                    var encoding = GetFileEncodeType(fileInfo.FullName);
                    File.WriteAllText(fileInfo.FullName, newText, encoding);
                }

            }
        }

        private void RemoveMedusaExtensionMedusaNamespace()
        {
            var path = mProjectExtensionPath;
            var files = GetDirectoryFiles2(path, true);

            foreach (var fileInfo in files)
            {
                if (fileInfo.DirectoryName.Contains("ExtensionLib"))
                {
                    continue;//ignore lib file
                }

                var text = File.ReadAllText(fileInfo.FullName);
                var newText = text.Replace("::Medusa::", string.Empty);
                newText = newText.Replace("Medusa::", string.Empty);
                if (text != newText)
                {
                    var encoding = GetFileEncodeType(fileInfo.FullName);
                    File.WriteAllText(fileInfo.FullName, newText, encoding);
                }

            }
        }

        private void GenerateMedusaCorePreDeclare()
        {
            mTypedefStrings.Clear();

            StringBuilder result = new StringBuilder();

            List<String> ignoreFiles=new List<string>();
            ignoreFiles.Add("TypelistUtility.h");
            ignoreFiles.Add("SirenTraits.h");

            result.AppendLine("#pragma once");
            result.AppendLine("#include \"CorePlatform/CorePlatform.h\"");

            //result.AppendLine("#include \"CorePlatform/Common/CommonMarcos.h\"");
            //result.AppendLine("#include \"CorePlatform/Common/MacroUtility.h\"");

            //result.AppendLine("#pragma warning(disable:4348)		//warning C4348 redefinition of default parameter");



            result.AppendLine("MEDUSA_BEGIN;");
            List<ClassBlock> blocks = new List<ClassBlock>();
            var files = GetDirectoryFiles(mProjectCorePath, true);
            foreach (var fileInfo in files)
            {
                if (fileInfo.Name != "MedusaCorePreDeclares.h" && !ignoreFiles.Contains(fileInfo.Name))
                {
                    blocks.AddRange(ExtractPreDeclare(fileInfo));
                }
            }

            List<ClassBlock> distinctBlocks = new List<ClassBlock>();

            //remove duplicate blocks
            Dictionary<ClassBlock, bool> dupBlocks = new Dictionary<ClassBlock, bool>();
            foreach (var block in blocks)
            {
                if (!dupBlocks.ContainsKey(block))
                {
                    dupBlocks.Add(block, true);
                    distinctBlocks.Add(block);  //keep order
                }
            }

            //group
            SortedDictionary<string, List<ClassBlock>> blockGroups = new SortedDictionary<string, List<ClassBlock>>(new InverseStringComparer());
            foreach (var distinctBlock in distinctBlocks)
            {
                List<ClassBlock> innerBlocks = null;
                if (!blockGroups.TryGetValue(distinctBlock.NameSpace, out innerBlocks))
                {
                    innerBlocks = new List<ClassBlock>();
                    blockGroups.Add(distinctBlock.NameSpace, innerBlocks);
                }

                innerBlocks.Add(distinctBlock);
            }


            //serialize
            foreach (var blockGroup in blockGroups)
            {
                if (blockGroup.Key.Contains("Private")|| blockGroup.Key.Contains("internal")) //ignore private classes
                {
                    continue;
                }

                if (blockGroup.Key != string.Empty)
                {
                    result.AppendFormat("namespace {0}", blockGroup.Key);
                    result.AppendLine();
                    result.AppendLine("{");

                    foreach (var block in blockGroup.Value)
                    {
                        foreach (var l in block.Lines)
                        {
                            result.AppendLine("\t" + l);
                        }
                    }
                    result.AppendLine("}");

                }
                else
                {
                    foreach (var block in blockGroup.Value)
                    {
                        foreach (var l in block.Lines)
                        {
                            result.AppendLine(l);
                        }
                    }
                }
            }

            result.AppendLine("#pragma region typedef");

            foreach (var typedefString in mTypedefStrings)
            {
                result.AppendLine(typedefString);
            }
            result.AppendLine("#pragma endregion typedef");


            result.AppendLine("MEDUSA_END;");


            WriteToFile(mProjectCorePath + @"\MedusaCorePreDeclares.h", result.ToString());

        }

        private void GenerateMedusaExtensionPreDeclare()
        {
            mTypedefStrings.Clear();

            StringBuilder result = new StringBuilder();
            result.AppendLine("#pragma once");
            result.AppendLine("#include \"ExtensionPlatform/ExtensionPlatform.h\"");

            //result.AppendLine("#include \"CorePlatform/Common/CommonMarcos.h\"");
            //result.AppendLine("#include \"CorePlatform/Common/MacroUtility.h\"");

            //result.AppendLine("#pragma warning(disable:4348)		//warning C4348 redefinition of default parameter");



            result.AppendLine("MEDUSA_BEGIN;");
            List<ClassBlock> blocks = new List<ClassBlock>();
            var files = GetDirectoryFiles(mProjectExtensionPath, true);
            foreach (var fileInfo in files)
            {
                if (fileInfo.Name != "MedusaExtensionPreDeclares.h")
                {
                    blocks.AddRange(ExtractPreDeclare(fileInfo));
                }
            }

            List<ClassBlock> distinctBlocks = new List<ClassBlock>();

            //remove duplicate blocks
            Dictionary<ClassBlock, bool> dupBlocks = new Dictionary<ClassBlock, bool>();
            foreach (var block in blocks)
            {
                if (!dupBlocks.ContainsKey(block))
                {
                    dupBlocks.Add(block, true);
                    distinctBlocks.Add(block);  //keep order
                }
            }

            //group
            SortedDictionary<string, List<ClassBlock>> blockGroups = new SortedDictionary<string, List<ClassBlock>>(new InverseStringComparer());
            foreach (var distinctBlock in distinctBlocks)
            {
                List<ClassBlock> innerBlocks = null;
                if (!blockGroups.TryGetValue(distinctBlock.NameSpace, out innerBlocks))
                {
                    innerBlocks = new List<ClassBlock>();
                    blockGroups.Add(distinctBlock.NameSpace, innerBlocks);
                }

                innerBlocks.Add(distinctBlock);
            }


            //serialize
            foreach (var blockGroup in blockGroups)
            {
                if (blockGroup.Key.Contains("Private") || blockGroup.Key.Contains("internal")) //ignore private classes
                {
                    continue;
                }

                if (blockGroup.Key != string.Empty)
                {
                    result.AppendFormat("namespace {0}", blockGroup.Key);
                    result.AppendLine();
                    result.AppendLine("{");

                    foreach (var block in blockGroup.Value)
                    {
                        foreach (var l in block.Lines)
                        {
                            result.AppendLine("\t" + l);
                        }
                    }
                    result.AppendLine("}");

                }
                else
                {
                    foreach (var block in blockGroup.Value)
                    {
                        foreach (var l in block.Lines)
                        {
                            result.AppendLine(l);
                        }
                    }
                }
            }

            result.AppendLine("#pragma region typedef");

            foreach (var typedefString in mTypedefStrings)
            {
                result.AppendLine(typedefString);
            }
            result.AppendLine("#pragma endregion typedef");


            result.AppendLine("MEDUSA_END;");


            WriteToFile(mProjectExtensionPath + @"\MedusaExtensionPreDeclares.h", result.ToString());

        }

        private void GenerateMedusaPreDeclare()
        {
            mTypedefStrings.Clear();

            StringBuilder result = new StringBuilder();
            result.AppendLine("#pragma once");
            result.AppendLine("#include \"Platform/Platform.h\"");

            //result.AppendLine("#include \"CorePlatform/Common/CommonMarcos.h\"");
            //result.AppendLine("#include \"CorePlatform/Common/MacroUtility.h\"");

            //result.AppendLine("#pragma warning(disable:4348)		//warning C4348 redefinition of default parameter");



            result.AppendLine("MEDUSA_BEGIN;");

            List<ClassBlock> blocks = new List<ClassBlock>();
            var files = GetDirectoryFiles(mProjectPath, true);
            foreach (var fileInfo in files)
            {
                if (fileInfo.Name != "MedusaPreDeclares.h")
                {
                    blocks.AddRange(ExtractPreDeclare(fileInfo));
                }
            }

            List<ClassBlock> distinctBlocks = new List<ClassBlock>();

            //remove duplicate blocks
            Dictionary<ClassBlock, bool> dupBlocks = new Dictionary<ClassBlock, bool>();
            foreach (var block in blocks)
            {
                if (!dupBlocks.ContainsKey(block))
                {
                    dupBlocks.Add(block, true);
                    distinctBlocks.Add(block);  //keep order
                }
            }

            //group
            SortedDictionary<string, List<ClassBlock>> blockGroups = new SortedDictionary<string, List<ClassBlock>>(new InverseStringComparer());
            foreach (var distinctBlock in distinctBlocks)
            {
                List<ClassBlock> innerBlocks = null;
                if (!blockGroups.TryGetValue(distinctBlock.NameSpace, out innerBlocks))
                {
                    innerBlocks = new List<ClassBlock>();
                    blockGroups.Add(distinctBlock.NameSpace, innerBlocks);
                }

                innerBlocks.Add(distinctBlock);
            }


            //serialize
            foreach (var blockGroup in blockGroups)
            {
                if (blockGroup.Key.Contains("Private") || blockGroup.Key.Contains("internal")) //ignore private classes
                {
                    continue;
                }

                if (blockGroup.Key != string.Empty)
                {
                    result.AppendFormat("namespace {0}", blockGroup.Key);
                    result.AppendLine();
                    result.AppendLine("{");

                    foreach (var block in blockGroup.Value)
                    {
                        foreach (var l in block.Lines)
                        {
                            result.AppendLine("\t" + l);
                        }
                    }
                    result.AppendLine("}");

                }
                else
                {
                    foreach (var block in blockGroup.Value)
                    {
                        foreach (var l in block.Lines)
                        {
                            result.AppendLine(l);
                        }
                    }
                }
            }

            result.AppendLine("#pragma region typedef");

            foreach (var typedefString in mTypedefStrings)
            {
                result.AppendLine(typedefString);
            }
            result.AppendLine("#pragma endregion typedef");


            result.AppendLine("MEDUSA_END;");
            WriteToFile(mProjectPath + @"\MedusaPreDeclares.h", result.ToString());

        }

        private void GenerateMedusaCoreHeader()
        {
            StringBuilder result = new StringBuilder();
            result.AppendLine("#pragma once");
            result.AppendLine("#include \"MedusaCorePreCompiled.h\"");
            result.AppendLine();

            List<string> lines = new List<string>();
            var subLines = GenerateDirectoryHeader(mProjectCorePath, mProjectCorePath + "\\Core");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            foreach (var line in lines)
            {
                result.AppendLine(line);
            }

            var str = result.ToString();
            WriteToFile(mProjectCorePath + @"\MedusaCore.h", str);

        }

        private void GenerateMedusaExtensionHeader()
        {
            StringBuilder result = new StringBuilder();
            result.AppendLine("#pragma once");
            result.AppendLine("#include \"MedusaExtensionPreCompiled.h\"");
            result.AppendLine();

            List<string> lines = new List<string>();

            var subLines = GenerateDirectoryHeader(mProjectExtensionPath, mProjectExtensionPath + "\\Analytics");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            //subLines = GenerateDirectoryHeader(mProjectExtensionPath, mProjectExtensionPath + "\\Channel");
            //lines.AddRange(subLines);
            //lines.Add(string.Empty);

            foreach (var line in lines)
            {
                result.AppendLine(line);
            }

            var str = result.ToString();
            WriteToFile(mProjectExtensionPath + @"\MedusaExtension.h", str);

        }


        private void GenerateMedusaHeader()
        {
            StringBuilder result = new StringBuilder();
            result.AppendLine("#pragma once");
            result.AppendLine("#include \"MedusaPreCompiled.h\"");
            result.AppendLine("#include \"MedusaCore.h\"");

            result.AppendLine();

            List<string> lines = new List<string>();

            var subLines = GenerateDirectoryHeader(mProjectPath, mProjectPath + "\\Graphics");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            subLines = GenerateDirectoryHeader(mProjectPath, mProjectPath + "\\Audio");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            subLines = GenerateDirectoryHeader(mProjectPath, mProjectPath + "\\Resource");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            subLines = GenerateDirectoryHeader(mProjectPath, mProjectPath + "\\Rendering");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            subLines = GenerateDirectoryHeader(mProjectPath, mProjectPath + "\\Node");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            subLines = GenerateDirectoryHeader(mProjectPath, mProjectPath + "\\Game");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            subLines = GenerateDirectoryHeader(mProjectPath, mProjectPath + "\\Application");
            lines.AddRange(subLines);
            lines.Add(string.Empty);

            foreach (var line in lines)
            {
                result.AppendLine(line);
            }

            var str = result.ToString();
            WriteToFile(mProjectPath + @"\Medusa.h", str);

        }

        private List<string> GenerateDirectoryHeader(string projectPath, string path)
        {
            projectPath = projectPath + "\\";
            List<string> lines = new List<string>();

            var files = GetDirectoryFiles(path, true);
            foreach (var fileInfo in files)
            {
                if (fileInfo.Directory.FullName.Contains("ios"))
                {
                    continue;
                }
                if (fileInfo.Extension != ".h" && fileInfo.Extension != ".inl")
                {
                    continue;
                }
                var subPath = fileInfo.FullName.Replace(projectPath, string.Empty);
                subPath = subPath.Replace("\\", "/");
                var line = string.Format("#include \"{0}\"", subPath);
                lines.Add(line);
            }

            lines.Sort();
            return lines;
        }

        private void mPreDeclareButton_Click(object sender, EventArgs e)
        {
            GenerateMedusaCorePreDeclare();
            GenerateMedusaPreDeclare();

        }

        public List<ClassBlock> ExtractPreDeclare(FileInfo fileInfo)
        {
            List<ClassBlock> result = new List<ClassBlock>();

            var lines = File.ReadAllLines(fileInfo.FullName);
            bool isInclude = false;
            for (int i = 0; i < lines.Length; i++)
            {
                var line = lines[i];
                lines[i] = line.Trim();

                if (line.Contains("//[IGNORE_PRE_DECLARE_FILE]"))
                {
                    return result;
                }


                if (line == "//[PRE_DECLARE_BEGIN]")
                {
                    isInclude = true;
                }
                else if (line == "//[PRE_DECLARE_END]")
                {
                    isInclude = false;
                }

                if (isInclude && line != "//[PRE_DECLARE_BEGIN]"&&!string.IsNullOrWhiteSpace(line))
                {
                    mTypedefStrings.Add(line);
                }
            }

            int preClassIndex = 0;
            for (int i = 0; i < lines.Length; i++)
            {
                var line = lines[i];
                if (line.StartsWith("namespace") && line.Contains("//[IGNORE_PRE_DECLARE]"))
                {
                    lines[i] = string.Empty;
                    continue;
                }


                if ((line.StartsWith("class ") || line.StartsWith("struct ")) && !line.Contains("\\") && !line.StartsWith("//")
                    && !line.Contains("//[IGNORE_PRE_DECLARE]") && !line.Contains("/*") && !line.Contains("::Schema") && !line.Contains("struct Schema;"))
                {
                    ClassBlock block = new ClassBlock();

                    for (int j = i - 1; j > 0; j--)
                    {
                        var preLine = lines[j];
                        if (preLine.StartsWith("namespace"))  //ignore private
                        {
                            preLine = preLine.Replace("namespace", string.Empty);
                            preLine = preLine.Trim();
                            block.NameSpace = preLine;
                            break;
                        }
                        if (preLine.StartsWith("//[PRE_DECLARE_NAMESPCAE]")) //custom
                        {
                            preLine = preLine.Replace("//[PRE_DECLARE_NAMESPCAE]", string.Empty);
                            preLine = preLine.Trim();
                            block.NameSpace = preLine;
                            break;
                        }


                    }

                    Stack<string> preLines = new Stack<string>();
                    bool isTemplate = false;
                    bool hasDefault = false;
                    for (int j = i - 1; j > preClassIndex; j--)
                    {
                        var preLine = lines[j];
                        if (!preLine.Contains(">")) //template should be one line
                        {
                            break;
                        }

                        //foreach (var ignoreString in mIgnoreStrings)
                        //{
                        //    preLine = preLine.Replace(ignoreString, string.Empty);
                        //}

                        preLines.Push(preLine);
                        if (preLine.StartsWith("template"))
                        {


                            if (preLine.Contains('='))
                            {
                                if (preLine.Contains("template <typename TId,typename TObject,typename TObjectNewer=DefaultNewerById<TId,TObject>,typename THashCoder=DefaultHashCoder<TId>,typename TKeyCompare=DefaultCompare<TId>,typename TObjectCompare=DefaultCompare<TObject> >"))
                                {
                                    foreach (var ignoreString in mIgnoreStrings)
                                    {
                                        preLine = preLine.Replace(ignoreString, string.Empty);
                                    }
                                }

                                foreach (var ignoreString in mIgnoreStrings)
                                {
                                    preLine = preLine.Replace(ignoreString, string.Empty);
                                }

                                //try to remove default
                                preLines.Pop();
                                do
                                {
                                    int index1 = preLine.IndexOf('=');
                                    if (index1 >= 0)
                                    {
                                        int index2 = preLine.IndexOf(',', index1);
                                        if (index2 < 0)
                                        {
                                            index2 = preLine.LastIndexOf('>');
                                        }

                                        preLine = preLine.Remove(index1, index2 - index1);
                                    }
                                    else
                                    {
                                        break;
                                    }


                                } while (true);
                                preLines.Push(preLine);

                                //hasDefault = true;
                            }
                            isTemplate = true;
                            break;
                        }
                    }

                    if (isTemplate)
                    {
                        if (hasDefault)
                        {
                            continue;
                        }
                        //continue;
                        block.Lines.AddRange(preLines);   //we have to pre declare template so that some template instance can be pre delcared
                    }



                    if (Regex.IsMatch(line, @"\w+\s+\w+\s+\w+;"))
                    {
                        continue;
                    }

                    if (line.Contains(":"))
                    {
                        if (line.Contains("public") || line.Contains("protected") || line.Contains("private"))
                        {
                            int x = line.IndexOf("public");
                            int y = line.IndexOf("protected");
                            int z = line.IndexOf("private");
                            int index = int.MaxValue;
                            if (x >= 0)
                            {
                                index = Math.Min(index, x);
                            }
                            if (y >= 0)
                            {
                                index = Math.Min(index, y);
                            }
                            if (z >= 0)
                            {
                                index = Math.Min(index, z);
                            }

                            while (true)
                            {
                                --index;
                                if (line[index] == ':')
                                {
                                    break;
                                }
                            }

                            line = line.Substring(0, index);
                        }
                        else
                        {
                            int index = line.IndexOf(":");
                            if (line.Contains("::"))
                            {

                            }
                            else
                            {
                                line = line.Substring(0, index);

                            }
                        }

                    }


                    if (line.Contains("{"))
                    {
                        line = line.Substring(0, line.IndexOf("{"));
                    }
                    line = line.TrimEnd();
                    if (line == "class" || line == "struct" || line == "interface" || line.Contains("<>"))
                    {
                        continue;
                    }

                    if (!line.EndsWith(";"))
                    {
                        line += ";";
                    }
                    block.Lines.Add(line);
                    block.Lines.Add(String.Empty);
                    preClassIndex = i;

                    result.Add(block);
                }
            }
            return result;
        }

        public static List<FileInfo> GetDirectoryFiles(string path, bool isRecursively = true)
        {
            List<FileInfo> result = new List<FileInfo>();
            var files = Directory.GetFiles(path);
            foreach (var file in files)
            {
                FileInfo info = new FileInfo(file);
                if (info.Extension == ".h" && info.Name != "PreDeclares.h" && !info.Name.Contains("pb.h"))
                {
                    result.Add(info);
                }
            }

            if (isRecursively)
            {
                var dirs = Directory.GetDirectories(path);
                foreach (string dir in dirs)
                {
                    if (dir.Contains("svn") || dir.Contains("Lib"))
                    {
                        continue;
                    }
                    result.AddRange(GetDirectoryFiles(dir, isRecursively));
                }
            }

            return result;
        }

        public static List<FileInfo> GetDirectoryFiles2(string path, bool isRecursively = true)
        {
            List<FileInfo> result = new List<FileInfo>();
            var files = Directory.GetFiles(path);
            foreach (var file in files)
            {
                FileInfo info = new FileInfo(file);
                if (info.Extension != ".cs")
                {
                    result.Add(info);
                }
            }

            if (isRecursively)
            {
                var dirs = Directory.GetDirectories(path);
                foreach (string dir in dirs)
                {
                    if (dir.Contains("svn") || dir.Contains("Lib"))
                    {
                        continue;
                    }
                    result.AddRange(GetDirectoryFiles2(dir, isRecursively));
                }
            }

            return result;
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            var dir = Environment.CurrentDirectory;
            int index = dir.IndexOf("Tool\\CodeAnalyzer");
            dir = dir.Substring(0, index);
            UpdatePaths(dir);


            GenerateMedusaCorePreDeclare();
            GenerateMedusaCoreHeader();

            GenerateMedusaPreDeclare();
            GenerateMedusaHeader();

            GenerateMedusaExtensionPreDeclare();
            GenerateMedusaExtensionHeader();


            
            //RemoveMedusaCoreMedusaNamespace();
            //RemoveMedusaMedusaNamespace();
            //RemoveMedusaExtensionMedusaNamespace();
            

            this.Close();

        }

        private void mHeaderButton_Click(object sender, EventArgs e)
        {
            GenerateMedusaCoreHeader();
            GenerateMedusaHeader();
            GenerateMedusaExtensionHeader();

        }
    }

    public class InverseStringComparer : IComparer<string>
    {
        public int Compare(string x, string y)
        {
            return y.CompareTo(x);
        }
    }

    public class ClassBlock
    {
        public string NameSpace = string.Empty;
        public readonly List<string> Lines = new List<string>();
        public override int GetHashCode()
        {
            int code = NameSpace.GetHashCode();
            for (int i = 0; i < Lines.Count; i++)
            {
                code ^= Lines[i].GetHashCode();
            }
            return code;

        }
        public override bool Equals(object obj)
        {

            ClassBlock block = obj as ClassBlock;
            if (NameSpace != block.NameSpace)
            {
                return false;
            }

            if (Lines.Count != block.Lines.Count)
            {
                return false;
            }

            for (int i = 0; i < Lines.Count; i++)
            {
                if (Lines[i] != block.Lines[i])
                {
                    return false;
                }
            }
            return true;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            foreach (var line in Lines)
            {
                sb.AppendLine(line);
            }
            return sb.ToString();
        }
    }

}
