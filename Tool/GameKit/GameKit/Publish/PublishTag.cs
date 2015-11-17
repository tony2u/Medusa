// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;

namespace GameKit.Publish
{
    [Flags]
    public enum PublishVersions
    {
        none = 0,
        main = 1,
        free = 2,
        all = main | free,
    }

    [Flags]
    public enum PublishDevices
    {
        none = 0,
        sd = 1, //480*320
        hd = 2, //960*640
        hd5 = 4, //1136*640
        ipad = 8, //1024*768
        ipad3 = 16, //2048*1536.
        all = sd | hd | hd5 | ipad | ipad3,
    }


    [Flags]
    public enum PublishLanguages
    {
        none = 0,
        enus = 1,
        zhcn = 2,
        all = enus | zhcn,
    }

    [Flags]
    public enum PublishPlatform
    {
        Win=1,
        IOS=2,
        Android=4,
        WindowsPhone=8,
        all = Win | IOS | Android | WindowsPhone,

    }

    public enum PVRQuality
    {
        pvrtcfast = 0,
        pvrtcnormal = 1,
        pvrtchigh = 2,

    }
}
