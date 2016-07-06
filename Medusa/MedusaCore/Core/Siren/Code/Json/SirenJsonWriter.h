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

	virtual bool OnValue(const float& obj)override
	{
		this->Double(obj);
		return true;
	}
	virtual bool OnValue(const double& obj)override
	{
		this->Double(obj);
		return true;
	}

	virtual bool OnValue(const bool& obj)override
	{
		this->Bool(obj);
		return true;
	}

	virtual bool OnValue(const int8& obj)override
	{
		this->Int(obj);
		return true;
	}

	virtual bool OnValue(const char& obj)override
	{
		this->Int(obj);
		return true;
	}

	virtual bool OnValue(const int16& obj)override
	{
		this->Int(obj);
		return true;
	}

	virtual bool OnValue(const int& obj)override
	{
		this->Int(obj);
		return true;
	}

	virtual bool OnValue(const int64& obj)override
	{
		this->Int64(obj);
		return true;
	}

	virtual bool OnValue(const uint8& obj)override
	{
		this->Uint(obj);
		return true;
	}

	virtual bool OnValue(const uint16& obj)override
	{
		this->Uint(obj);
		return true;
	}

	virtual bool OnValue(const uint& obj)override
	{
		this->Uint(obj);
		return true;
	}
	virtual bool OnValue(const uint64& obj)override
	{
		this->Uint64(obj);
		return true;
	}

	virtual bool OnValue(const StringRef& obj)override
	{
		this->String(obj.c_str(), (rapidjson::SizeType)obj.Length());
		return true;
	}


	virtual bool OnValue(const MemoryData& obj)override
	{
		Base91Encoder encoder;
		MemoryData resultData=encoder.Code(obj);
		this->String((const char*)resultData.Data(), (rapidjson::SizeType)resultData.Size());
		return true;
	}
	
	template<typename TObject, bool TWithHeader = true>
	void OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type);
		SirenSchemaSerializer<false>::Visit(*this, obj);
		OnFieldEnd();
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		SirenSchemaSerializer<false>::Visit(*this, obj);
	}
private:
	SirenJsonOutputStream mStream;
};


MEDUSA_END;