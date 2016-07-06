// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace Medusa.Siren.IO
{
    public class OutputMemoryStream : IOutputStream
    {
        private readonly MemoryStream mMemoryStream;

        public OutputMemoryStream(int length)
        {
            mMemoryStream = new MemoryStream(length);
        }
        public OutputMemoryStream()
            :this(1024)
        {
            
        }

        #region IOutputStream


        public void WriteUInt8(byte value)
        {
            mMemoryStream.WriteByte(value);
        }

        public void WriteUInt16(ushort value)
        {
            mMemoryStream.WriteByte((byte)value);
            mMemoryStream.WriteByte((byte)(value >> 8));
        }

        public virtual void WriteUInt32(uint value)
        {
            mMemoryStream.WriteByte((byte)value);
            mMemoryStream.WriteByte((byte)(value >> 8));
            mMemoryStream.WriteByte((byte)(value >> 16));
            mMemoryStream.WriteByte((byte)(value >> 24));
        }

        public virtual void WriteUInt64(ulong value)
        {

            mMemoryStream.WriteByte((byte)value);
            mMemoryStream.WriteByte((byte)(value >> 8));
            mMemoryStream.WriteByte((byte)(value >> 16));
            mMemoryStream.WriteByte((byte)(value >> 24));
            mMemoryStream.WriteByte((byte)(value >> 32));
            mMemoryStream.WriteByte((byte)(value >> 40));
            mMemoryStream.WriteByte((byte)(value >> 48));
            mMemoryStream.WriteByte((byte)(value >> 56));
        }

        public virtual void WriteFloat(float value)
        {
            WriteUInt32(new FloatLayout { value = value }.bytes);
        }

        public virtual void WriteDouble(double value)
        {
            WriteUInt64(new DoubleLayout { value = value }.bytes);
        }

        public virtual void WriteBytes(byte[] data)
        {
            mMemoryStream.Write(data, 0, data.Length);

        }

        public void WriteVarUInt16(ushort value)
        {
            IntegerHelper.EncodeVarUInt16(mMemoryStream, value);

        }

        public void WriteVarUInt32(uint value)
        {
            IntegerHelper.EncodeVarUInt32(mMemoryStream, value);
        }

        public void WriteVarUInt64(ulong value)
        {
            IntegerHelper.EncodeVarUInt64(mMemoryStream, value);
        }


        public void WriteString(string value)
        {
            var bytes = Encoding.UTF8.GetBytes(value);
            mMemoryStream.Write(bytes, 0, bytes.Length);
            mMemoryStream.WriteByte(0); //write '\0'
        }

        public ArraySegment<byte> ToBuffer()
        {
            return new ArraySegment<byte>(mMemoryStream.GetBuffer(), 0, (int)mMemoryStream.Length);
        }

        #endregion


        #region layouts

        [StructLayout(LayoutKind.Explicit)]
        struct DoubleLayout
        {
            [FieldOffset(0)]
            public readonly ulong bytes;

            [FieldOffset(0)]
            public double value;
        }

        [StructLayout(LayoutKind.Explicit)]
        struct FloatLayout
        {
            [FieldOffset(0)]
            public readonly uint bytes;

            [FieldOffset(0)]
            public float value;
        }

        #endregion
    }
}
