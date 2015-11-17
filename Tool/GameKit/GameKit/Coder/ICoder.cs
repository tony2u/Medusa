// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using Medusa.CoreProto;

namespace GameKit.Coder
{
    public interface ICoder
    {
        byte[] Code(byte[] data);
        FileList.FileCoder CoderInfo { get; }
    }
}