// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "Core/Siren/Serialization/ISirenReader.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Database/SqlDefines.h"
#include "Core/Collection/Dictionary.h"
#include "SirenSqlFieldChecker.h"

MEDUSA_BEGIN;

class SirenSqlPreparedReader : public ISirenReader
{
public:
	SirenSqlPreparedReader(NoCompareList<MYSQL_BIND>& binds, const NoCompareList<MYSQL_FIELD*>& fields,uint outputFieldCount)
		:mBinds(binds),
		mFields(fields),
		mOutputFieldCount(outputFieldCount)
	{
		uint fieldCount = (uint)fields.Count();
		FOR_EACH_UINT32(i, fieldCount)
		{
			auto field = fields[i];
			mFieldDict.Add(StringRef(field->name, field->name_length), i);

		}
	}


	virtual bool OnValue(bool& obj) override;
	virtual bool OnValue(char& obj) override;
	virtual bool OnValue(int8& obj) override;
	virtual bool OnValue(uint8& obj) override;
	virtual bool OnValue(int16& obj) override;
	virtual bool OnValue(uint16& obj)override;
	virtual bool OnValue(int32& obj) override;
	virtual bool OnValue(uint32& obj) override;
	virtual bool OnValue(int64& obj)override;
	virtual bool OnValue(uint64& obj)override;
	virtual bool OnValue(float& obj) override;
	virtual bool OnValue(double& obj)override;
	virtual bool OnValue(HeapString& obj) override;
	virtual bool OnValue(MemoryData& obj)override;
	

	virtual bool OnStructEnd()override
	{
		return true;
	}

	virtual bool OnListBegin(byte& outValueType, uint& outCount)override
	{
		return false;
	}

	virtual bool OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount)override
	{
		return false;
	}

	virtual int OnFieldBegin(const StringRef& name, ushort id, byte type, ushort& outId, byte& outType)override
	{
		mFieldIndex = mFieldDict.GetOptional(name, Math::UIntMaxValue);
		if (mFieldIndex == Math::UIntMaxValue)
		{
			return -1;
		}

		SirenSqlFieldChecker::Check(*mFields[mFieldIndex], type);
		return 0;
	}

	virtual bool OnFieldSkip() override
	{
		return true;
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnField(const StringRef& name, ushort id, TObject& outObj)
	{
		ushort outId;
		byte outType;
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type, outId, outType);
		SirenSchemaDeserializer::Visit(*this, outObj);
		OnFieldEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnField(const StringRef& name, ushort id, TObject& outObj)
	{
		SirenSchemaDeserializer::Visit(*this, outObj);
	}
	template<typename TObject>
	void OnStruct(TObject& outObj)
	{
		SirenSchemaDeserializer::Visit(*this, outObj);
	}
protected:
	NoCompareList<MYSQL_BIND>& mBinds;
	const NoCompareList<MYSQL_FIELD*>& mFields;
	uint mFieldIndex = 0;


	Dictionary<StringRef, uint> mFieldDict;	//store ** to quick index
	uint mOutputFieldCount = 0;

};

MEDUSA_END;
#endif