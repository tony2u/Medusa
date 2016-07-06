// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;

namespace Medusa.Coder.LZMA
{
    public class LZMADecoder : LZMACoder
    {
        public LZMADecoder(byte[] key)
            : base(key)
        {
        }

        public override byte[] Code(Byte[] data)
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