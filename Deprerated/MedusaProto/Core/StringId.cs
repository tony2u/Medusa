// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{

    [SirenClass(typeof(MedusaCoreTemplate), "Core/String/StringTable", SirenGenerateMode.Embeded)]
    public class StringId
    {
        [SirenProperty]
        public int Id { get; set; }
        [SirenProperty]
        public int Check1 { get; set; }
        [SirenProperty]
        public int Check2 { get; set; }

    }

   
}
