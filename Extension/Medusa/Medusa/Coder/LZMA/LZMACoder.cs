// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

namespace Medusa.Coder.LZMA
{
    public abstract class LZMACoder : BaseCoder
    {
        protected LZMACoder(byte[] key)
        {
            mKey = key;
        }

        protected readonly byte[] mKey;


        
    }
}