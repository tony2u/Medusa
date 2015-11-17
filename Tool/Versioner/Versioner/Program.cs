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

namespace Versioner
{
    [Flags]
    enum VersionerOptions
    {
        None = 0,
        Binary = 2,
    }

    class Program
    {
        public static List<string> OptionStrings = new List<string> { "/b", };
        public static List<VersionerOptions> OptionValues = new List<VersionerOptions> { VersionerOptions.Binary };
        public static string VersionString = "const Medusa::Version AssemblyVersion(";
        public static string LastBuildDate = "const char* AssemblyLastBuildDate=";




        static void PrintHelp(string[] args)
        {
            string version = FileVersionInfo.GetVersionInfo(Assembly.GetExecutingAssembly().Location).FileVersion;
            Console.WriteLine("Welcome to Versioner {0}", version);
            Console.WriteLine("Format: Version [options] (files) ");
            Console.WriteLine("/b binary mode");
            Console.WriteLine("/? or /help show help");
            Console.WriteLine("Default is -b");
            Console.WriteLine("Arg count: {0}", args.Length);
            var argString = string.Join(" ", args);
            Console.WriteLine(argString);


        }

        static void Main(string[] args)
        {
            bool isHelp = args.Any(s => s == "/?" || s == "/help");
            if (args.Length == 0 || isHelp)
            {
                PrintHelp(args);
            }
            else if (args.Length < 1)
            {
                Console.WriteLine("Error arguments!");
                PrintHelp(args);
            }
            else
            {
                var options = VersionerOptions.None;
                var inputFiles = new List<string>();
                for (int i = 0; i < args.Length; ++i)
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
                            PrintHelp(args);
                            return;
                        }
                        inputFiles.Add(args[i]);
                    }
                }

                if (options == VersionerOptions.None)
                {
                    options = VersionerOptions.Binary;
                }


                foreach (var inputFile in inputFiles)
                {
                    var versionString = VersionFile(new FileInfo(inputFile), options);
                    Console.WriteLine("Version:{0}", versionString);
                }
            }
        }

        static string VersionFile(FileInfo outputFile, VersionerOptions options)
        {
            var allLines = File.ReadAllLines(outputFile.FullName);
            int versionStringIndex = 0;
            int buildDateIndex = 0;

            for (int i = 0; i < allLines.Length; i++)
            {
                var line = allLines[i];
                if (line.Contains(VersionString))
                {
                    versionStringIndex = i;
                }
                else if (line.Contains(LastBuildDate))
                {
                    buildDateIndex = i;
                }
            }

            string versionString = allLines[versionStringIndex];
            versionString = versionString.Replace(VersionString, string.Empty);
            versionString = versionString.Replace(");", string.Empty);
            var versionParts = versionString.Split(new string[] { "," }, System.StringSplitOptions.RemoveEmptyEntries);

            uint majorVal = Convert.ToUInt32(versionParts[0]);
            uint minorVal = Convert.ToUInt32(versionParts[1]);
            uint buildVal = Convert.ToUInt32(versionParts[2]);
            uint revisionVal = Convert.ToUInt32(versionParts[3]);


            int curRevision = TryGetSVNRevision(outputFile.Directory.FullName);
            if (curRevision>0&&curRevision != revisionVal)
            {
                buildVal = 0;
                revisionVal = (uint)curRevision;
            }
            ++buildVal;

            //get result
            var resultVersionString = string.Join(",", majorVal, minorVal, buildVal, revisionVal);
            allLines[versionStringIndex] = string.Format("\t{0}{1});", VersionString, resultVersionString);


            string dataString = DateTime.Now.ToString("u");
            dataString = dataString.Remove(dataString.Length - 1); //remove last char
            allLines[buildDateIndex] = string.Format("\t{0}\"{1}\";", LastBuildDate, dataString);

            using (StreamWriter sw = new StreamWriter(outputFile.FullName))
            {
                foreach (var allLine in allLines)
                {
                    sw.WriteLine(allLine);
                }
            }


            return resultVersionString;
        }


        public static int TryGetSVNRevision(string dir)
        {
            string arguments = string.Format(" info {0}", dir);
            ProcessStartInfo start = new ProcessStartInfo("svn.exe");
            start.Arguments = arguments;//??????

            start.CreateNoWindow = true;//???dos?????
            start.RedirectStandardOutput = true;//
            start.RedirectStandardInput = true;//
            start.UseShellExecute = false;//????????????????
            Process p = Process.Start(start);
            StreamReader reader = p.StandardOutput;//?????
            List<string> lines = new List<string>();
            do
            {
                string line = reader.ReadLine();//??????
                if (!string.IsNullOrEmpty(line))
                {
                    lines.Add(line);
                }

            } while (!reader.EndOfStream);

            p.WaitForExit();//???????????
            p.Close();//????
            reader.Close();//???


            foreach (var line in lines)
            {
                if (line.StartsWith("Revision:"))
                {
                    string temp = line.Replace("Revision:", string.Empty).Trim();
                    int revision = Convert.ToInt32(temp);
                    return revision;
                }
            }

            return 0;
        }


    }
}
