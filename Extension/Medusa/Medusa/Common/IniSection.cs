// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System.Runtime.InteropServices;
using System.Text;

namespace Medusa.Common
{
    public class IniSection
    {
        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);

        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);

        public string FilePath { get; private set; }
        public string Section { get; private set; }

        public IniSection(string path, string section)
        {
            FilePath = path;
            Section = section;
        }

        public void WriteValue<T>(string key, T value)
        {
            WritePrivateProfileString(Section, key, value.ToString(), FilePath);
        }

        public string ReadString(string key)
        {
            var temp = new StringBuilder(1024);
            GetPrivateProfileString(Section, key, "", temp, 500, FilePath);
            string str = temp.ToString().Trim();
            return str;
        }

        public int ReadInt(string key)
        {
            var temp = new StringBuilder(1024);
            GetPrivateProfileString(Section, key, "", temp, 500, FilePath);
            string str = temp.ToString().Trim();
            return int.Parse(str);
        }

        public uint ReadUInt(string key)
        {
            var temp = new StringBuilder(1024);
            GetPrivateProfileString(Section, key, "", temp, 500, FilePath);
            string str = temp.ToString().Trim();
            return uint.Parse(str);
        }

        public float ReadFloat(string key)
        {
            var temp = new StringBuilder(1024);
            GetPrivateProfileString(Section, key, "", temp, 500, FilePath);
            string str = temp.ToString().Trim();
            return float.Parse(str);
        }

        public bool ReadBool(string key)
        {
            var temp = new StringBuilder(1024);
            GetPrivateProfileString(Section, key, "", temp, 500, FilePath);
            string str = temp.ToString().Trim();
            return str == "1";
        }
    }
}