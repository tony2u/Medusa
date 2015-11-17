// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config")]
    public enum UpdateServerStatus
    {
        OK = 0,
        Maintain = 1,
        Error = 2,
        DontUpgrade = 3
    };

    [SirenClass(typeof (MedusaCoreTemplate), "Core/Config", SirenGenerateMode.SirenConfig)]
    public class PackageInfo
    {
        [SirenProperty]
        public string Description { get; set; }

        [SirenProperty]
        public string Path { get; set; }

        [SirenProperty]
        public string Signature { get; set; }   //used to check after download from internet
    }

    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config", SirenGenerateMode.SirenConfig)]
    public class UpdateServer
    {
        [SirenProperty]
        public uint MinAppVersion { get; set; }

        [SirenProperty]
        public uint CurFileVersion { get; set; }

        [SirenProperty]
        public string Description { get; set; }

        [SirenProperty]
        public UpdateServerStatus Status { get; set; }

        [SirenProperty]
        public Dictionary<uint, PackageInfo> Patches { get; set; }

        [SirenProperty]
        public Dictionary<uint, PackageInfo> JumpPatches { get; set; }
    }
}
