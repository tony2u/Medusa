// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.IO;
using System.Text;

namespace Siren.IO
{
    /// <summary>
    /// Reads primitive data types as binary values in a specific encoding 
    /// </summary>
    public interface IInputStream
    {
        byte ReadUInt8();
        ushort ReadUInt16();
        uint ReadUInt32();

        ulong ReadUInt64();
        float ReadFloat();
        double ReadDouble();
        byte[] ReadBytes(int count);
        void SkipBytes(int count);
        ushort ReadVarUInt16();
        uint ReadVarUInt32();
        ulong ReadVarUInt64();
        string ReadString(int size);

        void Accept(ArraySegment<byte> data);
        bool IsEnd();
    }
}
