// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;

class ISirenReader
{
public:
	virtual ~ISirenReader() = 0;
public:
	virtual bool OnValue(bool& obj) { return true; }
	virtual bool OnValue(char& obj) { return true; }
	virtual bool OnValue(int8& obj) { return true; }
	virtual bool OnValue(uint8& obj) { return true; }
	virtual bool OnValue(int16& obj) { return true; }
	virtual bool OnValue(uint16& obj) { return true; }
	virtual bool OnValue(int32& obj) { return true; }
	virtual bool OnValue(uint32& obj) { return true; }
	virtual bool OnValue(int64& obj) { return true; }
	virtual bool OnValue(uint64& obj) { return true; }
	virtual bool OnValue(float& obj) { return true; }
	virtual bool OnValue(double& obj) { return true; }
	virtual bool OnValue(HeapString& obj) { return true; }
	virtual bool OnValue(MemoryData& obj) { return true; }

	template<typename TObject>
	typename std::enable_if<Compile::TypeTraits<TObject>::IsEnum, bool >::type OnValue(TObject& obj)
	{
		int32 val;
		if (this->OnValue(val))
		{
			obj = (TObject)val;
			return true;
		}
		return false;

	}
	
	virtual bool OnStructBegin() { return true; }
	virtual bool OnStructEnd() { return true; }

	virtual bool OnListBegin(byte& outValueType, uint& outCount) { return true; }
	virtual bool OnListItemBegin(uint index) { return true; }
	virtual bool OnListItemEnd(uint index) { return true; }
	virtual bool OnListEnd() { return true; }

	virtual bool OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount) { return true; }
	virtual bool OnDictionaryItemBegin(uint index) { return true; }
	virtual bool OnDictionaryKeyEnd(uint index) { return true; }
	virtual bool OnDictionaryItemEnd(uint index) { return true; }
	virtual bool OnDictionaryEnd() { return true; }


	virtual int OnFieldBegin(const StringRef& name, ushort id, byte type, ushort& outId, byte& outType) { return 0; }
	virtual bool OnFieldEnd() { return true; }
	virtual bool OnFieldSkip() { return true; }

	virtual bool OnError() { return true; }
	virtual bool IsEnd()const { return false; }


};


MEDUSA_END;