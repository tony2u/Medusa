// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/String/StringTable", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class StringNameItem
    {
        [SirenProperty]
        public Dictionary<uint, string> Items { get; set; }

    }

    [SirenClass(typeof(MedusaCoreTemplate), "Core/String/StringTable", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class StringTable
    {
        [SirenProperty]
        public Dictionary<string, StringNameItem> Items { get; set; }
    }
}
