// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/Utility", SirenGenerateMode.Suppress)]
    public class Version
    {
        [SirenProperty]
        public uint Major { get; set; }
        [SirenProperty]
        public uint Minor { get; set; }
        [SirenProperty]
        public uint Build { get; set; }
        [SirenProperty]
        public uint Revision { get; set; }

    }
}
