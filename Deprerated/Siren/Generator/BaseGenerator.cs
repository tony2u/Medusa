// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text;
using Siren.Attribute;

namespace Siren.Generator
{
    public abstract class BaseGenerator : IGenerator
    {
        public DirectoryInfo WorkingDirectory
        {
            get;
            set;
        }



        public void Generate()
        {
            foreach (var sirenClass in SirenFactory.SirenClasses)
            {
                if (sirenClass.Value.Attribute.Mode != SirenGenerateMode.Suppress)
                {
                    GenerateClass(sirenClass.Value);
                }
            }
        }

        public abstract void GenerateClass(SirenClass sirenClass);


        public void UpdateFile(string path, string content)
        {
            if (!File.Exists(path))
            {
                FileInfo info = new FileInfo(path);
                if (!info.Directory.Exists)
                {
                    info.Directory.Create();
                }

                File.WriteAllText(path, content,Encoding.UTF8);
                Console.WriteLine("Generate:{0}", path);
                return;
            }

            var oldText = File.ReadAllText(path);
            if (oldText != content)
            {
                File.WriteAllText(path, content, Encoding.UTF8);
                Console.WriteLine("Generate:{0}", path);
            }
            else
            {
                Console.WriteLine("Same:{0}", path);
            }
        }

        public string Replace(string text, string begin, string end, string content)
        {
            if (string.IsNullOrEmpty(content))
            {
                return text;
            }

            int index1 = text.IndexOf(begin);
            if (index1 < 0)
            {
                return text;
            }


            int index2 = text.IndexOf(end);
            if (index2 < 0 || index2 < index1)
            {
                return text;
            }

            text = text.Remove(index1 + begin.Length, index2 - index1 - begin.Length);
            text = text.Insert(index1 + begin.Length, content);
            return text;
        }
    }
}
