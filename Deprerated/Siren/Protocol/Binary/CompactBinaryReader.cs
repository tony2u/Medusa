// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Siren.IO;

namespace Siren.Protocol.Binary
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
        }

        public override void OnListBegin(out SirenFieldType dataType,out int count)
        {
            dataType = (SirenFieldType)Stream.ReadUInt8();
            count = (int)Stream.ReadVarUInt32();

        }

        public override void OnListEnd()
        {

        }

        public override void OnDictionaryBegin(out SirenFieldType keyDataType, out SirenFieldType valueDataType,out int count)
        {
            keyDataType = (SirenFieldType)Stream.ReadUInt8();
            valueDataType = (SirenFieldType)Stream.ReadUInt8();

            count = (int)Stream.ReadVarUInt32();
        }

        public override void OnDictionaryEnd()
        {

        }

        public override int OnPropertyBegin(string name, ushort id, SirenFieldType dataType, out ushort outId, out SirenFieldType outDataType)
        {
            if (!mIsPropertyWaiting)
            {
                ushort tempId;
                uint raw = Stream.ReadUInt8();
                var type = (SirenFieldType)(raw & 0x1f);
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

        public override void OnPropertyEnd()
        {

        }

        public override void OnPropertySkip(SirenFieldType dataType)
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
                    Console.WriteLine("Invalid value type:{0}", type);
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
            var type = (SirenFieldType)(raw & 0x1f);
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


        void SkipPropertyHelper(SirenFieldType type)
	{
		switch (type)
		{
			case SirenFieldType.Bool:
				Stream.SkipBytes(sizeof(byte));
				break;
			case SirenFieldType.Int8:
			case SirenFieldType.UInt8:
				Stream.SkipBytes(sizeof(byte));
				break;
			case SirenFieldType.Int16:
			case SirenFieldType.UInt16:
		        Stream.ReadVarUInt16();
				break;
			case SirenFieldType.Int32:
			case SirenFieldType.UInt32:
                Stream.ReadVarUInt32();
				break;
			case SirenFieldType.Int64:
			case SirenFieldType.UInt64:
                Stream.ReadVarUInt64();
				break;
			case SirenFieldType.Float:
				Stream.SkipBytes(sizeof(float));
				break;
			case SirenFieldType.Double:
				Stream.SkipBytes(sizeof(double));
				break;
			case SirenFieldType.String:
			{
				uint length= Stream.ReadVarUInt32();
				Stream.SkipBytes((int)length);
			}
			break;
			case SirenFieldType.Blob:
			{
				uint length= Stream.ReadVarUInt32();
				Stream.SkipBytes((int)length);
			}
			break;

			case SirenFieldType.Struct:
				SkipProperty();
				break;
			case SirenFieldType.List:
			{
				SirenFieldType valueType=(SirenFieldType)Stream.ReadUInt8();
				uint count= Stream.ReadVarUInt32();
			    for (int i = 0; i < count; i++)
			    {
					SkipPropertyHelper(valueType);
			    }
			}
			break;
			case SirenFieldType.Dictionary:
			{
				SirenFieldType keyType=(SirenFieldType)Stream.ReadUInt8();
				SirenFieldType valueType=(SirenFieldType)Stream.ReadUInt8();
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
