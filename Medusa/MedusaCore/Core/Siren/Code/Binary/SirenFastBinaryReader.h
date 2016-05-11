// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseSirenBinaryReader.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"
MEDUSA_BEGIN;

class SirenFastBinaryReader : public BaseSirenBinaryReader
{
public:
	using BaseSirenBinaryReader::BaseSirenBinaryReader;

	virtual bool OnValue(bool& obj) override{ this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(char& obj) override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(byte& obj) override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(short& obj) override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(ushort& obj)override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(int32& obj) override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(uint32& obj) override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(int64& obj)override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(uint64& obj)override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(float& obj) override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(double& obj)override { this->mStream.ReadTo(obj); return true; }
	virtual bool OnValue(HeapString& obj) override 
	{
		obj.Clear();
		uint length;
		this->mStream.ReadTo(length);
		obj.ReserveLength(length);
		this->mStream.ReadDataToString(obj,length);

		return true; 
	}

	virtual bool OnValue(MemoryData& obj)override 
	{
		uint length;
		this->mStream.ReadTo(length);
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
		this->mCurrentValueType = outValueType;

		this->mStream.ReadTo(outCount);
		return true;
	}

	virtual bool OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount)override
	{
		this->mStream.ReadTo(outKeyType);
		this->mStream.ReadTo(outValueType);
		this->mCurrentKeyType = outKeyType;
		this->mCurrentValueType = outValueType;
		this->mStream.ReadTo(outCount);
		return true;
	}

	virtual int OnFieldBegin(const StringRef& name, ushort id, byte type, ushort& outId, byte& outType)override
	{

		/*
		All field sorted asdending order by Id
		Current Id == readed Id		match
		Current Id < readed Id		miss
		Current Id > readed Id		unknown filed
		type==Null,current struct reading ends
		*/
		if (!this->mIsFieldWaiting)
		{
			this->mStream.ReadTo(this->mCurrentFieldId);
			this->mStream.ReadTo(this->mCurrentFieldType);
			this->mIsFieldWaiting = true;
		}

		outId = this->mCurrentFieldId;
		outType = this->mCurrentValueType;
		if (outType == (byte)SirenTypeId::Null.ToUInt())
		{
			return -1;
		}

		if (this->mCurrentFieldId == id)
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

	
	template<typename TObject>
	bool OnValue(TObject& obj)
	{
		this->mStream.ReadTo(obj);
		return true;
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
		ushort currentFieldId;
		byte currentFieldType;
		this->mStream.ReadTo(currentFieldId);
		this->mStream.ReadTo(currentFieldType);

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
				this->mStream.Skip(sizeof(short));
				break;
			case (byte)SirenTypeId::Int32.IntValue:
			case (byte)SirenTypeId::UInt32.IntValue:
				this->mStream.Skip(sizeof(int));
				break;
			case (byte)SirenTypeId::Int64.IntValue:
			case (byte)SirenTypeId::UInt64.IntValue:
				this->mStream.Skip(sizeof(int64));
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
				this->mStream.ReadTo(length);	//include '\0'
				this->mStream.Skip(length);
			}
			break;
			case (byte)SirenTypeId::Blob.IntValue:
			{
				uint length;
				this->mStream.ReadTo(length);	//include '\0'
				this->mStream.Skip(length);
			}
			break;
			case (byte)SirenTypeId::Struct.IntValue:
				SkipField();
				break;
			case (byte)SirenTypeId::List.IntValue:
			{
				byte valueType = (byte)this->mStream.ReadChar();
				uint count;
				this->mStream.ReadTo(count);
				FOR_EACH_SIZE(i, count)
				{
					SkipFieldHelper(valueType);
				}
			}
			break;
			case (byte)SirenTypeId::Dictionary.IntValue:
			{
				byte keyType = (byte)this->mStream.ReadChar();
				byte valueType = (byte)this->mStream.ReadChar();
				uint count;
				this->mStream.ReadTo(count);
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
