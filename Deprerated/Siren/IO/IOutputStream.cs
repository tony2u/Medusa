// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Text;

namespace Siren.IO
{
    public interface IOutputStream
    {
        void WriteUInt8(byte value);
        void WriteUInt16(ushort value);
        void WriteUInt32(uint value);
        void WriteUInt64(ulong value);
        void WriteFloat(float value);
        void WriteDouble(double value);
        void WriteBytes(byte[] data);
        void WriteVarUInt16(ushort value);
        void WriteVarUInt32(uint value);
        void WriteVarUInt64(ulong value);
        void WriteString(string value);

        ArraySegment<byte> ToBuffer();
    }
}
