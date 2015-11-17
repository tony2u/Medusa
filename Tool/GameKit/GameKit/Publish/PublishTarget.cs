// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using System.IO;
using System.Windows.Forms.Design;
using GameKit.Packing;
using GameKit.UI;
using Medusa.CoreProto;
using Version = System.Version;

namespace GameKit.Publish
{
    public class PublishTarget
    {
        public static PublishTarget Current = new PublishTarget();

        public PublishTarget()
        {
            Platform = PublishPlatform.Win;
            Device = PublishDevices.all;
            Language = PublishLanguages.all;
            Version = PublishVersions.all;
            IsOptimzed = true;
            IsRecursively = true;
            IsGenerateUpdateServer = false;
            IsGuidName = false;
            LimitSize = Size.Empty;
            ClientVersion = new Version(1,0);
            IsPVR = true;
            UpdateServerStatus = UpdateServer.UpdateServerStatus.OK;
            UpdateServerMinClientVersion = new Version(1,0);
            IsGod = false;
            IsCacheEnabled = false;
        }

        [Category("??"), Description("??????,????")]
        public bool IsGod { get; set; }

        [Category("??"), Description("??????,?????????,?????????PVR")]
        public bool IsCacheEnabled { get; set; }

        [Category("PVR"), Description("?????PVR?????")]
        public bool IsPVR { get; set; }

        [Category("PVR"), Description("PVR??")]
        public string PVRFormat
        {
            get
            {
                if (Platform == PublishPlatform.Android)
                {
                    return "PVRTC1_4";
                }
                if (Platform == PublishPlatform.IOS)
                {
                    return "PVRTC1_4";
                }
                return "PVRTC1_4";
            }
        }




        [Category("PVR"), Description("PVR??")]
        public PVRQuality PVRQuality { get; set; }


        [Category("??"), Description("?????")]
        [TypeConverter(typeof(FlagsEnumConverter))]
        public PublishPlatform Platform { get; set; }

        [Category("??"), Description("????")]
        [TypeConverter(typeof(FlagsEnumConverter))]
        public PublishDevices Device { get; set; }

        [Category("??"), Description("??")]
        [TypeConverter(typeof(FlagsEnumConverter))]
        public PublishLanguages Language { get; set; }

        [Category("??"), Description("??")]
        [TypeConverter(typeof(FlagsEnumConverter))]
        public PublishVersions Version { get; set; }

        [Category("??"), Description("?????0,0???????????")]
        public Size LimitSize { get; set; }

        private bool mIsPOT = false;
        [Category("??"), Description("???????????2??")]
        public bool IsPOT
        {
            get
            {
                if (IsPVR)
                {
                    return true;
                }
                return mIsPOT;
            }
            set
            {
                mIsPOT = value;
            }
        }

        private bool mIsSquare = false;
        [Category("??"), Description("????????????")]
        public bool IsSquare
        {
            get
            {
                if (IsPVR)
                {
                    return true;
                }
                return mIsSquare;
            }
            set
            {
                mIsSquare = value;
            }
        }


        private bool mIsOptimzed = false;

        [Category("??"), Description("??????????????")]
        public bool IsOptimzed
        {
            get
            {
                //if (IsPVR)
                //{
                //    return true;
                //}
                return mIsOptimzed;
            }
            set
            {
                mIsOptimzed = value;
            }
        }

        [Category("??"), Description("???????????")]
        public bool IsGenerateUpdateServer { get; set; }

        [Category("??"), Description("????Android?????")]
        public bool IsGenerateAndroid { get { return (Platform & PublishPlatform.Android) != 0; } }

        private bool mIsPack = true;

        [Category("??"), Description("??????")]
        public bool IsPack
        {
            get
            {
                if (IsPVR)
                {
                    return true;
                }
                return mIsPack;
            }
            set
            {
                mIsPack = value;
            }
        }


        [Category("??"), Description("????")]
        public bool IsEncrypt { get; set; }

        [Category("??"), Description("????")]
        public bool IsCompress { get; set; }

        [Category("??"), Description("???????????")]
        public Size DefaultImageSize
        {
            get
            {
                return new Size(128, 128);
            }
        }

        [Category("??"), Description("??????")]
        public Size MaxImageSize
        {
            get
            {
                if (LimitSize == Size.Empty)
                {
                    if ((Device & PublishDevices.sd) == PublishDevices.sd || Device == PublishDevices.none)
                    {
                        return new Size(512, 512);
                    }

                    if (Device == PublishDevices.hd)
                    {
                        return new Size(1024, 1024);
                    }

                    if ((Platform & PublishPlatform.Android) != 0)
                    {
                        return new Size(2048, 2048);
                    }

                    return new Size(2048, 2048);
                }
                return LimitSize;
            }
        }


        [Category("??"), Description("???????")]
        public bool IsGuidName { get; set; }

        [Category("??"), Description("??")]
        public string DataPath
        {
            get
            {
                if (PathManager.DataPath == null)
                {
                    return string.Empty;
                }
                return PathManager.DataPath.FullName;
            }
        }

        [Category("??"), Description("????")]
        public string InputPath
        {
            get
            {
                if (PathManager.InputPath == null)
                {
                    return string.Empty;
                }
                return PathManager.InputPath.FullName;
            }
        }


        [Category("??"), Description("???????")]
        public bool IsRecursively { get; set; }

        [Category("??"), Description("????")]
        public string OutputPath
        {
            get
            {
                if (PathManager.OutputPath == null)
                {
                    return string.Empty;
                }
                return PathManager.OutputPath.FullName;
            }
        }

        [Browsable(false)]
        public string FileSystemFileName { get; set; }

        [Browsable(false)]
        public string FileListFileName { get; set; }

        [Category("???"), Description("?????")]
        [TypeConverter(typeof(VersionConverter))]
        public Version ClientVersion { get; set; }

        [Category("?????"), Description("???????")]
        public UpdateServer.UpdateServerStatus UpdateServerStatus { get; set; }
        [Category("?????"), Description("???????????????")]
        [TypeConverter(typeof(VersionConverter))]
        public Version UpdateServerMinClientVersion { get; set; }
        [Category("?????"), Description("?????????")]
        public string UpdateServerPath
        {
            get
            {
                if (PathManager.UpdateServerPath == null)
                {
                    return string.Empty;
                }
                return PathManager.UpdateServerPath.FullName;
            }
        }

        [Category("?????"), Description("??????????")]
        public string UpdateServerConfigFileName { get; set; }

        [Category("?????"), Description("?????????")]
        public string UpdateServerDescription { get; set; }

        [Category("?????"), Description("?????????")]
        public string GameServerPath
        {
            get
            {
                if (PathManager.GameServerPath == null)
                {
                    return string.Empty;
                }
                return PathManager.GameServerPath.FullName;
            }
        }

        [Category("??"), Description("????????")]
        public string ProjectPath
        {
            get
            {
                if (PathManager.ProjectPath == null)
                {
                    return string.Empty;
                }
                return PathManager.ProjectPath.FullName;
            }
        }


        [Category("??"), Description("????")]
        public string DevPath
        {
            get
            {
                if (PathManager.DevPath == null)
                {
                    return string.Empty;
                }
                return PathManager.DevPath.FullName;
            }
        }

        [Category("??"), Description("???????")]
        //[Editor(typeof(FolderNameEditor), typeof(UITypeEditor))]
        public string RootPath
        {
            get
            {
                if (PathManager.RootPath == null)
                {
                    return string.Empty;
                }
                return PathManager.RootPath.FullName;
            }
            //set
            //{
            //    PathManager.RootPath = new DirectoryInfo(value);
            //}
        }
        [Browsable(false)]
        public string FileSystemFilePath
        {
            get { return OutputPath + System.IO.Path.AltDirectorySeparatorChar + FileSystemFileName; }

        }

        [Browsable(false)]
        public string FileListFilePath
        {
            get { return OutputPath + System.IO.Path.AltDirectorySeparatorChar + FileListFileName; }

        }

        [Browsable(false)]
        public string ServerConfigFilePath
        {
            get { return UpdateServerPath + System.IO.Path.AltDirectorySeparatorChar + UpdateServerConfigFileName; }

        }

        [Browsable(false)]
        public PublishInfo PublishInfo
        {
            get { return new PublishInfo(Version, Device, Language); }
        }

        [Browsable(false)]
        public DirectoryInfo InputDirectoryInfo
        {
            get { return new DirectoryInfo(InputPath); }
        }

        [Browsable(false)]
        public DirectoryInfo OutputDirectoryInfo
        {
            get { return new DirectoryInfo(OutputPath); }
        }





    }
}