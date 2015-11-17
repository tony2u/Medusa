// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace GameKit.Publish
{
    public class PublishInfo
    {
        public PublishInfo(PublishVersions version, PublishDevices device, PublishLanguages language)
        {
            Version = version;
            Device = device;
            Language = language;
        }


        public PublishInfo()
            : this(PublishVersions.all, PublishDevices.all, PublishLanguages.all)
        {
        }

        public PublishInfo(int tag)
            : this((PublishVersions)((tag&0xFF0000)>>16), (PublishDevices)((tag&0x00FF00)>>8), (PublishLanguages)(tag&0x0000FF))
        {
        }

        public PublishVersions Version { get; set; }
        public PublishDevices Device { get; set; }
        public PublishLanguages Language { get; set; }
        public int Tag
        {
            get { return GetTag(Version, Device, Language); }
        }

        public static int GetTag(PublishVersions version, PublishDevices device, PublishLanguages language)
        {
            return (int)version << 16 | (int)device << 8 | (int)language;
        }

        public override bool Equals(object obj)
        {
            var info = (PublishInfo) obj;
            bool result = Version == info.Version && Device == info.Device && Language == info.Language;
            return result;
        }

        public override int GetHashCode()
        {
            return Version.GetHashCode() ^ Device.GetHashCode() ^ Language.GetHashCode();
        }

        public static PublishInfo GetPublishInfo(string filePath)
        {
            try
            {
                return GetPublishInfo(new FileInfo(filePath));

            }
            catch (System.Exception ex)
            {
                MessageBox.Show(string.Format("{0}  \n{1}", ex.Message, filePath));

                return null;
            }
        }

        public static PublishInfo GetPublishInfo(FileInfo file)
        {
            string resPath = file.Name;
            List<string> tags=new List<string>();

            int firstIndex=resPath.IndexOf('-');
            if (firstIndex<0)
            {
                return new PublishInfo(PublishVersions.all, PublishDevices.all,
                                        PublishLanguages.all);
            }

            string myPath;
            int lastIndex = resPath.LastIndexOf('.');

            if (lastIndex>0)
            {
                myPath=resPath.Substring(firstIndex, lastIndex - firstIndex);
            }
            else
            {
                myPath=resPath.Substring(firstIndex);
            }
            var tags1=myPath.Split(new char[] {'-'}, StringSplitOptions.RemoveEmptyEntries);
            tags.AddRange(tags1);



            var result = new PublishInfo(PublishVersions.none, PublishDevices.none,
                                         PublishLanguages.none);

            var versionNames = Enum.GetNames(typeof (PublishVersions));
            var deviceNames = Enum.GetNames(typeof (PublishDevices));
            var languageNames = Enum.GetNames(typeof (PublishLanguages));

            foreach (var versionName in versionNames)
            {
                if (tags.Contains(versionName))
                {
                    result.Version |= (PublishVersions)Enum.Parse(typeof(PublishVersions), versionName);
                }
            }

            if (result.Version == PublishVersions.none)
            {
                result.Version = PublishVersions.all;
            }

            foreach (var deviceName in deviceNames)
            {
                if (tags.Contains(deviceName))
                {
                    result.Device |= (PublishDevices)Enum.Parse(typeof(PublishDevices), deviceName);
                }
            }
           

            if (result.Device == PublishDevices.none)
            {
                result.Device = PublishDevices.all;
            }

            foreach (var languageName in languageNames)
            {
                if (tags.Contains(languageName))
                {
                    result.Language |= (PublishLanguages)Enum.Parse(typeof(PublishLanguages), languageName);
                }
            }

            if (result.Language == PublishLanguages.none)
            {
                result.Language = PublishLanguages.all;
            }

            return result;
        }

        public override string ToString()
        {
            string versionStr = string.Empty;
            if (Version != PublishVersions.all)
            {
                var items = Enum.GetValues(typeof (PublishVersions));
                versionStr =
                    items.Cast<PublishVersions>()
                         .Where(item => (Version & item) != 0 && item != PublishVersions.all)
                         .Aggregate(versionStr, (current, item) => current + ("-" + item.ToString()));
            }

            string deviceStr = string.Empty;
            if (Device != PublishDevices.all)
            {
                var items = Enum.GetValues(typeof (PublishDevices));
                deviceStr =
                    items.Cast<PublishDevices>()
                         .Where(item => (Device & item) != 0 && item != PublishDevices.all)
                         .Aggregate(deviceStr, (current, item) => current + ("-" + item.ToString()));
            }

            string languageStr = string.Empty;
            if (Language != PublishLanguages.all)
            {
                var items = Enum.GetValues(typeof (PublishLanguages));
                languageStr =
                    items.Cast<PublishLanguages>()
                         .Where(item => (Language & item) != 0 && item != PublishLanguages.all)
                         .Aggregate(languageStr, (current, item) => current + ("-" + item.ToString()));
            }

            return string.Format("{0}{1}{2}", versionStr, deviceStr, languageStr);
        }

        public void Merge(PublishInfo info)
        {
            Version |= info.Version;
            Device |= info.Device;
            Language |= info.Language;
        }

        public bool IsInclude(PublishInfo info)
        {
            if ((info.Version & Version) != info.Version)
            {
                return false;
            }
            if ((info.Device & Device) != info.Device)
            {
                return false;
            }
            if ((info.Language & Language) != info.Language)
            {
                return false;
            }

            return true;
        }

        public bool IsPublish(PublishTarget target)
        {
            var info = target.PublishInfo;
            if ((info.Version & Version) != 0)
            {
                return true;
            }
            if ((info.Device & Device) != 0)
            {
                return true;
            }
            if ((info.Language & Language) != 0)
            {
                return true;
            }
            return false;
        }

       
    }
}