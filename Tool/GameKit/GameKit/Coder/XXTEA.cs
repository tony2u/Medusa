// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Text;

namespace GameKit.Coder
{
    public class XXTEACoder
    {
        private const uint mDelta = 0x9E3779B9;
        private const string mKey = "1CE75352E16F47CCAB16D283B19AA9D5";
        private static readonly byte[] mKeyBytes;

       
        static XXTEACoder()
        {
            mKeyBytes = Encoding.UTF8.GetBytes(mKey);
            //var key = ByteArrayToString(mKeyBytes);
        }

        public static byte[] Encrypt(Byte[] data)
        {
            return Encrypt(data, mKeyBytes);
        }

        public static Byte[] Decrypt(Byte[] data)
        {
            return Decrypt(data, mKeyBytes);
        }

        private static Byte[] Encrypt(Byte[] data, Byte[] key)
        {
            if (data.Length == 0)
            {
                return data;
            }
            return ToByteArray(Encrypt(ToUInt32Array(data, true), ToUInt32Array(key, false)), false);
        }
        private static Byte[] Decrypt(Byte[] data, Byte[] key)
        {
            if (data.Length == 0)
            {
                return data;
            }
            return ToByteArray(Decrypt(ToUInt32Array(data, false), ToUInt32Array(key, false)), true);
        }

        private static UInt32[] Encrypt(UInt32[] v, UInt32[] k)
        {
            Int32 n = v.Length - 1;
            if (n < 1)
            {
                return v;
            }
            if (k.Length < 4)
            {
                var key = new UInt32[4];
                k.CopyTo(key, 0);
                k = key;
            }
            UInt32 z = v[n];

            UInt32 sum = 0;
            Int32 q = 6 + 52 / (n + 1);
            while (q-- > 0)
            {
                sum = unchecked(sum + mDelta);
                UInt32 e = sum >> 2 & 3;
                UInt32 y;
                Int32 p;
                for (p = 0; p < n; p++)
                {
                    y = v[p + 1];
                    z = unchecked(v[p] += (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z));
                }
                y = v[0];
                z = unchecked(v[n] += (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z));
            }
            return v;
        }
        private static UInt32[] Decrypt(UInt32[] v, UInt32[] k)
        {
            Int32 n = v.Length - 1;
            if (n < 1)
            {
                return v;
            }
            if (k.Length < 4)
            {
                var key = new UInt32[4];
                k.CopyTo(key, 0);
                k = key;
            }
            UInt32 y = v[0];

            Int32 q = 6 + 52 / (n + 1);
            var sum = unchecked((UInt32)(q * mDelta));
            while (sum != 0)
            {
                UInt32 e = sum >> 2 & 3;
                UInt32 z;
                Int32 p;
                for (p = n; p > 0; p--)
                {
                    z = v[p - 1];
                    y = unchecked(v[p] -= (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z));
                }
                z = v[n];
                y = unchecked(v[0] -= (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z));
                sum = unchecked(sum - mDelta);
            }
            return v;
        }
        private static UInt32[] ToUInt32Array(Byte[] data, Boolean includeLength)
        {
            Int32 n = (((data.Length & 3) == 0) ? (data.Length >> 2) : ((data.Length >> 2) + 1));
            UInt32[] result;
            if (includeLength)
            {
                result = new UInt32[n + 1];
                result[n] = (UInt32)data.Length;
            }
            else
            {
                result = new UInt32[n];
            }
            n = data.Length;
            for (Int32 i = 0; i < n; i++)
            {
                result[i >> 2] |= (UInt32)data[i] << ((i & 3) << 3);
            }
            return result;
        }
        private static Byte[] ToByteArray(UInt32[] data, Boolean includeLength)
        {
            Int32 n;
            if (includeLength)
            {
                n = (Int32)data[data.Length - 1];
            }
            else
            {
                n = data.Length << 2;
            }
            var result = new Byte[n];
            for (Int32 i = 0; i < n; i++)
            {
                result[i] = (Byte)(data[i >> 2] >> ((i & 3) << 3));
            }
            return result;
        }
    }
}