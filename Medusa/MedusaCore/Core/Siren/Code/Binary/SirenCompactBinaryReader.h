// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseSirenBinaryReader.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"

MEDUSA_BEGIN;

class SirenCompactBinaryReader : public BaseSirenBinaryReader
{
public:
	using BaseSirenBinaryReader::BaseSirenBinaryReader;

	virtual bool OnValue(bool& obj)override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(char& obj) override
	{
		uint8 unsignedValue;
		this->ReadVariableUnsigned(unsignedValue);
		obj = (char)BitConverter::DecodeZigZag(unsignedValue);
		return true;
	}
	virtual bool OnValue(int8& obj) override
	{
		uint8 unsignedValue;
		this->ReadVariableUnsigned(unsignedValue);
		obj = (int8)BitConverter::DecodeZigZag(unsignedValue);
		return true;
	}
	virtual bool OnValue(uint8& obj) override { this->ReadVariableUnsigned(obj); return true; }
	virtual bool OnValue(int16& obj)override
	{
		uint16 unsignedValue;
		this->ReadVariableUnsigned(unsignedValue);
		obj = (short)BitConverter::DecodeZigZag(unsignedValue);
		return true;
	}
	virtual bool OnValue(uint16& obj)override { this->ReadVariableUnsigned(obj); return true; }
	virtual bool OnValue(int32& obj)override
	{
		uint32 unsignedValue;
		this->ReadVariableUnsigned(unsignedValue);
		obj = (int32)BitConverter::DecodeZigZag(unsignedValue);
		return true;
	}
	virtual bool OnValue(uint32& obj) override { this->ReadVariableUnsigned(obj); return true; }
	virtual bool OnValue(int64& obj)override
	{
		uint64 unsignedValue;
		this->ReadVariableUnsigned(unsignedValue);
		obj = (int64)BitConverter::DecodeZigZag(unsignedValue);
		return true;
	}
	virtual bool OnValue(uint64& obj)override { this->ReadVariableUnsigned(obj); return true; }
	virtual bool OnValue(float& obj)override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(double& obj)override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(HeapString& obj)override
	{
		obj.Clear();
		uint length;
		this->ReadVariableUnsigned(length);	//include \0
		obj.ReserveLength(length - 1);
		this->mStream.ReadDataToString(obj, length, true);
		return true;
	}
	virtual bool OnValue(MemoryData& obj)override
	{
		uint length;
		this->ReadVariableUnsigned(length);
		obj = MemoryData::Alloc(length);
		this->mStream.ReadDataTo(obj);
		return true;
	}


	virtual bool OnStructEnd()override
	{
		if (this->mIsFieldWaiting&&this->mCurrentFieldType == (byte)SirenTypeId::Null.ToUInt())
		{
			this->mIsFieldWaiting = false;
		}
		else
		{
			this->mStream.Skip(1);
		}
		return true;
	}

	virtual bool OnListBegin(byte& outValueType, uint& outCount)override
	{
		this->mStream.ReadTo(outValueType);
		this->ReadVariableUnsigned(outCount);

		this->mCurrentValueType = outValueType;
		return true;
	}


	virtual bool OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount)override
	{
		this->mStream.ReadTo(outKeyType);
		this->mStream.ReadTo(outValueType);

		this->ReadVariableUnsigned(outCount);

		this->mCurrentKeyType = outKeyType;
		this->mCurrentValueType = outValueType;
		return true;
	}


	virtual int OnFieldBegin(const StringRef& name, ushort id, byte type, ushort& outId, byte& outType)override
	{
		/*
		All field sorted ascending order by Id
		Current Id == readed Id		match
		Current Id < readed Id		miss
		Current Id > readed Id		unknown filed
		type==Null,current struct reading ends
		*/
		if (!this->mIsFieldWaiting)
		{
			uint8_t raw;
			raw = this->mStream.ReadChar();
			this->mCurrentFieldType = static_cast<uint>(raw & 0x1f);
			this->mCurrentFieldId = static_cast<uint16_t>(raw & (0x07 << 5));

			if (this->mCurrentFieldId == (0x07 << 5))
			{
				this->mStream.ReadTo(this->mCurrentFieldId);
			}
			else if (this->mCurrentFieldId == (0x06 << 5))
			{
				this->mCurrentFieldId = this->mStream.ReadChar();
			}
			else
			{
				this->mCurrentFieldId >>= 5;
			}

			this->mIsFieldWaiting = true;
		}

		outId = this->mCurrentFieldId;
		outType = this->mCurrentFieldType;
		if (outType == (byte)SirenTypeId::Null.ToUInt())
		{
			return -1;
		}

		if (id == this->mCurrentFieldId)
		{
			this->mIsFieldWaiting = false;
			return 0;
		}
		else if (id < this->mCurrentFieldId)
		{
			return -1;
		}

		this->mIsFieldWaiting = false;
		return 1;

	}


	virtual bool OnFieldSkip()override
	{
		return SkipFieldHelper(this->mCurrentFieldType);
	}



	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnField(const StringRef& name, ushort id, TObject& outObj)
	{
		ushort outId;
		byte outType;
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type, outId, outType);
		SirenSchemaDeserializer::Visit(*this, outObj);
		OnFieldEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnField(const StringRef& name, ushort id, TObject& outObj)
	{
		SirenSchemaDeserializer::Visit(*this, outObj);
	}

	template<typename TObject>
	void OnStruct(TObject& outObj)
	{
		SirenSchemaDeserializer::Visit(*this, outObj);
	}

protected:
	bool SkipField()
	{
		uint8_t raw;
		raw = this->mStream.ReadChar();
		byte currentFieldType = static_cast<byte>(raw & 0x1f);
		ushort currentFieldId = static_cast<uint16_t>(raw & (0x07 << 5));

		if (currentFieldId == (0x07 << 5))
		{
			this->mStream.ReadTo(currentFieldId);
		}
		else if (currentFieldId == (0x06 << 5))
		{
			this->mStream.ReadChar();
		}

		return SkipFieldHelper(currentFieldType);
	}


	bool SkipFieldHelper(byte type)
	{
		//STRONG_ENUM_16(SirenFieldType, Bool, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String, Blob, List, Dictionary, Struct));

		switch (type)
		{
		case (byte)SirenTypeId::Bool.IntValue:
			this->mStream.Skip(sizeof(byte));
			break;
		case (byte)SirenTypeId::Int8.IntValue:
		case (byte)SirenTypeId::UInt8.IntValue:
			this->mStream.Skip(sizeof(byte));
			break;
		case (byte)SirenTypeId::Int16.IntValue:
		case (byte)SirenTypeId::UInt16.IntValue:
			this->template SkipVariableUnsigned<ushort>();
			break;
		case (byte)SirenTypeId::Int32.IntValue:
		case (byte)SirenTypeId::UInt32.IntValue:
			this->template SkipVariableUnsigned<uint>();
			break;
		case (byte)SirenTypeId::Int64.IntValue:
		case (byte)SirenTypeId::UInt64.IntValue:
			this->template SkipVariableUnsigned<uint64>();
			break;
		case (byte)SirenTypeId::Float.IntValue:
			this->mStream.Skip(sizeof(float));
			break;
		case (byte)SirenTypeId::Double.IntValue:
			this->mStream.Skip(sizeof(double));
			break;
		case (byte)SirenTypeId::String.IntValue:
		{
			uint length;
			this->ReadVariableUnsigned(length);
			this->mStream.Skip(length);
		}
		break;
		case (byte)SirenTypeId::Blob.IntValue:
		{
			uint length;
			this->ReadVariableUnsigned(length);
			this->mStream.Skip(length);
		}
		break;

		case (byte)SirenTypeId::Struct.IntValue:
			SkipField();
			this->mStream.Skip(1);	//end mask
			break;
		case (byte)SirenTypeId::List.IntValue:
		{
			byte valueType;
			this->mStream.ReadTo(valueType);

			uint count;
			this->ReadVariableUnsigned(count);
			FOR_EACH_SIZE(i, count)
			{
				SkipFieldHelper(valueType);
			}
		}
		break;
		case (byte)SirenTypeId::Dictionary.IntValue:
		{
			byte keyType;
			this->mStream.ReadTo(keyType);
			byte valueType;
			this->mStream.ReadTo(valueType);

			uint count;
			this->ReadVariableUnsigned(count);
			FOR_EACH_SIZE(i, count)
			{
				SkipFieldHelper(keyType);
				SkipFieldHelper(valueType);
			}
		}
		break;
		}
		return true;
	}
};

MEDUSA_END;
