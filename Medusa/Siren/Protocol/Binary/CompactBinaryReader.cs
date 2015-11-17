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

        public override void OnListBegin(out SirenDataType dataType,out int count)
        {
            dataType = (SirenDataType)Stream.ReadUInt8();
            count = (int)Stream.ReadVarUInt32();

        }

        public override void OnListEnd()
        {

        }

        public override void OnDictionaryBegin(out SirenDataType keyDataType, out SirenDataType valueDataType,out int count)
        {
            keyDataType = (SirenDataType)Stream.ReadUInt8();
            valueDataType = (SirenDataType)Stream.ReadUInt8();

            count = (int)Stream.ReadVarUInt32();
        }

        public override void OnDictionaryEnd()
        {

        }

        public override int OnPropertyBegin(string name, ushort id, SirenDataType dataType, out ushort outId, out SirenDataType outDataType)
        {
            if (!mIsPropertyWaiting)
            {
                ushort tempId;
                uint raw = Stream.ReadUInt8();
                var type = (SirenDataType)(raw & 0x1f);
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

        public override void OnPropertySkip(SirenDataType dataType)
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
            var type = (SirenDataType)(raw & 0x1f);
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


        void SkipPropertyHelper(SirenDataType type)
	{
		switch (type)
		{
			case SirenDataType.Bool:
				Stream.SkipBytes(sizeof(byte));
				break;
			case SirenDataType.Int8:
			case SirenDataType.UInt8:
				Stream.SkipBytes(sizeof(byte));
				break;
			case SirenDataType.Int16:
			case SirenDataType.UInt16:
		        Stream.ReadVarUInt16();
				break;
			case SirenDataType.Int32:
			case SirenDataType.UInt32:
                Stream.ReadVarUInt32();
				break;
			case SirenDataType.Int64:
			case SirenDataType.UInt64:
                Stream.ReadVarUInt64();
				break;
			case SirenDataType.Float:
				Stream.SkipBytes(sizeof(float));
				break;
			case SirenDataType.Double:
				Stream.SkipBytes(sizeof(double));
				break;
			case SirenDataType.String:
			{
				uint length= Stream.ReadVarUInt32();
				Stream.SkipBytes((int)length);
			}
			break;
			case SirenDataType.Blob:
			{
				uint length= Stream.ReadVarUInt32();
				Stream.SkipBytes((int)length);
			}
			break;

			case SirenDataType.Struct:
				SkipProperty();
				break;
			case SirenDataType.List:
			{
				SirenDataType valueType=(SirenDataType)Stream.ReadUInt8();
				uint count= Stream.ReadVarUInt32();
			    for (int i = 0; i < count; i++)
			    {
					SkipPropertyHelper(valueType);
			    }
			}
			break;
			case SirenDataType.Dictionary:
			{
				SirenDataType keyType=(SirenDataType)Stream.ReadUInt8();
				SirenDataType valueType=(SirenDataType)Stream.ReadUInt8();
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
