// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseBinaryWriter.h"
#include "Core/Siren/SirenProtocol.h"
#include "Core/Utility/Utility.h"
#include "Core/Siren/Reflection/StaticSchemaVisitor.h"
#include "FastBinarySizeCounter.h"

MEDUSA_SIREN_BEGIN;

template <typename TStream>
class FastBinaryWriter : public BaseBinaryWriter < TStream >
{
public:
	static const uint16_t Magic = (uint16_t)SirenProtocol::Fast;
	typedef FastBinarySizeCounter SizeCounter;

	FastBinaryWriter(TStream& output)
		: BaseBinaryWriter<TStream>(output)
	{
	}

	template<typename TObject>
	bool Run(const TObject& obj)
	{
		SizeCounter sizeCounter;
		RETURN_FALSE_IF_FALSE(sizeCounter.Run(obj));
		this->mStream.ReserveSize(sizeCounter.Size());
		return StaticSchemaVisitor::Visit(*this, obj);
	}

	void WriteVersion()
	{
		this->mStream.Write(Magic);
	}

	void OnStructBegin()
	{

	}

	void OnStructEnd()
	{
		this->mStream.Write((byte)SirenDataType::StructEnd.ToUInt());
	}

	void OnListBegin(byte itemType, uint count)
	{
		this->mStream.WriteByte(itemType);
		this->mStream.Write(count);
	}

	void OnListEnd()
	{
	}

	
	void OnDictionaryBegin(byte keyType, byte valueType, uint count)
	{
		this->mStream.WriteByte(keyType);
		this->mStream.WriteByte(valueType);
		this->mStream.Write(count);
	}

	void OnDictionaryEnd()
	{

	}

	void OnPropertyBegin(const char* name, ushort nameLength, ushort id, byte type)
	{
		this->mStream.Write(id);
		this->mStream.Write(type);
	}

	void OnPropertyEnd()
	{

	}

	template<typename TObject>
	typename std::enable_if<!std::is_same<TObject, HeapString>::value&&!std::is_same<TObject, MemoryByteData>::value >::type OnValue(const TObject& obj)
	{
		this->mStream.Write(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, HeapString>::value >::type OnValue(const TObject&  obj)
	{
		this->mStream.Write((uint)obj.Length());
		this->mStream.WriteString(obj);	//include '\0'
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, MemoryByteData>::value >::type OnValue(const TObject&  obj)
	{
		this->mStream.Write((uint)obj.Size());
		this->mStream.WriteData(obj);
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnProperty(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		OnPropertyBegin(name, nameLength, id, Siren::GetDataType<TObject>::Type);
		OnValue(obj);
		OnPropertyEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnProperty(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		OnValue(obj);
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		StaticSchemaVisitor::Visit(*this, obj);
	}
};


MEDUSA_SIREN_END;
