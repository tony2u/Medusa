// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;

class ISirenWriter
{
public:
	virtual ~ISirenWriter() = 0;
public:
	virtual bool OnValue(bool val) { return true; }
	virtual bool OnValue(char val) { return true; }
	virtual bool OnValue(byte val) { return true; }
	virtual bool OnValue(short val) { return true; }
	virtual bool OnValue(ushort val) { return true; }
	virtual bool OnValue(int32 val) { return true; }
	virtual bool OnValue(uint32 val) { return true; }
	virtual bool OnValue(int64 val) { return true; }
	virtual bool OnValue(uint64 val) { return true; }
	virtual bool OnValue(float val) { return true; }
	virtual bool OnValue(double val) { return true; }
	virtual bool OnValue(const StringRef& val) { return true; }
	virtual bool OnValue(const MemoryData& val) { return true; }
	virtual bool OnValue(const SirenObject& val);

	template<typename TObject>
	typename std::enable_if<Compile::TypeTraits<TObject>::IsEnum, bool >::type OnValue(const TObject& obj)
	{
		return OnValue((int32)obj);
	}

	virtual bool OnStructBegin() { return true; }
	virtual bool OnStructEnd() { return true; }

	virtual bool OnListBegin(byte itemType, uint count) { return true; }
	virtual bool OnListItemBegin(uint index) { return true; }
	virtual bool OnListItemEnd(uint index) { return true; }
	virtual bool OnListEnd(uint count) { return true; }

	virtual bool OnDictionaryBegin(byte keyType, byte valueType, uint count) { return true; }
	virtual bool OnDictionaryItemBegin(uint index) { return true; }
	virtual bool OnDictionaryKeyEnd(uint index) { return true; }
	virtual bool OnDictionaryItemEnd(uint index) { return true; }
	virtual bool OnDictionaryEnd(uint count) { return true; }

	virtual bool OnFieldBegin(const StringRef& name, ushort id, byte type) { return true; }
	virtual bool OnFieldEnd() { return true; }

	virtual bool OnError() { return true; }
};

MEDUSA_END;