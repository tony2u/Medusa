// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseBinaryReader.h"
#include "Core/Siren/Reflection/DynamicSchemaVisitor.h"
#include "Core/Siren/SirenDataType.h"

MEDUSA_SIREN_BEGIN;

template <typename TStream>
class CompactBinaryReader : public BaseBinaryReader < TStream >
{
public:
	static const uint16_t Magic = (uint16_t)SirenProtocol::Compact;

	template<typename TObject>
	bool Run(TObject& obj)
	{
		return DynamicSchemaVisitor::Visit(*this, obj);
	}

	CompactBinaryReader(TStream& input)
		: BaseBinaryReader<TStream>(input)
	{
	}

	bool ReadVersion()
	{
		uint16_t magic;
		this->mStream.Read(magic);
		return magic == CompactBinaryReader::Magic;
	}

	void OnStructBegin()
	{


	}

	void OnStructEnd()
	{
		if (this->mIsPropertyWaiting&&this->mCurrentPropertyType == (byte)SirenDataType::StructEnd.ToUInt())
		{
			this->mIsPropertyWaiting = false;
		}
		else
		{
			this->mStream.Skip(1);
		}

	}

	void OnListBegin(byte& outValueType, uint& outCount)
	{
		this->mStream.ReadTo(outValueType);
		this->ReadVariableUnsigned(outCount);

		this->mCurrentValueType = outValueType;
	}

	void OnListEnd()
	{
	}

	void OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount)
	{
		this->mStream.ReadTo(outKeyType);
		this->mStream.ReadTo(outValueType);

		this->ReadVariableUnsigned(outCount);

		this->mCurrentKeyType = outKeyType;
		this->mCurrentValueType = outValueType;
	}

	void OnDictionaryEnd()
	{

	}

	int OnPropertyBegin(const char* name, ushort nameLength, ushort id, byte type, ushort& outId, byte& outType)
	{
		/*
		All field sorted asdending order by Id
		Current Id == readed Id		match
		Current Id < readed Id		miss
		Current Id > readed Id		unknown filed
		type==StructEnd,current struct reading ends
		*/
		if (!this->mIsPropertyWaiting)
		{
			uint8_t raw;
			raw = this->mStream.ReadChar();
			this->mCurrentPropertyType = static_cast<uint>(raw & 0x1f);
			this->mCurrentPropertyId = static_cast<uint16_t>(raw & (0x07 << 5));

			if (this->mCurrentPropertyId == (0x07 << 5))
			{
				this->mStream.ReadTo(this->mCurrentPropertyId);
			}
			else if (this->mCurrentPropertyId == (0x06 << 5))
			{
				this->mCurrentPropertyId = this->mStream.ReadChar();
			}
			else
			{
				this->mCurrentPropertyId >>= 5;
			}

			this->mIsPropertyWaiting = true;
		}

		outId = this->mCurrentPropertyId;
		outType = this->mCurrentPropertyType;
		if (outType == (byte)SirenDataType::StructEnd.ToUInt())
		{
			return -1;
		}

		if (id == this->mCurrentPropertyId)
		{
			this->mIsPropertyWaiting = false;
			return 0;
		}
		else if (id < this->mCurrentPropertyId)
		{
			return -1;
		}

		this->mIsPropertyWaiting = false;
		return 1;

	}

	void OnPropertyEnd()
	{

	}

	void OnPropertySkip()
	{
		SkipPropertyHelper(this->mCurrentPropertyType);
	}

	template<typename TObject>
	typename std::enable_if<std::is_floating_point<TObject>::value >::type OnValue(TObject& obj)
	{
		this->mStream.ReadTo(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, bool>::value >::type OnValue(TObject& obj)
	{
		this->mStream.ReadTo(obj);
	}

	template<typename TObject>
	typename std::enable_if<!std::is_same<TObject, bool>::value&&std::is_unsigned<TObject>::value >::type OnValue(TObject& obj)
	{
		this->ReadVariableUnsigned(obj);
	}

	template<typename TObject>
	typename std::enable_if<Compile::TypeTraits<TObject>::IsSignedInt >::type OnValue(TObject& obj)
	{
		typename std::make_unsigned<TObject>::type unsignedValue;
		this->ReadVariableUnsigned(unsignedValue);

		obj = (TObject)Utility::DecodeZigZag(unsignedValue);
	}

	template<typename TObject>
	typename std::enable_if<SirenTraits<TObject>::IsEnum >::type OnValue(TObject& obj)
	{
		uint val;
		this->ReadVariableUnsigned(val);
		obj = (TObject)val;
	}

	void OnString(HeapString& obj)
	{
		obj.Clear();
		uint length;
		this->ReadVariableUnsigned(length);
		obj.ReserveLength(length - 1);
		this->mStream.ReadStringTo(obj);	//include '\0'
	}

	void OnMemoryData(MemoryByteData& obj)
	{
		uint length;
		this->ReadVariableUnsigned(length);
		obj = MemoryByteData::Alloc(length);
		this->mStream.ReadDataTo(obj);
	}
	void OnArrayStep(uint index)
	{
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnProperty(const char* name, ushort nameLength, ushort id, TObject& outObj)
	{
		ushort outId;
		byte outType;
		OnPropertyBegin(name, nameLength, id, Siren::GetDataType<TObject>::Type, outId, outType);
		DynamicSchemaVisitor::Visit(*this, outObj);
		OnPropertyEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnProperty(const char* name, ushort nameLength, ushort id, TObject& outObj)
	{
		DynamicSchemaVisitor::Visit(*this, outObj);
	}

	template<typename TObject>
	void OnStruct(TObject& outObj)
	{
		DynamicSchemaVisitor::Visit(*this, outObj);
	}

protected:
	void SkipProperty()
	{
		uint8_t raw;
		raw = this->mStream.ReadChar();
		byte currentPropertyType = static_cast<byte>(raw & 0x1f);
		ushort currentPropertyId = static_cast<uint16_t>(raw & (0x07 << 5));

		if (currentPropertyId == (0x07 << 5))
		{
			this->mStream.ReadTo(currentPropertyId);
		}
		else if (currentPropertyId == (0x06 << 5))
		{
			this->mStream.ReadChar();
		}

		SkipPropertyHelper(currentPropertyType);
	}


	void SkipPropertyHelper(byte type)
	{
		//STRONG_ENUM_16(SirenDataType, Bool, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String, Blob, List, Dictionary, Struct));

		switch (type)
		{
			case (byte)SirenDataType::Bool.IntValue:
				this->mStream.Skip(sizeof(byte));
				break;
			case (byte)SirenDataType::Int8.IntValue:
			case (byte)SirenDataType::UInt8.IntValue:
				this->mStream.Skip(sizeof(byte));
				break;
			case (byte)SirenDataType::Int16.IntValue:
			case (byte)SirenDataType::UInt16.IntValue:
				this->template SkipVariableUnsigned<ushort>();
				break;
			case (byte)SirenDataType::Int32.IntValue:
			case (byte)SirenDataType::UInt32.IntValue:
				this->template SkipVariableUnsigned<uint>();
				break;
			case (byte)SirenDataType::Int64.IntValue:
			case (byte)SirenDataType::UInt64.IntValue:
				this->template SkipVariableUnsigned<uint64>();
				break;
			case (byte)SirenDataType::Float.IntValue:
				this->mStream.Skip(sizeof(float));
				break;
			case (byte)SirenDataType::Double.IntValue:
				this->mStream.Skip(sizeof(double));
				break;
			case (byte)SirenDataType::String.IntValue:
			{
				uint length;
				this->ReadVariableUnsigned(length);	//include '\0'
				this->mStream.Skip(length);
			}
			break;
			case (byte)SirenDataType::Blob.IntValue:
			{
				uint length;
				this->ReadVariableUnsigned(length);	//include '\0'
				this->mStream.Skip(length);
			}
			break;

			case (byte)SirenDataType::Struct.IntValue:
				SkipProperty();
				this->mStream.Skip(1);	//end mask
				break;
			case (byte)SirenDataType::List.IntValue:
			{
				byte valueType;
				this->mStream.ReadTo(valueType);

				uint count;
				this->ReadVariableUnsigned(count);
				FOR_EACH_SIZE(i, count)
				{
					SkipPropertyHelper(valueType);
				}
			}
			break;
			case (byte)SirenDataType::Dictionary.IntValue:
			{
				byte keyType;
				this->mStream.ReadTo(keyType);
				byte valueType;
				this->mStream.ReadTo(valueType);

				uint count;
				this->ReadVariableUnsigned(count);
				FOR_EACH_SIZE(i, count)
				{
					SkipPropertyHelper(keyType);
					SkipPropertyHelper(valueType);
				}
			}
			break;
		}
	}
};

MEDUSA_SIREN_END;
