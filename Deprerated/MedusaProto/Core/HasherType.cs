// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/Hash", EnumUnderType = "byte")]
    public enum HasherType
    {
        None = 0,

        CRC32C = 1,
        MD5 = 2,
        SHA1 = 3
    };


}
