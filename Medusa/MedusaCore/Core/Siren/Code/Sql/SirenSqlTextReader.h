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
#include "SirenSqlFieldChecker.h"


MEDUSA_BEGIN;

class SirenSqlTextReader : public ISirenReader
{
public:
	SirenSqlTextReader(MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount, uint outputFieldCount)
		:mRow(row),
		mRowLengths(rowLengths),
		mFields(fields),
		mFieldCount(fieldCount),
		mOutputFieldCount(outputFieldCount)
	{
		FOR_EACH_UINT32(i, fieldCount)
		{
			const MYSQL_FIELD& field = mFields[i];
			mFieldDict.Add(StringRef(field.name, field.name_length), i);
		}
	}


	virtual bool OnValue(bool& obj) override
	{
		Log::AssertOrThrow<SqlException>(mFieldIndex < mFieldCount, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		StringRef val(mRow[mFieldIndex], (size_t)mRowLengths[mFieldIndex]);
		obj = val == "1";
		return true;
	}
	virtual bool OnValue(char& obj) override { OnValueHelper(obj); return true; }
	virtual bool OnValue(int8& obj) override { OnValueHelper(obj); return true; }
	virtual bool OnValue(uint8& obj) override { OnValueHelper(obj); return true; }
	virtual bool OnValue(int16& obj) override { OnValueHelper(obj); return true; }
	virtual bool OnValue(uint16& obj)override { OnValueHelper(obj); return true; }
	virtual bool OnValue(int32& obj) override { OnValueHelper(obj); return true; }
	virtual bool OnValue(uint32& obj) override { OnValueHelper(obj); return true; }
	virtual bool OnValue(int64& obj)override { OnValueHelper(obj); return true; }
	virtual bool OnValue(uint64& obj)override { OnValueHelper(obj); return true; }
	virtual bool OnValue(float& obj) override { OnValueHelper(obj); return true; }
	virtual bool OnValue(double& obj)override { OnValueHelper(obj); return true; }

	virtual bool OnValue(HeapString& obj) override
	{
		obj.Clear();
		Log::AssertOrThrow<SqlException>(mFieldIndex < mFieldCount, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		StringRef val(mRow[mFieldIndex], (size_t)mRowLengths[mFieldIndex]);
		obj = val;

		return true;
	}

	virtual bool OnValue(MemoryData& obj)override
	{
		Log::AssertOrThrow<SqlException>(mFieldIndex < mFieldCount, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		obj = MemoryData::CopyFrom((const byte*)mRow[mFieldIndex], (size_t)mRowLengths[mFieldIndex]);
		return true;
	}


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

		SirenSqlFieldChecker::Check(mFields[mFieldIndex], type);
		return 0;
	}

	virtual bool OnFieldSkip() override
	{
		return true;
	}


protected:
	template<typename T>
	bool OnValueHelper(T& obj)
	{
		Log::AssertOrThrow<SqlException>(mFieldIndex < mFieldCount, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		StringRef val(mRow[mFieldIndex], (size_t)mRowLengths[mFieldIndex]);
		obj = StringParser::StringTo<T>(val);
		return true;
	}


protected:
	MYSQL_ROW mRow = nullptr;
	ulong* mRowLengths = nullptr;
	const MYSQL_FIELD* mFields = nullptr;
	uint mFieldCount = 0;
	uint mFieldIndex = 0;
	Dictionary<StringRef, uint> mFieldDict;
	uint mOutputFieldCount = 0;

};

MEDUSA_END;
#endif