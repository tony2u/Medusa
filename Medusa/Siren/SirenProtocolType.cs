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
    public enum SirenProtocolType
    {
        // Fast binary protocol
        Fast = 0x464d,

        // Compact binary protocol
        Compact = 0x4243,

        // Simple JSON protocol
        Json = 0x4a53,
    }
}
