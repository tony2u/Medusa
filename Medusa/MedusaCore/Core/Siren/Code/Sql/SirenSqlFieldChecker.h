// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "Core/Siren/Serialization/ISirenWriter.h"
#include "Core/Database/SqlDefines.h"
#include "Core/Log/Log.h"
#include "Core/Database/SqlException.h"

MEDUSA_BEGIN;

class SirenSqlFieldChecker
{
public:
	SirenSqlFieldChecker(const MYSQL_FIELD* fields, uint fieldCount,uint outputFieldCount)
		:mFields(fields), mFieldCount(fieldCount),mOutputFieldCount(outputFieldCount)
	{
		mFieldsEnd = fields + fieldCount;
		FOR_EACH_SIZE(i, fieldCount)
		{
			const MYSQL_FIELD& field = mFields[i];
			mFieldDict.Add(StringRef(field.name, field.name_length), &field);
		}
	}

	template<typename T>
	bool OnValue();

	template<>
	bool OnValue<bool>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_BIT, "Invalid field type:{} to bool", mCurrentField->type);
		return true;
	}

	template<>
	bool OnValue<char>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField != nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_TINY && ((mCurrentField->flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to char", mCurrentField->type);
		return true;

	}

	template<>
	bool OnValue<int8>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_TINY && ((mCurrentField->flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to char", mCurrentField->type);
		return true;

	}

	template<>
	bool OnValue<uint8>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_TINY && ((mCurrentField->flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to byte", mCurrentField->type);
		return true;


	}
	template<>
	bool OnValue<int16>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_SHORT && ((mCurrentField->flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to short", mCurrentField->type);
		return true;


	}
	template<>
	bool OnValue<uint16>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_SHORT && ((mCurrentField->flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to ushort", mCurrentField->type);
		return true;

	}
	template<>
	bool OnValue<int>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_LONG && ((mCurrentField->flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to int", mCurrentField->type);
		return true;

	}
	template<>
	bool OnValue<uint>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_LONG && ((mCurrentField->flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to uint", mCurrentField->type);
		return true;

	}
	template<>
	bool OnValue<int64>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_LONGLONG && ((mCurrentField->flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to int64", mCurrentField->type);
		return true;


	}
	template<>
	bool OnValue<uint64>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_LONGLONG && ((mCurrentField->flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to uint64", mCurrentField->type);
		return true;

	}
	template<>
	bool OnValue<float>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_FLOAT, "Invalid field type:{} to float", mCurrentField->type);
		return true;

	}
	template<>
	bool OnValue<double>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_DOUBLE, "Invalid field type:{} to double", mCurrentField->type);
		return true;

	}
	template<>
	bool OnValue<HeapString>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_VAR_STRING ||
			mCurrentField->type == MYSQL_TYPE_STRING ||
			mCurrentField->type == MYSQL_TYPE_VARCHAR, "Invalid field type:{} to HeapString", mCurrentField->type);
		return true;

	}
	template<>
	bool OnValue<MemoryData>()
	{
		Log::AssertOrThrow<SqlException>(mCurrentField!=nullptr, "Not enough result filed count:{} for output:{}", mFieldCount, mOutputFieldCount);
		Log::AssertOrThrow<SqlException>(mCurrentField->type == MYSQL_TYPE_BLOB ||
			mCurrentField->type == MYSQL_TYPE_TINY_BLOB ||
			mCurrentField->type == MYSQL_TYPE_MEDIUM_BLOB ||
			mCurrentField->type == MYSQL_TYPE_LONG_BLOB, "Invalid field type:{} to MemoryData", mCurrentField->type);
		return true;

	}

	template<typename T>
	bool OnStructBegin()
	{
		return true;
	}

	template<typename T>
	bool OnStructEnd()
	{
		return true;
	}

	template<typename T>
	bool OnListBegin()
	{
		return false;
	}

	template<typename T>
	bool OnListEnd()
	{
		return true;
	}

	template<typename T>
	bool OnDictionaryBegin()
	{
		return false;
	}

	template<typename T>
	bool OnDictionaryEnd()
	{
		return true;
	}

	template<typename T>
	bool OnFieldBegin(const StringRef& name, ushort id, byte type)
	{
		mCurrentField = mFieldDict.GetOptional(name, nullptr);
		if (mCurrentField == nullptr)
		{
			return false;
		}

		Check(*mCurrentField, type);
		return true;
	}

	template<typename T>
	bool OnFieldEnd()
	{
		return true;
	}

	static void Check(const MYSQL_FIELD& field, byte type)
	{
		SirenTypeId id = (SirenTypeId)type;
		switch (id.ToInt())
		{
		case SirenTypeId::Bool.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_BIT, "Invalid field type:{} to bool", field.type);
			break;
		case SirenTypeId::Int8.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_TINY && ((field.flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to char", field.type);
			break;
		case SirenTypeId::UInt8.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_TINY && ((field.flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to byte", field.type);

			break;
		case SirenTypeId::Int16.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_SHORT && ((field.flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to short", field.type);

			break;
		case SirenTypeId::UInt16.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_SHORT && ((field.flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to ushort", field.type);

			break;
		case SirenTypeId::Int32.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_LONG && ((field.flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to int", field.type);

			break;
		case SirenTypeId::UInt32.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_LONG && ((field.flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to uint", field.type);

			break;
		case SirenTypeId::Int64.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_LONGLONG && ((field.flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to int64", field.type);

			break;
		case SirenTypeId::UInt64.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_LONGLONG && ((field.flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to uint64", field.type);

			break;
		case SirenTypeId::Float.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_FLOAT, "Invalid field type:{} to float", field.type);

			break;
		case SirenTypeId::Double.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_DOUBLE, "Invalid field type:{} to double", field.type);

			break;
		case SirenTypeId::String.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_VAR_STRING ||
				field.type == MYSQL_TYPE_STRING ||
				field.type == MYSQL_TYPE_VARCHAR, "Invalid field type:{} to HeapString", field.type);
			break;
		case SirenTypeId::Blob.IntValue:
			Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_BLOB ||
				field.type == MYSQL_TYPE_TINY_BLOB ||
				field.type == MYSQL_TYPE_MEDIUM_BLOB ||
				field.type == MYSQL_TYPE_LONG_BLOB, "Invalid field type:{} to MemoryData", field.type);
			break;
		default:
			break;
		}

	}
private:
	const MYSQL_FIELD* mFields;
	const MYSQL_FIELD* mFieldsEnd;
	uint mFieldCount=0;
	uint mOutputFieldCount=0;


	const MYSQL_FIELD* mCurrentField = nullptr;
	Dictionary<StringRef, const MYSQL_FIELD*> mFieldDict;
};


MEDUSA_END;
#endif
