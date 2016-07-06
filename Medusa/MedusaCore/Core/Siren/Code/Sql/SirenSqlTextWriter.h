// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "Core/Siren/Code/SirenCoderType.h"
#include "Core/System/BitConverter.h"
#include "Core/Siren/Serialization/ISirenWriter.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/String/StringParser.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"

MEDUSA_BEGIN;

class SirenSqlTextWriter : public ISirenWriter
{
public:
	SirenSqlTextWriter(IStream& stream)
		:mStream(stream) {}

	virtual bool OnValue(const bool& val) override { mStream.WriteString(val ? "1" : "0", false); return true; }
	virtual bool OnValue(const char& val)override { return OnValueHelper(val); }
	virtual bool OnValue(const int8& val)override { return OnValueHelper(val); }
	virtual bool OnValue(const uint8& val) override { return OnValueHelper(val); }
	virtual bool OnValue(const int16& val) override { return OnValueHelper(val); }
	virtual bool OnValue(const uint16& val) override { return OnValueHelper(val); }
	virtual bool OnValue(const int32& val)override { return OnValueHelper(val); }
	virtual bool OnValue(const uint32& val)override { return OnValueHelper(val); }
	virtual bool OnValue(const int64& val) override { return OnValueHelper(val); }
	virtual bool OnValue(const uint64& val)override { return OnValueHelper(val); }
	virtual bool OnValue(const float& val) override { return OnValueHelper(val); }
	virtual bool OnValue(const double& val) override { return OnValueHelper(val); }
	virtual bool OnValue(const StringRef& val) override { return OnValueHelper(val); }

	virtual bool OnValue(const MemoryData& val) override
	{
		//to hex string
		//like 0x61736466776572
		HeapString str;
		if (!mIsFirstField)
		{
			str = ",0x";
		}
		else
		{
			str = "0x";
			mIsFirstField = false;
		}

		str += StringParser::BytesToHexString<char>(val.Data(), val.Size());
		mStream.WriteString(str, false);

		return true;
	}

	virtual bool OnStructEnd()override
	{
		return true;
	}

	virtual bool OnListBegin(byte itemType, uint count)override
	{
		//not support inner list
		return false;
	}

	virtual bool OnDictionaryBegin(byte keyType, byte valueType, uint count)override
	{
		//not support inner list
		return false;
	}

	virtual bool OnFieldBegin(const StringRef& name, ushort id, byte type)override
	{
		//not support inner struct
		return type!=SirenTypeId::Struct.IntValue;
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type);
		OnValue(obj);
		OnFieldEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		OnValue(obj);
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		SirenSchemaSerializer<true>::Visit(*this, obj);
	}

protected:
	template<typename T>
	bool OnValueHelper(const T& val)
	{
		HeapString str;
		if (!mIsFirstField)
		{
			str.Format(",'{}'", val);
		}
		else
		{
			str.Format("'{}'", val);
			mIsFirstField = false;
		}

		mStream.WriteString(str, false);
		return true;
	}
protected:
	IStream& mStream;
	bool mIsFirstField = true;
};

MEDUSA_END;
#endif