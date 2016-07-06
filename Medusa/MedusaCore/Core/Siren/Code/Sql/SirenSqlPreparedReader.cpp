// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL

#include "SirenSqlPreparedReader.h"
#include "Core/Database/SqlBinder.h"

MEDUSA_BEGIN;

template<typename T>
static bool OnValueHelper(T& obj, uint fieldIndex, NoCompareList<MYSQL_BIND>& binds, const NoCompareList<MYSQL_FIELD*>& fields, uint outputFieldCount)
{
	Log::AssertOrThrow<SqlException>(fieldIndex < fields.Count(), "Not enough result filed count:{} for output:{}", fields.Count(), outputFieldCount);

	NoCompareList<MYSQL_BIND> tempBinds;
	tempBinds.ForceSetItems(binds.MutableItems() + fieldIndex);
	tempBinds.ForceSetSize(binds.Size() - fieldIndex);
	tempBinds.ForceSetCount(binds.Count() - fieldIndex);

	NoCompareList<MYSQL_FIELD*> tempFields;
	tempFields.ForceSetItems((MYSQL_FIELD**)fields.Items() + fieldIndex);
	tempFields.ForceSetSize(fields.Size() - fieldIndex);
	tempFields.ForceSetCount(fields.Count() - fieldIndex);

	SqlBinder::Detail::BindResultHelper<0, T, false>::Run(obj, tempBinds, tempFields);

	tempBinds.ForceSetItems(nullptr);
	tempFields.ForceSetItems(nullptr);

	return true;
}


bool SirenSqlPreparedReader::OnValue(bool& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}

bool SirenSqlPreparedReader::OnValue(char& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(int8& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}

bool SirenSqlPreparedReader::OnValue(uint8& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(int16& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(uint16& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(int& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(uint& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(int64& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(uint64& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(float& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(double& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(HeapString& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}
bool SirenSqlPreparedReader::OnValue(MemoryData& obj)
{
	return OnValueHelper(obj, mFieldIndex, mBinds, mFields, mOutputFieldCount);
}

MEDUSA_END;
#endif