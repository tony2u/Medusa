// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{

    [SirenClass(typeof(MedusaCoreTemplate), "Core/String/StringTable")]
    public class IdStringTable
    {
        [SirenProperty]
        public Dictionary<StringId, string> Items { get; set; }
    }
}
