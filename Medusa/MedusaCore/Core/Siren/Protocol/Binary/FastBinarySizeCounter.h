// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseBinarySizeCounter.h"
#include "Core/Siren/SirenProtocol.h"
#include "Core/Utility/Utility.h"
#include "Core/Siren/Reflection/StaticSchemaVisitor.h"
MEDUSA_SIREN_BEGIN;

class FastBinarySizeCounter :public BaseBinarySizeCounter
{
public:
	template<typename TObject>
	bool Run(const TObject& obj)
	{
		mSize = 0;
		return StaticSchemaVisitor::Visit(*this, obj);
	}

	void OnStructBegin()
	{

	}

	void OnStructEnd()
	{
		mSize += sizeof(byte);

	}

	void OnListBegin(byte itemType, uint count)
	{
		mSize += sizeof(byte);
		mSize += sizeof(uint);
	}

	void OnListEnd()
	{
	}

	void OnDictionaryBegin(byte keyType, byte valueType, uint count)
	{
		mSize += sizeof(byte);
		mSize += sizeof(byte);
		mSize += sizeof(uint);
	}

	void OnDictionaryEnd()
	{

	}

	void OnPropertyBegin(const char* name, ushort nameLength, ushort id, byte type)
	{
		mSize += sizeof(ushort);
		mSize += sizeof(byte);
	}

	void OnPropertyEnd()
	{

	}

	template<typename TObject>
	typename std::enable_if<!std::is_same<TObject, HeapString>::value&&!std::is_same<TObject, MemoryByteData>::value >::type OnValue(const TObject& obj)
	{
		mSize += sizeof(TObject);

	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, HeapString>::value >::type OnValue(const TObject&  obj)
	{
		mSize += sizeof(uint);
		mSize += obj.Length() + 1;//include '\0'
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, MemoryByteData>::value >::type OnValue(const TObject&  obj)
	{
		mSize += sizeof(uint);
		mSize += obj.Size();
	}


	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnProperty(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		OnPropertyBegin(name, nameLength, id, Siren::GetDataType<TObject>::Type);
		StaticSchemaVisitor::Visit(*this, obj);
		OnPropertyEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnProperty(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		StaticSchemaVisitor::Visit(*this, obj);
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		StaticSchemaVisitor::Visit(*this, obj);
	}
};


MEDUSA_SIREN_END;
