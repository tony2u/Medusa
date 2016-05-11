// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), @"Core/String/RandomName")]
    public class RandomNameConfigItem
    {
        [SirenProperty]
        public uint Position { get; set; }
        [SirenProperty]
        public string Value { get; set; }

    }

    [SirenClass(typeof(MedusaCoreTemplate), @"Core/String/RandomName", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class RandomNameConfig
    {
        [SirenProperty]
        public List<RandomNameConfigItem> Items { get; set; }
    }
}
