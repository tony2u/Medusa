// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Code/Json/SirenJsonOutputStream.h"
#include "Core/Coder/Crypt/Base91Encoder.h"
#include "Core/Siren/Code/SirenCoderType.h"
#include "CoreLib/Common/rapidjson.h"
#include "Core/Siren/Serialization/ISirenWriter.h"

MEDUSA_BEGIN;

class SirenJsonWriter : protected rapidjson::PrettyWriter < SirenJsonOutputStream >,public ISirenWriter
{
public:

	SirenJsonWriter(IStream& output)
		: mStream(output), rapidjson::PrettyWriter<SirenJsonOutputStream >(mStream)
	{
	}

	
	virtual bool OnStructBegin()override
	{
		this->StartObject();
		return true;
	}

	virtual bool OnStructEnd()override
	{
		this->EndObject();
		return true;
	}

	virtual bool OnListBegin(byte itemType, uint count)override
	{
		this->StartArray();
		return true;
	}


	virtual bool OnListEnd(uint count)override
	{
		this->EndArray();
		return true;
	}

	virtual bool OnDictionaryBegin(byte keyType, byte valueType, uint count)override
	{
		this->StartArray();
		return true;
	}


	virtual bool OnDictionaryEnd(uint count)override
	{
		this->EndArray();
		return true;
	}

	virtual bool OnFieldBegin(const StringRef& name, ushort id, byte type)override
	{
		this->Key(name.c_str(), (rapidjson::SizeType)name.Length());
		return true;
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
	typename std::enable_if<std::is_same<TObject, HeapString>::value >::type OnValue(const TObject& obj)
	{
		this->String(obj.c_str(), obj.Length());
	}


	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, MemoryData>::value >::type OnValue(const TObject& obj)
	{
		Base91Encoder encoder;
		MemoryData resultData=encoder.Code(obj);
		this->String((const char*)resultData.Data(), resultData.Size());
	}
	
	template<typename TObject, bool TWithHeader = true>
	void OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type);
		SirenSchemaSerializer::Visit(*this, obj);
		OnFieldEnd();
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		SirenSchemaSerializer::Visit(*this, obj);
	}
private:
	SirenJsonOutputStream mStream;
};


MEDUSA_END;