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
    public abstract class BaseBinaryReader : BaseProtocolReader
    {
        public InputMemoryStream Stream { get; set; }
        protected BaseBinaryReader()
        {
            Stream=new InputMemoryStream();
            mIsPropertyWaiting = false;

        }

        public override void Accept(ArraySegment<byte> data)
        {
            Stream.Accept(data);
        }

        public override bool IsEnd()
        {
            return Stream.IsEnd();
        }


        protected ushort mCurrentPropertyId;
        protected SirenFieldType mCurrentPropertyType;
        protected SirenFieldType mCurrentKeyType;
        protected SirenFieldType mCurrentVaueType;
        protected bool mIsPropertyWaiting;


      

    

    }
}
