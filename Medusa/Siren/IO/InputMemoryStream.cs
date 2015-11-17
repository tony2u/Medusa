// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Siren.IO
{
    /// <summary>
    /// Implements IInputStream on top of memory buffer
    /// </summary>
    public class InputMemoryStream : IInputStream
    {
        private MemoryStream mMemoryStream;

        public InputMemoryStream()
        {
            
        }
        public InputMemoryStream(byte[] data)
            : this(data, 0, data.Length)
        {

        }

        public InputMemoryStream(byte[] data, int length)
            : this(data, 0, length)
        { }

        public InputMemoryStream(ArraySegment<byte> seg)
            : this(seg.Array, seg.Offset, seg.Count)
        { }

        public InputMemoryStream(byte[] data, int offset, int length)
        {
            mMemoryStream = new MemoryStream(data, offset, length, false);
        }

        public void Accept(ArraySegment<byte> data)
        {
            mMemoryStream = new MemoryStream(data.Array, data.Offset, data.Count, false);
        }

        public void SkipBytes(int count)
        {
            mMemoryStream.Seek(count, SeekOrigin.Current);
        }

        public byte ReadUInt8()
        {
            return (byte)mMemoryStream.ReadByte();
        }

        public ushort ReadUInt16()
        {
            uint result = (byte)mMemoryStream.ReadByte();
            result |= (uint)mMemoryStream.ReadByte() << 8;
            return (ushort)result;
        }


        public uint ReadUInt32()
        {
            uint result = (uint)mMemoryStream.ReadByte();
            result |= (uint)mMemoryStream.ReadByte() << 8;
            result |= (uint)mMemoryStream.ReadByte() << 16;
            result |= (uint)mMemoryStream.ReadByte() << 24;
            return result;
        }

        public ulong ReadUInt64()
        {
            byte[] buffer = new byte[sizeof(ulong)];
            mMemoryStream.Read(buffer, 0, sizeof(ulong));
            return BitConverter.ToUInt64(buffer, 0);
        }

        public float ReadFloat()
        {
            byte[] buffer = new byte[sizeof(float)];
            mMemoryStream.Read(buffer, 0, sizeof(float));
            return BitConverter.ToSingle(buffer, 0);
        }

        public double ReadDouble()
        {
            byte[] buffer = new byte[sizeof(double)];
            mMemoryStream.Read(buffer, 0, sizeof(double));
            return BitConverter.ToDouble(buffer, 0);
        }

        public byte[] ReadBytes(int count)
        {
            byte[] buffer = new byte[count];
            mMemoryStream.Read(buffer, 0, count);
            return buffer;
        }

      
        public ushort ReadVarUInt16()
        {
            return IntegerHelper.DecodeVarUInt16(mMemoryStream);
        }

       
        public uint ReadVarUInt32()
        {
            return IntegerHelper.DecodeVarUInt32(mMemoryStream);
        }

        public ulong ReadVarUInt64()
        {
            return IntegerHelper.DecodeVarUInt64(mMemoryStream);
        }

        public string ReadString(int size)
        {
            byte[] tempBuffer=new byte[size];
            mMemoryStream.Read(tempBuffer, 0, size);

            var result = Encoding.UTF8.GetString(tempBuffer, 0, size - 1);
            
            return result;
        }

        public bool IsEnd()
        {
            return mMemoryStream.Position > mMemoryStream.Length;
        }


    }
}
