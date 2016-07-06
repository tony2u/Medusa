// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using Medusa.Log;
using Medusa.Siren.IO;
using Medusa.Siren.Schema;

namespace Medusa.Siren.Code.Binary
{
    public class CompactBinaryReader : BaseBinaryReader
    {
       
        public CompactBinaryReader()
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
            if (mIsPropertyWaiting && mCurrentPropertyType == (byte)Schema.SirenTypeId.Null)
            {
                mIsPropertyWaiting = false;
            }
            else
            {
                Stream.SkipBytes(1);
            }
        }

        public override void OnListBegin(out SirenTypeId dataType,out int count)
        {
            dataType = (SirenTypeId)Stream.ReadUInt8();
            count = (int)Stream.ReadVarUInt32();

        }

        public override void OnListEnd()
        {

        }

        public override void OnDictionaryBegin(out SirenTypeId keyDataType, out SirenTypeId valueDataType,out int count)
        {
            keyDataType = (SirenTypeId)Stream.ReadUInt8();
            valueDataType = (SirenTypeId)Stream.ReadUInt8();

            count = (int)Stream.ReadVarUInt32();
        }

        public override void OnDictionaryEnd()
        {

        }

        public override int OnFieldBegin(string name, ushort id, SirenTypeId dataType, out ushort outId, out SirenTypeId outDataType)
        {
            if (!mIsPropertyWaiting)
            {
                ushort tempId;
                uint raw = Stream.ReadUInt8();
                var type = (SirenTypeId)(raw & 0x1f);
                raw >>= 5;

                if (raw < 6)
                {
                    tempId = (ushort)raw;
                }
                else if (raw == 6)
                {
                    tempId = Stream.ReadUInt8();
                }
                else
                {
                    tempId = Stream.ReadUInt16();
                }

                mCurrentPropertyId = tempId;
                mCurrentPropertyType = type;

                mIsPropertyWaiting = true;
            }

            outId = mCurrentPropertyId;
            outDataType = mCurrentPropertyType;

            if (id == mCurrentPropertyId)
            {
                mIsPropertyWaiting = false;
                return 0;
            }
            else if (id < mCurrentPropertyId)
            {
                return -1;
            }
            mIsPropertyWaiting = false;
            return 1;

        }

        public override void OnFieldEnd()
        {

        }

        public override void OnFieldSkip(SirenTypeId dataType)
        {
            SkipPropertyHelper(dataType);
        }


        public override object OnValue(Type type)
        {
            if (type == typeof(bool))
            {
                return Stream.ReadUInt8() == 1;
            }
            else if (type == typeof(char))
            {
                return (char)Stream.ReadUInt8();
            }
            else if (type == typeof(short))
            {
                return IntegerHelper.DecodeZigzag(Stream.ReadVarUInt16());
            }
            else if (type == typeof(int))
            {
                return IntegerHelper.DecodeZigzag(Stream.ReadVarUInt32());
            }
            else if (type == typeof(Int64))
            {
                return IntegerHelper.DecodeZigzag(Stream.ReadVarUInt64());
            }
            else if (type == typeof(byte))
            {
                return Stream.ReadUInt8();
            }
            else if (type == typeof(ushort))
            {
                return Stream.ReadVarUInt16();
            }
            else if (type == typeof(uint))
            {
                return Stream.ReadVarUInt32();
            }
            else if (type == typeof(UInt64))
            {
                return Stream.ReadVarUInt64();
            }
            else if (type == typeof(float))
            {
                return Stream.ReadFloat();
            }
            else if (type == typeof(double))
            {
                return Stream.ReadDouble();
            }
            else
            {
                if (type.IsEnum)
                {
                    return Stream.ReadVarUInt32();
                }
                else
                {
                    Logger.ErrorLine("Invalid value type:{0}", type);
                }
            }

            return null;
        }

        public override string OnString()
        {
            uint length = Stream.ReadVarUInt32();
            return Stream.ReadString((int)length);
        }

        public override byte[] OnMemoryData()
        {
            uint length = Stream.ReadVarUInt32();
            return Stream.ReadBytes((int)length);
        }

        public override void OnError()
        {
        }

        void SkipProperty()
        {
            uint raw = Stream.ReadUInt8();
            var type = (SirenTypeId)(raw & 0x1f);
            raw >>= 5;

            if (raw < 6)
            {
                
            }
            else if (raw == 6)
            {
                Stream.ReadUInt8();
            }
            else
            {
                Stream.ReadUInt16();
            }


            SkipPropertyHelper(type);
        }


        void SkipPropertyHelper(SirenTypeId type)
	{
		switch (type)
		{
			case SirenTypeId.Bool:
				Stream.SkipBytes(sizeof(byte));
				break;
			case SirenTypeId.Int8:
			case SirenTypeId.UInt8:
				Stream.SkipBytes(sizeof(byte));
				break;
			case SirenTypeId.Int16:
			case SirenTypeId.UInt16:
		        Stream.ReadVarUInt16();
				break;
			case SirenTypeId.Int32:
			case SirenTypeId.UInt32:
                Stream.ReadVarUInt32();
				break;
			case SirenTypeId.Int64:
			case SirenTypeId.UInt64:
                Stream.ReadVarUInt64();
				break;
			case SirenTypeId.Float:
				Stream.SkipBytes(sizeof(float));
				break;
			case SirenTypeId.Double:
				Stream.SkipBytes(sizeof(double));
				break;
			case SirenTypeId.String:
			{
				uint length= Stream.ReadVarUInt32();
				Stream.SkipBytes((int)length);
			}
			break;
			case SirenTypeId.Blob:
			{
				uint length= Stream.ReadVarUInt32();
				Stream.SkipBytes((int)length);
			}
			break;

			case SirenTypeId.Struct:
				SkipProperty();
				break;
			case SirenTypeId.List:
			{
				SirenTypeId valueType=(SirenTypeId)Stream.ReadUInt8();
				uint count= Stream.ReadVarUInt32();
			    for (int i = 0; i < count; i++)
			    {
					SkipPropertyHelper(valueType);
			    }
			}
			break;
			case SirenTypeId.Dictionary:
			{
				SirenTypeId keyType=(SirenTypeId)Stream.ReadUInt8();
				SirenTypeId valueType=(SirenTypeId)Stream.ReadUInt8();
                uint count= Stream.ReadVarUInt32();
			    for (int i = 0; i < count; i++)
			    {
					SkipPropertyHelper(keyType);
					SkipPropertyHelper(valueType);

			    }
			}
			break;
		}
	}
    }
}
