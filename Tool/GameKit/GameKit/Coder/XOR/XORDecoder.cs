// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using Medusa.CoreProto;

namespace GameKit.Coder.XOR
{
    public class XORDecoder : XORCoder
    {
        public XORDecoder(byte[] key)
            : base(key)
        {
        }


        public override FileList.FileCoder CoderInfo
        {
            get { return new FileList.FileCoder {Info = 0, Type = FileList.FileCoder.FileCoderType.XORDecoder}; }
        }

        public override Byte[] Code(byte[] data)
        {
            int keyIndex = 0;

            for (uint i = 0; i < data.Length; ++i)
            {
                data[i] ^= mKey[keyIndex];
                if (keyIndex < mKey.Length - 1)
                {
                    ++keyIndex;
                }
                else
                {
                    keyIndex = 0;
                }
            }

            return data;
        }

    }
}