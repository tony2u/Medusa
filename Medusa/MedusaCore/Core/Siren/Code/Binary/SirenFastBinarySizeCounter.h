// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseSirenBinarySizeCounter.h"
#include "Core/Siren/Code/SirenCoderType.h"
#include "Core/Utility/Utility.h"

MEDUSA_BEGIN;

class SirenFastBinarySizeCounter :public BaseSirenBinarySizeCounter
{
public:
	virtual bool OnValue(bool val)override { mSize += sizeof(val); return true; }
	virtual bool OnValue(char val) override { mSize += sizeof(val); return true; }
	virtual bool OnValue(byte val)override { mSize += sizeof(val); return true; }
	virtual bool OnValue(short val) override { mSize += sizeof(val); return true; }
	virtual bool OnValue(ushort val) override { mSize += sizeof(val); return true; }
	virtual bool OnValue(int32 val)override { mSize += sizeof(val); return true; }
	virtual bool OnValue(uint32 val) override { mSize += sizeof(val); return true; }
	virtual bool OnValue(int64 val)override { mSize += sizeof(val); return true; }
	virtual bool OnValue(uint64 val)override { mSize += sizeof(val); return true; }
	virtual bool OnValue(float val)override { mSize += sizeof(val); return true; }
	virtual bool OnValue(double val)override { mSize += sizeof(val); return true; }
	virtual bool OnValue(const StringRef& val)override
	{
		mSize += sizeof(uint);
		mSize += (uint)val.Length();
		return true; 
	}
	virtual bool OnValue(const MemoryData& val) override
	{
		mSize += sizeof(uint);
		mSize += (uint)val.Size();
		return true;
	}

	virtual bool OnStructEnd()override
	{
		mSize += sizeof(byte);
	}

	virtual bool OnListBegin(byte itemType, uint count)override
	{
		mSize += sizeof(byte);
		mSize += sizeof(uint);
	}


	virtual bool OnDictionaryBegin(byte keyType, byte valueType, uint count)override
	{
		mSize += sizeof(byte);
		mSize += sizeof(byte);
		mSize += sizeof(uint);
	}


	virtual bool OnFieldBegin(const StringRef& name, ushort id, byte type)override
	{
		mSize += sizeof(ushort);
		mSize += sizeof(byte);
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type);
		SirenSchemaSerializer::Visit(*this, obj);
		OnFieldEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		SirenSchemaSerializer::Visit(*this, obj);
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		SirenSchemaSerializer::Visit(*this, obj);
	}
};


MEDUSA_END;
