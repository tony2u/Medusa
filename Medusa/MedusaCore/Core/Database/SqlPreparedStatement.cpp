// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL
#include "SqlPreparedStatement.h"
#include "SqlException.h"
#include "Core/Database/SqlConnection.h"

MEDUSA_BEGIN;



SqlPreparedStatement::SqlPreparedStatement(const StringRef& statement, const StringRef& name /*= StringRef::Empty*/, SqlConnection* connection /*= nullptr*/)
	:ISqlStatement(statement,name),
	mConnection(connection)
{

}

SqlPreparedStatement::~SqlPreparedStatement()
{
	if (mResultMetadata != nullptr)
	{
		mysql_free_result(mResultMetadata);
		mResultMetadata = nullptr;
	}
	mResultFields.Clear();

	if (mSTMT != nullptr)
	{
		mysql_stmt_free_result(mSTMT);
		mysql_stmt_close(mSTMT);
		mSTMT = nullptr;
	}

}

MYSQL* SqlPreparedStatement::Sql() const
{
	return mConnection->Sql();
}

bool SqlPreparedStatement::Prepare()
{
	auto sql = Sql();
	mSTMT = mysql_stmt_init(Sql());
	if (mSTMT == nullptr)
	{
		throw SqlException(sql, "Error in SqlPreparedStatement::mysql_stmt_init");
	}

	if (mysql_stmt_prepare(mSTMT, mStatement.c_str(), (ulong)mStatement.Length()) != 0)
	{
		SqlException e(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_prepare");
		mysql_stmt_free_result(mSTMT);
		mysql_stmt_close(mSTMT);
		throw e;
	}

	mParamterCount = mysql_stmt_param_count(mSTMT);
	mResultCount = mysql_stmt_field_count(mSTMT);
	if (mResultCount!=0)
	{
		if ((mResultMetadata = mysql_stmt_result_metadata(mSTMT)) == NULL)
		{
			throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_result_metadata");
		}

		MYSQL_FIELD* field = nullptr;
		while ((field = mysql_fetch_field(mResultMetadata)) != nullptr)
		{
			mResultFields.Add(field);
		}
	}

	
	
	return true;
}


void SqlPreparedStatement::RefetchTruncatedColumns(NoCompareList<MYSQL_BIND>& resultBinds)const
{
	// Find which buffers were too small, expand them and refetch
	
	FOR_EACH_UINT32(i, mResultCount)
	{
		MYSQL_BIND& bind = resultBinds[i];
		ulong alreadyRetrieved = bind.buffer_length;

		if (bind.length != nullptr&&alreadyRetrieved < *bind.length)
		{
			if (bind.buffer_type == MYSQL_TYPE_BLOB ||
				bind.buffer_type == MYSQL_TYPE_TINY_BLOB ||
				bind.buffer_type == MYSQL_TYPE_MEDIUM_BLOB ||
				bind.buffer_type == MYSQL_TYPE_LONG_BLOB)
			{
				MemoryData& data = *(MemoryData*)bind.extension;
				data.Realloc(*bind.length);
				bind.buffer = data.MutableData() + alreadyRetrieved;
				bind.buffer_length = (ulong)data.Size() - alreadyRetrieved;
				const int status = mysql_stmt_fetch_column(mSTMT, &bind, i, alreadyRetrieved);
				if (0 != status)
				{
					throw SqlException(mSTMT, mysql_stmt_error(mSTMT));
				}

			}
			else if (bind.buffer_type == MYSQL_TYPE_VAR_STRING ||
				bind.buffer_type == MYSQL_TYPE_STRING ||
				bind.buffer_type == MYSQL_TYPE_VARCHAR)
			{
				HeapString& str = *(HeapString*)bind.extension;
				str.ReserveLength(*bind.length);
				bind.buffer = str.MutableBuffer() + alreadyRetrieved;
				bind.buffer_length = (ulong)str.Size() - alreadyRetrieved;
				const int status = mysql_stmt_fetch_column(mSTMT, &bind, i, alreadyRetrieved);
				if (0 != status)
				{
					throw SqlException(mSTMT, mysql_stmt_error(mSTMT));
				}
				str.ForceSetLength(*bind.length);
			}

		}

	}
}

MEDUSA_END;

#endif