// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Siren.IO;

namespace Siren.Protocol.Binary
{
    public abstract class BaseBinaryWriter : BaseProtocolWriter
    {
        public OutputMemoryStream Stream { get; set; }

        protected BaseBinaryWriter()
        {
            Stream = new OutputMemoryStream();
        }

     

        public override ArraySegment<byte> ToBuffer()
        {
            return Stream.ToBuffer();
        }

      
    }
}
