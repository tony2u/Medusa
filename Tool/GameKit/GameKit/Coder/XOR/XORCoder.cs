// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;

namespace GameKit.Coder.XOR
{
    public abstract class XORCoder : BaseCoder
    {
        protected XORCoder(byte[] key)
        {
            mKey = key;
        }

        protected readonly byte[] mKey;


        
    }
}