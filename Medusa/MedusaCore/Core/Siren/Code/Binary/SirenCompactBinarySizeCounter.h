// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseSirenBinarySizeCounter.h"
#include "Core/Siren/Code/SirenCoderType.h"
#include "Core/System/BitConverter.h"
#include "Core/Siren/Serialization/ISirenSizeCounter.h"

MEDUSA_BEGIN;

class SirenCompactBinarySizeCounter :public BaseSirenBinarySizeCounter
{
public:
	using BaseSirenBinarySizeCounter::BaseSirenBinarySizeCounter;


	virtual bool OnValue(const bool& val) override{ mSize += sizeof(val); return true; }
	virtual bool OnValue(const char& val) override { mSize += CountVariableUnsigned(BitConverter::EncodeZigZag(val)); return true; }
	virtual bool OnValue(const int8& val) override { mSize += CountVariableUnsigned(BitConverter::EncodeZigZag(val)); return true; }
	virtual bool OnValue(const uint8& val) override { mSize += CountVariableUnsigned(val); return true; }
	virtual bool OnValue(const int16& val) override { mSize += CountVariableUnsigned(BitConverter::EncodeZigZag(val)); return true; }
	virtual bool OnValue(const uint16& val) override { mSize += CountVariableUnsigned(val);  return true; }
	virtual bool OnValue(const int32& val) override { mSize += CountVariableUnsigned(BitConverter::EncodeZigZag(val)); return true; }
	virtual bool OnValue(const uint32& val)override { mSize += CountVariableUnsigned(val); return true; }
	virtual bool OnValue(const int64& val) override { mSize += CountVariableUnsigned(BitConverter::EncodeZigZag(val)); return true; }
	virtual bool OnValue(const uint64& val) override { mSize += CountVariableUnsigned(val); return true; }
	virtual bool OnValue(const float& val)override { mSize += sizeof(val); return true; }
	virtual bool OnValue(const double& val)override { mSize += sizeof(val);  return true; }
	virtual bool OnValue(const StringRef& val)override 
	{
		mSize += CountVariableUnsigned(val.Length()+1);
		mSize += (uint32)val.Length()+1;
		return true; 
	}
	virtual bool OnValue(const MemoryData& val)override
	{
		mSize += CountVariableUnsigned(val.Size());
		mSize += (uint32)val.Size();
		return true;
	}


	virtual bool OnStructEnd()override
	{
		mSize += sizeof(byte);
		return true;
	}
	
	virtual bool OnListBegin(byte itemType, uint count)override
	{
		mSize += sizeof(byte);
		mSize += CountVariableUnsigned(count);
		return true;
	}

	virtual bool OnDictionaryBegin(byte keyType, byte valueType, uint count)override
	{
		mSize += sizeof(byte);
		mSize += sizeof(byte);
		mSize += CountVariableUnsigned(count);
		return true;

	}

	
	virtual bool OnFieldBegin(const StringRef& name, ushort id, byte type)override
	{
		if (id <= 5)
		{
			mSize += sizeof(byte);
		}
		else if (id <= 0xff)
		{
			mSize += sizeof(ushort);
		}
		else
		{
			mSize += sizeof(byte);
			mSize += sizeof(ushort);
		}
		return true;

	}

	

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnField(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		OnFieldBegin(name, nameLength, id, Siren::GetDataType<TObject>::Type);
		SirenSchemaSerializer<false>::Visit(*this, obj);
		OnFieldEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnField(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		SirenSchemaSerializer<false>::Visit(*this, obj);
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		SirenSchemaSerializer<false>::Visit(*this, obj);
	}
};


MEDUSA_END;
