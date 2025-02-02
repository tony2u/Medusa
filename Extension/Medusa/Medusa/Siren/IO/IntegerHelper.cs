// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

using System;
using System.IO;

namespace Medusa.Siren.IO
{
    /// <summary>
    /// Helper methods for encoding and decoding integer values.
    /// </summary>
    internal static class IntegerHelper
    {
        public const int MaxBytesVarInt16 = 3;
        public const int MaxBytesVarInt32 = 5;
        public const int MaxBytesVarInt64 = 10;

        public static int EncodeVarUInt16(byte[] data, ushort value, int index)
        {
            // byte 0
            if (value >= 0x80)
            {
                data[index++] = (byte)(value | 0x80);
                value >>= 7;
                // byte 1
                if (value >= 0x80)
                {
                    data[index++] = (byte)(value | 0x80);
                    value >>= 7;
                }
            }
            // byte 2
            data[index++] = (byte)value;
            return index;
        }

        public static int EncodeVarUInt32(byte[] data, uint value, int index)
        {
            // byte 0
            if (value >= 0x80)
            {
                data[index++] = (byte)(value | 0x80);
                value >>= 7;
                // byte 1
                if (value >= 0x80)
                {
                    data[index++] = (byte)(value | 0x80);
                    value >>= 7;
                    // byte 2
                    if (value >= 0x80)
                    {
                        data[index++] = (byte)(value | 0x80);
                        value >>= 7;
                        // byte 3
                        if (value >= 0x80)
                        {
                            data[index++] = (byte)(value | 0x80);
                            value >>= 7;
                        }
                    }
                }
            }
            // last byte
            data[index++] = (byte)value;
            return index;
        }

        public static int EncodeVarUInt64(byte[] data, ulong value, int index)
        {
            // byte 0
            if (value >= 0x80)
            {
                data[index++] = (byte)(value | 0x80);
                value >>= 7;
                // byte 1
                if (value >= 0x80)
                {
                    data[index++] = (byte)(value | 0x80);
                    value >>= 7;
                    // byte 2
                    if (value >= 0x80)
                    {
                        data[index++] = (byte)(value | 0x80);
                        value >>= 7;
                        // byte 3
                        if (value >= 0x80)
                        {
                            data[index++] = (byte)(value | 0x80);
                            value >>= 7;
                            // byte 4
                            if (value >= 0x80)
                            {
                                data[index++] = (byte)(value | 0x80);
                                value >>= 7;
                                // byte 5
                                if (value >= 0x80)
                                {
                                    data[index++] = (byte)(value | 0x80);
                                    value >>= 7;
                                    // byte 6
                                    if (value >= 0x80)
                                    {
                                        data[index++] = (byte)(value | 0x80);
                                        value >>= 7;
                                        // byte 7
                                        if (value >= 0x80)
                                        {
                                            data[index++] = (byte)(value | 0x80);
                                            value >>= 7;
                                            // byte 8
                                            if (value >= 0x80)
                                            {
                                                data[index++] = (byte)(value | 0x80);
                                                value >>= 7;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // last byte
            data[index++] = (byte)value;
            return index;
        }

        public static ushort DecodeVarUInt16(byte[] data, ref int index)
        {
            var i = index;
            // byte 0
            uint result = data[i++];
            if (0x80u <= result)
            {
                // byte 1
                uint raw = data[i++];
                result = (result & 0x7Fu) | ((raw & 0x7Fu) << 7);
                if (0x80u <= raw)
                {
                    // byte 2
                    raw = data[i++];
                    result |= raw << 14;
                }
            }
            index = i;
            return (ushort) result;
        }

        public static uint DecodeVarUInt32(byte[] data, ref int index)
        {
            var i = index;
            // byte 0
            uint result = data[i++];
            if (0x80u <= result)
            {
                // byte 1
                uint raw = data[i++];
                result = (result & 0x7Fu) | ((raw & 0x7Fu) << 7);
                if (0x80u <= raw)
                {
                    // byte 2
                    raw = data[i++];
                    result |= (raw & 0x7Fu) << 14;
                    if (0x80u <= raw)
                    {
                        // byte 3
                        raw = data[i++];
                        result |= (raw & 0x7Fu) << 21;
                        if (0x80u <= raw)
                        {
                            // byte 4
                            raw = data[i++];
                            result |= raw << 28;
                        }
                    }
                }
            }
            index = i;
            return result;
        }

        public static ulong DecodeVarUInt64(byte[] data, ref int index)
        {
            var i = index;
            // byte 0
            ulong result = data[i++];
            if (0x80u <= result)
            {
                // byte 1
                ulong raw = data[i++];
                result = (result & 0x7Fu) | ((raw & 0x7Fu) << 7);
                if (0x80u <= raw)
                {
                    // byte 2
                    raw = data[i++];
                    result |= (raw & 0x7Fu) << 14;
                    if (0x80u <= raw)
                    {
                        // byte 3
                        raw = data[i++];
                        result |= (raw & 0x7Fu) << 21;
                        if (0x80u <= raw)
                        {
                            // byte 4
                            raw = data[i++];
                            result |= (raw & 0x7Fu) << 28;
                            if (0x80u <= raw)
                            {
                                // byte 5
                                raw = data[i++];
                                result |= (raw & 0x7Fu) << 35;
                                if (0x80u <= raw)
                                {
                                    // byte 6
                                    raw = data[i++];
                                    result |= (raw & 0x7Fu) << 42;
                                    if (0x80u <= raw)
                                    {
                                        // byte 7
                                        raw = data[i++];
                                        result |= (raw & 0x7Fu) << 49;
                                        if (0x80u <= raw)
                                        {
                                            // byte 8
                                            raw = data[i++];
                                            result |= raw << 56;
                                            if (0x80u <= raw)
                                            {
                                                // byte 9
                                                i++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            index = i;
            return result;
        }



        public static void EncodeVarUInt16(Stream stream, ushort value)
        {
            // byte 0
            if (value >= 0x80)
            {
                stream.WriteByte((byte)(value | 0x80));
                value >>= 7;
                // byte 1
                if (value >= 0x80)
                {
                    stream.WriteByte((byte)(value | 0x80));
                    value >>= 7;
                }
            }
            // byte 2
            stream.WriteByte( (byte)value);
        }

        public static void EncodeVarUInt32(Stream stream, uint value)
        {
            // byte 0
            if (value >= 0x80)
            {
                stream.WriteByte( (byte)(value | 0x80));
                value >>= 7;
                // byte 1
                if (value >= 0x80)
                {
                   stream.WriteByte((byte)(value | 0x80));
                    value >>= 7;
                    // byte 2
                    if (value >= 0x80)
                    {
                        stream.WriteByte((byte)(value | 0x80));
                        value >>= 7;
                        // byte 3
                        if (value >= 0x80)
                        {
                            stream.WriteByte( (byte)(value | 0x80));
                            value >>= 7;
                        }
                    }
                }
            }
            // last byte
            stream.WriteByte( (byte)value);
        }

        public static void EncodeVarUInt64(Stream stream, ulong value)
        {
            // byte 0
            if (value >= 0x80)
            {
                stream.WriteByte( (byte)(value | 0x80));
                value >>= 7;
                // byte 1
                if (value >= 0x80)
                {
                    stream.WriteByte( (byte)(value | 0x80));
                    value >>= 7;
                    // byte 2
                    if (value >= 0x80)
                    {
                        stream.WriteByte( (byte)(value | 0x80));
                        value >>= 7;
                        // byte 3
                        if (value >= 0x80)
                        {
                            stream.WriteByte( (byte)(value | 0x80));
                            value >>= 7;
                            // byte 4
                            if (value >= 0x80)
                            {
                                stream.WriteByte( (byte)(value | 0x80));
                                value >>= 7;
                                // byte 5
                                if (value >= 0x80)
                                {
                                    stream.WriteByte( (byte)(value | 0x80));
                                    value >>= 7;
                                    // byte 6
                                    if (value >= 0x80)
                                    {
                                        stream.WriteByte( (byte)(value | 0x80));
                                        value >>= 7;
                                        // byte 7
                                        if (value >= 0x80)
                                        {
                                            stream.WriteByte( (byte)(value | 0x80));
                                            value >>= 7;
                                            // byte 8
                                            if (value >= 0x80)
                                            {
                                                stream.WriteByte( (byte)(value | 0x80));
                                                value >>= 7;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // last byte
            stream.WriteByte((byte)value);
        }

        public static ushort DecodeVarUInt16(Stream stream)
        {
            // byte 0
            uint result = (uint)stream.ReadByte();
            if (0x80u <= result)
            {
                // byte 1
                uint raw =  (uint)stream.ReadByte();
                result = (result & 0x7Fu) | ((raw & 0x7Fu) << 7);
                if (0x80u <= raw)
                {
                    // byte 2
                    raw =  (uint)stream.ReadByte();
                    result |= raw << 14;
                }
            }
            return (ushort)result;
        }

        public static uint DecodeVarUInt32(Stream stream)
        {
            // byte 0
            uint result =  (uint)stream.ReadByte();
            if (0x80u <= result)
            {
                // byte 1
                uint raw =  (uint)stream.ReadByte();
                result = (result & 0x7Fu) | ((raw & 0x7Fu) << 7);
                if (0x80u <= raw)
                {
                    // byte 2
                    raw =  (uint)stream.ReadByte();
                    result |= (raw & 0x7Fu) << 14;
                    if (0x80u <= raw)
                    {
                        // byte 3
                        raw =  (uint)stream.ReadByte();
                        result |= (raw & 0x7Fu) << 21;
                        if (0x80u <= raw)
                        {
                            // byte 4
                            raw =  (uint)stream.ReadByte();
                            result |= raw << 28;
                        }
                    }
                }
            }
            return result;
        }

        public static ulong DecodeVarUInt64(Stream stream)
        {
            // byte 0
            ulong result =  (uint)stream.ReadByte();
            if (0x80u <= result)
            {
                // byte 1
                ulong raw =  (uint)stream.ReadByte();
                result = (result & 0x7Fu) | ((raw & 0x7Fu) << 7);
                if (0x80u <= raw)
                {
                    // byte 2
                    raw =  (uint)stream.ReadByte();
                    result |= (raw & 0x7Fu) << 14;
                    if (0x80u <= raw)
                    {
                        // byte 3
                        raw =  (uint)stream.ReadByte();
                        result |= (raw & 0x7Fu) << 21;
                        if (0x80u <= raw)
                        {
                            // byte 4
                            raw =  (uint)stream.ReadByte();
                            result |= (raw & 0x7Fu) << 28;
                            if (0x80u <= raw)
                            {
                                // byte 5
                                raw =  (uint)stream.ReadByte();
                                result |= (raw & 0x7Fu) << 35;
                                if (0x80u <= raw)
                                {
                                    // byte 6
                                    raw =  (uint)stream.ReadByte();
                                    result |= (raw & 0x7Fu) << 42;
                                    if (0x80u <= raw)
                                    {
                                        // byte 7
                                        raw =  (uint)stream.ReadByte();
                                        result |= (raw & 0x7Fu) << 49;
                                        if (0x80u <= raw)
                                        {
                                            // byte 8
                                            raw =  (uint)stream.ReadByte();
                                            result |= raw << 56;
                                            if (0x80u <= raw)
                                            {
                                                // byte 9
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return result;
        }



        public static UInt16 EncodeZigzag(Int16 value)
        {
            return (UInt16)((value << 1) ^ (value >> (sizeof(Int16) * 8 - 1)));
        }

        public static UInt32 EncodeZigzag(Int32 value)
        {
            return (UInt32)((value << 1) ^ (value >> (sizeof(Int32) * 8 - 1)));
        }

        public static UInt64 EncodeZigzag(Int64 value)
        {
            return (UInt64)((value << 1) ^ (value >> (sizeof(Int64) * 8 - 1)));
        }

        public static Int16 DecodeZigzag(UInt16 value)
        {
            return (Int16)((value >> 1) ^ (-(value & 1)));
        }

        public static Int32 DecodeZigzag(UInt32 value)
        {
            return (Int32)((value >> 1) ^ (-(value & 1)));
        }

        public static Int64 DecodeZigzag(UInt64 value)
        {
            return (Int64)((value >> 1) ^ (UInt64)(-(Int64)(value & 1)));
        }
    }
}
