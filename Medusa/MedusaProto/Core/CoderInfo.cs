// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/Coder", SirenGenerateMode.Generate | SirenGenerateMode.SuppressCompare)]
    public class CoderInfo
    {
        [SirenProperty]
        public CoderType Type { get; set; }
        [SirenProperty(SirenPropertyModifier.Optional)]
        public byte[] Data { get; set; }
    }


}
