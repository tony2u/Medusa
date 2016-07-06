// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL

#include "SirenSqlPreparedWriter.h"
#include "Core/Database/SqlBinder.h"

MEDUSA_BEGIN;

template<typename T>
static bool OnValueHelper(NoCompareList<MYSQL_BIND>& allBinds,uint index,const T& val)
{
	NoCompareList<MYSQL_BIND> binds;
	binds.ForceSetItems(allBinds.MutableItems() + index);
	binds.ForceSetSize(allBinds.Size()-index);
	binds.ForceSetCount(allBinds.Count()- index);

	SqlBinder::BindParameters<0>(binds, val);

	binds.ForceSetItems(nullptr);
	return true;
}


bool SirenSqlPreparedWriter::OnValue(const bool& val)
{
	return OnValueHelper(mBinds,mIndex++,val);
}
bool SirenSqlPreparedWriter::OnValue(const char& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const int8& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}


bool SirenSqlPreparedWriter::OnValue(const uint8& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}
bool SirenSqlPreparedWriter::OnValue(const int16& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const uint16& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const int& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const uint& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const int64& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const uint64& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const float& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const double& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const StringRef&  val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}

bool SirenSqlPreparedWriter::OnValue(const MemoryData& val)
{
	return OnValueHelper(mBinds, mIndex++, val);
}


MEDUSA_END;
#endif