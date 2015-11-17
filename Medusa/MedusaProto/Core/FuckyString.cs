// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/String/FuckyString", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class FuckyStringNode
    {
        [SirenProperty]
        public int Char { get; set; }
        [SirenProperty]
        public bool IsFucky { get; set; }

        [SirenProperty(ForceValueToPtr = true)]
        public Dictionary<int, FuckyStringNode> Childs { get; set; }

    }

    [SirenClass(typeof(MedusaCoreTemplate), "Core/String/FuckyString", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class FuckyString
    {
        [SirenProperty]
        public Dictionary<int, FuckyStringNode> RootNodes { get; set; }
    }
}
