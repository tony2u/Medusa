// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Protocol/Json/JsonOutputStream.h"
#include "Core/Coder/Crypt/Base91Encoder.h"
#include "Core/Siren/SirenProtocol.h"
#include "Core/Siren/Reflection/StaticSchemaVisitor.h"
#include "CoreLib/Common/rapidjson.h"

MEDUSA_SIREN_BEGIN;

template <typename TStream>
class JsonWriter : protected rapidjson::PrettyWriter < JsonOutputStream<TStream> >
{
public:
	static const uint16_t Magic = (uint16_t)SirenProtocol::Json;

	JsonWriter(TStream& output)
		: mStream(output), rapidjson::PrettyWriter<JsonOutputStream<TStream> >(mStream)
	{
	}

	template<typename TObject>
	void Run(const TObject& obj)
	{
		StaticSchemaVisitor::Visit(*this, obj);
	}

	void WriteVersion()
	{

	}

	void OnStructBegin()
	{
		this->StartObject();

	}

	void OnStructEnd()
	{
		this->EndObject();
	}

	void OnListBegin(byte itemType, uint count)
	{
		this->StartArray();
	}


	void OnListEnd()
	{
		this->EndArray();
	}

	void OnDictionaryBegin(byte keyType, byte valueType, uint count)
	{
		this->StartArray();
	}


	void OnDictionaryEnd()
	{
		this->EndArray();
	}

	void OnPropertyBegin(const char* name, ushort nameLength, ushort id, byte type)
	{
		this->Key(name, nameLength);
	}

	void OnPropertyEnd()
	{

	}

	template<typename TObject>
	typename std::enable_if<std::is_floating_point<TObject>::value >::type OnValue(const TObject& obj)
	{
		this->Double(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, bool>::value >::type OnValue(const TObject& obj)
	{
		this->Bool(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, char>::value >::type OnValue(const TObject& obj)
	{
		this->Int(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, short>::value >::type OnValue(const TObject& obj)
	{
		this->Int(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, int>::value >::type OnValue(const TObject& obj)
	{
		this->Int(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, int64>::value >::type OnValue(const TObject& obj)
	{
		this->Int64(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, byte>::value >::type OnValue(const TObject& obj)
	{
		this->Uint(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, ushort>::value >::type OnValue(const TObject& obj)
	{
		this->Uint(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, uint>::value >::type OnValue(const TObject& obj)
	{
		this->Uint(obj);
	}
	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, uint64>::value >::type OnValue(const TObject& obj)
	{
		this->Uint64(obj);
	}

	template<typename TObject>
	typename std::enable_if<SirenTraits<TObject>::IsEnum>::type OnValue(const TObject& obj)
	{
		this->Uint((uint)obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, HeapString>::value >::type OnValue(const TObject& obj)
	{
		this->String(obj.c_str(), obj.Length());
	}


	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, MemoryByteData>::value >::type OnValue(const TObject& obj)
	{
		Base91Encoder encoder;
		MemoryByteData resultData=encoder.Code(obj);
		this->String((const char*)resultData.Data(), resultData.Size());
	}

	void OnError()
	{

	}

	
	template<typename TObject, bool TWithHeader = true>
	void OnProperty(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		OnPropertyBegin(name, nameLength, id, Siren::GetDataType<TObject>::Type);
		StaticSchemaVisitor::Visit(*this, obj);
		OnPropertyEnd();
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		StaticSchemaVisitor::Visit(*this, obj);
	}
private:
	JsonOutputStream<TStream> mStream;
};


MEDUSA_SIREN_END;