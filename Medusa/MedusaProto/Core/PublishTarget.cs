// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using Siren;
using Siren.Attribute;
namespace Medusa.Core
{


    [Flags]
    [SirenClass(typeof(MedusaCoreTemplate), @"Core/System", SirenGenerateMode.Suppress)]
    public enum PublishVersions
    {
        none = 0,
        main = 1,
        free = 2,
        all = main | free,
    };

    [Flags]
    [SirenClass(typeof(MedusaCoreTemplate), @"Core/System", SirenGenerateMode.Suppress)]
    public enum PublishDevices
    {
        none = 0,
        sd = 1, //480*320
        hd = 2, //960*640
        hd5 = 4, //1136*640
        ipad = 8, //1024*768
        ipad3 = 16, //2048*1536.
        all = sd | hd | hd5 | ipad | ipad3,
    };


    [Flags]
    [SirenClass(typeof(MedusaCoreTemplate), @"Core/System", SirenGenerateMode.Suppress)]
    public enum PublishLanguages
    {
        none = 0,
        enus = 1,
        zhcn = 2,
        all = enus | zhcn,
    };


    public enum PublishPlatform
    {
        Win = 1,
        IOS = 2,
        Android = 4,
        WindowsPhone = 8,
        all = Win | IOS | Android | WindowsPhone,

    }

    [SirenClass(typeof(MedusaCoreTemplate), @"Core/System", SirenGenerateMode.Suppress)]
    public class PublishTarget
    {
        [SirenProperty(SirenPropertyModifier.Optional)]
        public PublishVersions Version { get; set; }
        [SirenProperty(SirenPropertyModifier.Optional)]
        public PublishDevices Device { get; set; }
        [SirenProperty(SirenPropertyModifier.Optional)]
        public PublishLanguages Language { get; set; }

        public override int GetHashCode()
        {
            return Tag();
        }

        public int Tag() { return ((int)Version << 16) | ((int)Device << 8) | ((int)Language); }
    }
}
