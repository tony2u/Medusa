// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Siren
{
    [Flags]
    public enum SirenGenerateMode
    {
        Generate = 1,
        Suppress = 2,
        Embeded = 4,

        CustomEnum = 8,
        CustomFlag = 16,

        SuppressCompare = 32,
        SuppressCopy = 64,

        SirenConfig = 128 | SuppressCompare | SuppressCopy,

    }
}
