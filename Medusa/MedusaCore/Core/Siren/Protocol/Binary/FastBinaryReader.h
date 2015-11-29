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
class FastBinaryReader : public BaseBinaryReader < TStream >
{
public:
	static const uint16_t Magic = (uint16_t)SirenProtocol::Fast;

	template<typename TObject>
	bool Run(TObject& obj)
	{
		return DynamicSchemaVisitor::Visit(*this, obj);
	}

	FastBinaryReader(TStream& input)
		: BaseBinaryReader<TStream>(input)
	{
	}

	bool ReadVersion()
	{
		uint16_t magic;
		this->mStream.Read(magic);
		return magic == FastBinaryReader::Magic;
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
		this->mCurrentValueType = outValueType;

		this->mStream.ReadTo(outCount);
	}

	void OnListEnd()
	{
	}

	void OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount)
	{
		this->mStream.ReadTo(outKeyType);
		this->mStream.ReadTo(outValueType);
		this->mCurrentKeyType = outKeyType;
		this->mCurrentValueType = outValueType;
		this->mStream.ReadTo(outCount);
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
			this->mStream.ReadTo(this->mCurrentPropertyId);
			this->mStream.ReadTo(this->mCurrentPropertyType);
			this->mIsPropertyWaiting = true;
		}

		outId = this->mCurrentPropertyId;
		outType = this->mCurrentValueType;
		if (outType == (byte)SirenDataType::StructEnd.ToUInt())
		{
			return -1;
		}

		if (this->mCurrentPropertyId == id)
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

	}
	void OnArrayStep(uint index)
	{
	}
	template<typename TObject>
	void OnValue(TObject& obj)
	{
		this->mStream.ReadTo(obj);
	}

	void OnString(HeapString& obj)
	{
		obj.Clear();
		uint length;
		this->mStream.ReadTo(length);
		obj.ReserveLength(length);
		this->mStream.ReadStringTo(obj);	//include '\0'
	}

	void OnMemoryData(MemoryByteData& obj)
	{
		uint length;
		this->mStream.ReadTo(length);
		obj = MemoryByteData::Alloc(length);
		this->mStream.ReadDataTo(obj);
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
		ushort currentPropertyId;
		byte currentPropertyType;
		this->mStream.ReadTo(currentPropertyId);
		this->mStream.ReadTo(currentPropertyType);

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
				this->mStream.Skip(sizeof(short));
				break;
			case (byte)SirenDataType::Int32.IntValue:
			case (byte)SirenDataType::UInt32.IntValue:
				this->mStream.Skip(sizeof(int));
				break;
			case (byte)SirenDataType::Int64.IntValue:
			case (byte)SirenDataType::UInt64.IntValue:
				this->mStream.Skip(sizeof(int64));
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
				this->mStream.ReadTo(length);	//include '\0'
				this->mStream.Skip(length);
			}
			break;
			case (byte)SirenDataType::Blob.IntValue:
			{
				uint length;
				this->mStream.ReadTo(length);	//include '\0'
				this->mStream.Skip(length);
			}
			break;
			case (byte)SirenDataType::Struct.IntValue:
				SkipProperty();
				break;
			case (byte)SirenDataType::List.IntValue:
			{
				byte valueType = this->mStream.ReadByte();
				uint count;
				this->mStream.ReadTo(count);
				FOR_EACH_SIZE(i, count)
				{
					SkipPropertyHelper(valueType);
				}
			}
			break;
			case (byte)SirenDataType::Dictionary.IntValue:
			{
				byte keyType = this->mStream.ReadByte();
				byte valueType = this->mStream.ReadByte();
				uint count;
				this->mStream.ReadTo(count);
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
