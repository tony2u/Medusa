using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Medusa.Network
{
    public sealed class NetworkBuffer
    {
        private readonly MemoryStream mStream;
        private const int mInitialialSize = 1024;

        private int mWriteOffset;
        private int mReadOffset;

        public int PrependableCount => mReadOffset;
        public int ReadableCount => mWriteOffset - mReadOffset;
        public int WritableCount => (int)(mStream.Length - mWriteOffset);

        public NetworkBuffer(byte[] buffer)
        {
            mStream = new MemoryStream(buffer, 0, buffer.Length, false, true);
            mReadOffset = 0;
            mWriteOffset = buffer.Length;
        }

        public NetworkBuffer()
        {
            mStream = new MemoryStream();
            mStream.SetLength(mInitialialSize);
            mReadOffset = 0;
            mWriteOffset = 0;

        }

        public void Retrieve(int len)
        {
            if (len < ReadableCount)
            {
                mReadOffset += len;
            }
            else
            {
                RetrieveAll();
            }
        }

        public void RetrieveAll()
        {
            mReadOffset = 0;
            mWriteOffset = 0;
        }
        public int PeekInteger()
        {
            Debug.Assert(ReadableCount >= 4);
            var val = BitConverter.ToInt32(mStream.GetBuffer(), mReadOffset);
            val = IPAddress.NetworkToHostOrder(val);
            return val;
        }

        public uint PeekUInt()
        {
            Debug.Assert(ReadableCount >= 4);
            var val = BitConverter.ToInt32(mStream.GetBuffer(), mReadOffset);
            val = IPAddress.NetworkToHostOrder(val);
            return (uint)val;
        }

        public int ReadInteger()
        {
            Debug.Assert(ReadableCount >= 4);
            var val = BitConverter.ToInt32(mStream.GetBuffer(), mReadOffset);
            val = IPAddress.NetworkToHostOrder(val);
            mReadOffset += 4;
            return val;
        }

        public uint ReadUInt()
        {
            Debug.Assert(ReadableCount >= 4);
            var val = BitConverter.ToInt32(mStream.GetBuffer(), mReadOffset);
            val = IPAddress.NetworkToHostOrder(val);
            mReadOffset += 4;
            return (uint)val;
        }

        public void Write(int val)
        {
            val = IPAddress.HostToNetworkOrder(val);
            var buffer = BitConverter.GetBytes(val);
            Write(buffer);
        }

        public void Write(uint val)
        {
            int val2 = IPAddress.HostToNetworkOrder((int)val);
            var buffer = BitConverter.GetBytes(val2);
            Write(buffer);
        }

        public void Write(string val)
        {
            var buffer = Encoding.UTF8.GetBytes(val);
            Write(buffer, 0, buffer.Length);
        }

        public void Write(byte[] buffer)
        {
            Write(buffer, 0, buffer.Length);
        }
        public void Write(byte[] buffer, int offset, int count)
        {
            EnsureWritableCount(count);
            mStream.Seek(mWriteOffset, SeekOrigin.Begin);
            mStream.Write(buffer, offset, count);
            mWriteOffset += count;
        }

        public byte[] ReadAll()
        {
            var buffer = ReadData(ReadableCount);
            RetrieveAll();
            return buffer;
        }

        public byte[] ReadData(int len)
        {
            len = Math.Min(len, ReadableCount);
            mStream.Seek(mReadOffset, SeekOrigin.Begin);
            byte[] buffer = new byte[len];
            mStream.Read(buffer, 0, len);
            mReadOffset += len;
            return buffer;
        }

        public string ReadString(uint len)
        {
            var buffer = ReadData((int)len);
            return Encoding.UTF8.GetString(buffer);
        }


        private void EnsureWritableCount(int len)
        {
            if (WritableCount < len)
            {
                if (mReadOffset + WritableCount < len)  //available prepend and  write count < count needed
                {
                    mStream.SetLength(mWriteOffset + len);
                }
                else
                {
                    // move readable data to the front, make space inside buffer
                    int readable = ReadableCount;
                    var tempBuffer = new byte[readable];
                    mStream.Seek(mReadOffset, SeekOrigin.Begin);
                    mStream.Read(tempBuffer, 0, readable);

                    mStream.Seek(0, SeekOrigin.Begin);
                    mStream.Write(tempBuffer, 0, readable);

                    mReadOffset = 0;
                    mWriteOffset = mReadOffset + readable;
                }
            }
        }


    }
}