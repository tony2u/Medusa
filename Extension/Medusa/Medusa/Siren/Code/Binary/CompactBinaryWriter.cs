// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using Medusa.Log;
using Medusa.Siren.IO;
using Medusa.Siren.Schema;

namespace Medusa.Siren.Code.Binary
{
    public class CompactBinaryWriter : BaseBinaryWriter
    {
        public CompactBinaryWriter()
            : base()
        {

        }

        public override void OnVersion()
        {
        }

        public override void OnStructBegin()
        {

        }

        public override void OnStructEnd()
        {
            Stream.WriteUInt8((byte)SirenTypeId.Null);
        }

        public override void OnListBegin(SirenTypeId itemDataType, int count)
        {

            Stream.WriteUInt8((byte)itemDataType);
            Stream.WriteVarUInt32((uint)count);

        }

        public override void OnListEnd()
        {

        }

        public override void OnDictionaryBegin(SirenTypeId keyDataType, SirenTypeId valueDataType, int count)
        {
            Stream.WriteUInt8((byte)keyDataType);
            Stream.WriteUInt8((byte)valueDataType);

            Stream.WriteVarUInt32((uint)count);
        }

        public override void OnDictionaryEnd()
        {

        }

        public override void OnFieldBegin(string name, ushort id, SirenTypeId dataType)
        {
            if (id <= 5)
            {
                Stream.WriteUInt8((byte)((uint)dataType | ((uint)id << 5)));
            }
            else if (id <= 0xFF)
            {
                Stream.WriteUInt16((ushort)((uint)dataType | (uint)id << 8 | (0x06 << 5)));
            }
            else
            {
                Stream.WriteUInt8((byte)((uint)dataType | (0x07 << 5)));
                Stream.WriteUInt16(id);
            }


        }

        public override void OnFieldEnd()
        {

        }

        public override void OnString(string obj)
        {
            Stream.WriteVarUInt32((uint)obj.Length + 1);//include '\0'
            Stream.WriteString(obj);
        }

        public override void OnMemoryData(byte[] obj)
        {
            Stream.WriteVarUInt32((uint)obj.Length);
            Stream.WriteBytes(obj);
        }

        public override void OnError()
        {
        }

        public override void OnValue<T>(T obj)
        {
            if (obj is bool)
            {
                Stream.WriteUInt8(Convert.ToByte(obj));
            }
            else if (obj is char)
            {
                Stream.WriteUInt8(Convert.ToByte(obj));
            }
            else if (obj is short)
            {
                Stream.WriteVarUInt16(IntegerHelper.EncodeZigzag(Convert.ToInt16(obj)));
            }
            else if (obj is int)
            {
                Stream.WriteVarUInt32(IntegerHelper.EncodeZigzag(Convert.ToInt32(obj)));
            }
            else if (obj is Int64)
            {
                Stream.WriteVarUInt64(IntegerHelper.EncodeZigzag(Convert.ToInt64(obj)));
            }
            else if (obj is byte)
            {
                Stream.WriteUInt8(Convert.ToByte(obj));
            }
            else if (obj is ushort)
            {
                Stream.WriteVarUInt16(Convert.ToUInt16(obj));
            }
            else if (obj is uint)
            {
                Stream.WriteVarUInt32(Convert.ToUInt32(obj));
            }
            else if (obj is UInt64)
            {
                Stream.WriteVarUInt64(Convert.ToUInt64(obj));
            }
            else if (obj is float)
            {
                Stream.WriteFloat((float)Convert.ToDouble(obj));
            }
            else if (obj is double)
            {
                Stream.WriteDouble(Convert.ToDouble(obj));
            }
            else
            {
                var type = obj.GetType();
                if (type.IsEnum)
                {
                    Stream.WriteVarUInt32(Convert.ToUInt32(obj));
                }
                else
                {
                    Logger.ErrorLine("Invalid value:{0} in type:{1}", obj,obj.GetType());
                }
            }
        }
    }
}
