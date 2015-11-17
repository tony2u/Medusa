// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

namespace FileWrapper
{
    [Flags]
    enum WrapperOptions
    {
        None = 0,
        Append = 1,
        Binary = 2,
        Literal = 4,
        Manually = 8,
        Recursively = 16,
        ClearOutputDir = 32,


    }

    struct MyFileInfo
    {
        public FileInfo Info;
        public DirectoryInfo Root;

        public string SubPath
        {
            get
            {
                return Info.DirectoryName.Replace(Root.FullName, String.Empty).TrimStart(Path.DirectorySeparatorChar);
            }
        }
    }
    class Program
    {
        public static List<string> OptionStrings = new List<string> { "/a", "/b", "/s", "/m", "/r", "/c" };
        public static List<WrapperOptions> OptionValues = new List<WrapperOptions> { WrapperOptions.Append, WrapperOptions.Binary, WrapperOptions.Literal, WrapperOptions.Manually, WrapperOptions.Recursively, WrapperOptions.ClearOutputDir };
        public static uint LineCharCount = 150;

        static uint ConvertInt(uint b1, uint b2, uint b3, uint b4)
        {
            return b1 | b2 << 8 | b3 << 16 | b4 << 24;
        }

        static void PrintHelp()
        {
            string version = FileVersionInfo.GetVersionInfo(Assembly.GetExecutingAssembly().Location).FileVersion;
            Console.WriteLine("Welcome to FileWrapper {0}", version);
            Console.WriteLine("Format: FileWrapper (outFile or outDir) [options] (inputFiles or inputDirs)");
            Console.WriteLine("/a append to out file");
            Console.WriteLine("/b binary mode");
            Console.WriteLine("/s string literal mode");
            Console.WriteLine("/m manually register");
            Console.WriteLine("/r recursively");
            Console.WriteLine("/c clear output dir");
            Console.WriteLine("/? or /help show help");
            Console.WriteLine("Default is /b /m");

        }

        static void Main(string[] args)
        {

            bool isHelp = args.Any(s => s == "/?" || s == "/help");
            if (args.Length == 0 || isHelp)
            {
                PrintHelp();
            }
            else if (args.Length < 2)
            {
                Console.WriteLine("Error arguments!");
                PrintHelp();
            }
            else
            {
                string outputFile = args[0];
                var options = WrapperOptions.None;
                var inputFiles = new List<string>();
                for (int i = 1; i < args.Length; ++i)
                {
                    int index = OptionStrings.IndexOf(args[i]);
                    if (index >= 0)
                    {
                        options |= OptionValues[index];
                    }
                    else
                    {
                        if (args[i].Contains('/'))
                        {
                            Console.WriteLine("Error arguments!");
                            PrintHelp();
                            return;
                        }
                        inputFiles.Add(args[i]);
                    }
                }

                if (options.HasFlag(WrapperOptions.Binary) && options.HasFlag(WrapperOptions.Literal))
                {
                    Console.WriteLine("Cannot use -s and -b together!");
                    PrintHelp();
                }
                else
                {
                    if (options == WrapperOptions.None)
                    {
                        options = WrapperOptions.Binary | WrapperOptions.Manually;
                    }
                    if (Path.HasExtension(outputFile))
                    {
                        SearchOption searchOption = options.HasFlag(WrapperOptions.Recursively)
                                                   ? SearchOption.AllDirectories
                                                   : SearchOption.TopDirectoryOnly;
                        var allFiles = GetAllInputFiles(inputFiles, searchOption);
                        WrapperToFile(outputFile, options, allFiles);
                    }
                    else
                    {
                        SearchOption searchOption = options.HasFlag(WrapperOptions.Recursively)
                                                  ? SearchOption.AllDirectories
                                                  : SearchOption.TopDirectoryOnly;
                        var allFiles = GetAllInputFiles(inputFiles, searchOption);
                        WrapperToDirectory(outputFile, options, allFiles);

                    }


                }


            }
            Console.WriteLine("Success!");
        }
        static List<MyFileInfo> GetAllInputFiles(List<string> inputFiles, SearchOption searchOption)
        {
            List<MyFileInfo> result = new List<MyFileInfo>();
            foreach (var inputFile in inputFiles)
            {
                if (Path.HasExtension(inputFile))
                {
                    string dir = Path.GetDirectoryName(inputFile);
                    string ext = Path.GetFileName(inputFile);
                    var files = Directory.EnumerateFiles(dir, ext, searchOption);
                    foreach (var file in files)
                    {
                        result.Add(new MyFileInfo() { Info = new FileInfo(file), Root = new DirectoryInfo(Path.GetDirectoryName(inputFile)) });
                    }

                }
                else
                {
                    //is path
                    var files = Directory.EnumerateFiles(inputFile, "*.*", searchOption);
                    foreach (var file in files)
                    {
                        result.Add(new MyFileInfo() { Info = new FileInfo(file), Root = new DirectoryInfo(Path.GetDirectoryName(inputFile)) });
                    }
                }
            }

            return result;
        }

        static void WrapperToDirectory(string outputDir, WrapperOptions options, IEnumerable<MyFileInfo> inputFiles)
        {
            if (Directory.Exists(outputDir))
            {
                if (options.HasFlag(WrapperOptions.ClearOutputDir))
                {
                    Directory.Delete(outputDir, true);
                }
                Directory.CreateDirectory(outputDir);
            }


            foreach (var myFileInfo in inputFiles)
            {
                string newOutDir = Path.Combine(outputDir, myFileInfo.SubPath);
                if (!Directory.Exists(newOutDir))
                {
                    Directory.CreateDirectory(newOutDir);
                }
                string newOutputFile = Path.Combine(newOutDir, myFileInfo.Info.Name.Replace('.', '_') + ".cpp");
                //                newOutputFile = Path.ChangeExtension(newOutputFile, ".cpp");
                WrapperToFile(newOutputFile, options, new List<MyFileInfo>() { myFileInfo });
            }
        }
        static void WrapperToFile(string outputFile, WrapperOptions options, IEnumerable<MyFileInfo> inputFiles)
        {
            StringBuilder sb = new StringBuilder();
            StringWriter sw = new StringWriter(sb);
            if (options.HasFlag(WrapperOptions.Append))
            {
                if (File.Exists(outputFile))
                {
                    string temp = File.ReadAllText(outputFile);
                    sw.Write(temp);
                }
            }
            else
            {
                string version = FileVersionInfo.GetVersionInfo(Assembly.GetExecutingAssembly().Location).FileVersion;

                sw.WriteLine("//This file was created by FileWrapper {0}", version);
                sw.WriteLine("//DO NOT EDIT");

                sw.WriteLine("#include \"MedusaPreCompiled.h\"");
                sw.WriteLine("#include \"Core/IO/MemoryFileAutoRegister.h\"");
            }


            foreach (var inputFile in inputFiles)
            {
                if (options.HasFlag(WrapperOptions.Binary))
                {
                    WrapperBinary(sw, inputFile.Info.FullName, options.HasFlag(WrapperOptions.Manually));
                }
                else
                {
                    WrapperString(sw, inputFile.Info.FullName, options.HasFlag(WrapperOptions.Manually));
                }
            }

            sw.Close();

            String result = sb.ToString();
            if (options.HasFlag(WrapperOptions.Append))
            {
                System.IO.File.WriteAllText(outputFile, result);
            }
            else
            {
                if (File.Exists(outputFile))
                {
                    string temp = File.ReadAllText(outputFile);
                    if (temp != result)
                    {
                        System.IO.File.WriteAllText(outputFile, result);
                    }
                }
                else
                {
                    System.IO.File.WriteAllText(outputFile, result);
                }
            }
        }

        static void WrapperBinary(StringWriter sw, string file, bool isManually)
        {
            var info = new FileInfo(file);
            string fieldName = "_" + info.Name.Replace('.', '_');
            sw.WriteLine("#pragma region {0}", info.Name);
            sw.WriteLine("MEDUSA_CONTENT_BEGIN;");

            sw.WriteLine("const static uint {0}[] = {{", fieldName);

            byte[] bytes = File.ReadAllBytes(file);
            int size = bytes.Length;
            var sb = new StringBuilder();
            for (int i = 0; i < size; i += 4)
            {
                uint r;
                if (i + 3 < size)
                {
                    r = ConvertInt(bytes[i], bytes[i + 1], bytes[i + 2], bytes[i + 3]);
                }
                else
                {
                    int d = size - 1 - i;
                    switch (d)
                    {
                        case 0:
                            r = ConvertInt(bytes[i], 0, 0, 0);
                            break;
                        case 1:
                            r = ConvertInt(bytes[i], bytes[i + 1], 0, 0);
                            break;
                        case 2:
                            r = ConvertInt(bytes[i], bytes[i + 1], bytes[i + 2], 0);
                            break;
                        default:
                            throw new Exception("Error");
                    }
                }

                string str = "0x" + Convert.ToString(r, 16) + ",";
                sb.Append(str);
                if (sb.Length >= LineCharCount)
                {
                    sw.WriteLine(sb);
                    sb.Clear();
                }
            }
            //last line
            if (sb.Length > 0)
            {
                sw.WriteLine(sb);
            }

            sw.WriteLine("};");
            if (isManually)
            {
                sw.WriteLine("//const static MemoryFileAutoRegister mRegister{0}(\"{1}\",{2},{3});", fieldName, info.Name, fieldName, size);
                sw.WriteLine("static void Register{0}(){{MemoryFileAutoRegister::Register(\"{1}\",{2},{3});}}", fieldName, info.Name, fieldName, size);
            }
            else
            {
                sw.WriteLine("const static MemoryFileAutoRegister mRegister{0}(\"{1}\",{2},{3});", fieldName, info.Name, fieldName, size);
                sw.WriteLine("//static void Register{0}(){{MemoryFileAutoRegister::Register(\"{1}\",{2},{3});}}", fieldName, info.Name, fieldName, size);
            }


            sw.WriteLine("MEDUSA_CONTENT_END;");

            sw.WriteLine("#pragma endregion {0}", info.Name);
            sw.WriteLine();
        }

        static void WrapperString(StringWriter sw, string file, bool isManually)
        {
            string[] allLines = File.ReadAllLines(file);
            var info = new FileInfo(file);
            string fieldName = "_" + info.Name.Replace('.', '_');
            sw.WriteLine("#pragma region {0}", info.Name);
            sw.WriteLine("MEDUSA_CONTENT_BEGIN;");

            sw.WriteLine("const static char {0}[] = \"\\", fieldName);
            foreach (var allLine in allLines)
            {
                var newLine = allLine.Replace("\"", "\\\"");
                sw.WriteLine(newLine + "\\n\\");
            }
            sw.WriteLine("\";");
            if (isManually)
            {
                sw.WriteLine("//const static MemoryFileAutoRegister mRegister{0}(FileIdRef(\"{1}\"),{2});", fieldName, info.Name, fieldName);
                sw.WriteLine("static void Register{0}(){{MemoryFileAutoRegister::Register(FileIdRef(\"{1}\"),{2});}}", fieldName, info.Name, fieldName);
            }
            else
            {
                sw.WriteLine("const static MemoryFileAutoRegister mRegister{0}(FileIdRef(\"{1}\"),{2});", fieldName, info.Name, fieldName);
                sw.WriteLine("//static void Register{0}(){{MemoryFileAutoRegister::Register(FileIdRef(\"{1}\"),{2});}}", fieldName, info.Name, fieldName);
            }
            sw.WriteLine("MEDUSA_CONTENT_END;");

            sw.WriteLine("#pragma endregion {0}", info.Name);
            sw.WriteLine();
        }
    }
}
