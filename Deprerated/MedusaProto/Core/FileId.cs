// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/IO",SirenGenerateMode.Suppress)]
    public class FileId
    {
        [SirenProperty]
        public string Name { get; set; }

        [SirenProperty(SirenPropertyModifier.Optional)]
        public uint Order { get; set; }
    }
}
