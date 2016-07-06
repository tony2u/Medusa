using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Medusa.Common
{
    public static class StreamHelper
    {
        public static uint ReadUInt(this Stream stream)
        {
            byte[] buffer=new byte[4];
            stream.Read(buffer, 0, buffer.Length);
            return BitConverter.ToUInt32(buffer, 0);
        }
        public static int ReadInt(this Stream stream)
        {
            byte[] buffer = new byte[4];
            stream.Read(buffer, 0, buffer.Length);
            return BitConverter.ToInt32(buffer, 0);
        }

        public static string ReadString(this Stream stream)
        {
            StringBuilder sb=new StringBuilder();
            while (stream.CanRead)
            {
                char c = (char)stream.ReadByte();
                if (c!='\0')
                {
                    sb.Append(c);
                }
                else
                {
                    break;
                }
            }
            return sb.ToString();
        }

        public static void WriteString(this Stream stream,string val)
        {
            var bytes = Encoding.UTF8.GetBytes(val);
            stream.Write(bytes, 0, bytes.Length);
        }

        public static void Write(this Stream stream, uint val)
        {
            var bytes =BitConverter.GetBytes(val);
            stream.Write(bytes, 0, bytes.Length);
        }

        public static void Write(this Stream stream, int val)
        {
            var bytes = BitConverter.GetBytes(val);
            stream.Write(bytes, 0, bytes.Length);
        }
    }
}
