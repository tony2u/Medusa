// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL
#include "SqlConnection.h"
#include "Core/Log/Log.h"
#include "SqlException.h"


MEDUSA_BEGIN;

SqlConnection::SqlConnection()
{
	if ((mSql = mysql_init(NULL)) == NULL)
	{
		throw SqlException("Error trying to initialize MYSQL database", 0, "-----", "insufficient memory");
	}

}

SqlConnection::SqlConnection(const SqlConectionInfo& info)
	:mInfo(info)
{
	mIsConnected = false;
	mAutoCommit = true;

	if ((mSql = mysql_init(NULL)) == NULL)
	{
		throw SqlException("Error trying to initialize MYSQL database", 0, "-----", "insufficient memory");
	}
}



SqlConnection::~SqlConnection()
{
	mPreparedStatements.Clear();

	mysql_thread_end();
	if (mSql != nullptr)
	{
		mysql_close(mSql);
		mSql = nullptr;
	}
}

void SqlConnection::EnableAutoCommit(bool val)
{
	RETURN_IF_EQUAL(this->mAutoCommit, val);
	mAutoCommit = val;

	if (mysql_autocommit(mSql, mAutoCommit) != 0) 
	{
		throw SqlException(mSql, "Error in Database::Autocommit");
	}
}

bool SqlConnection::Connect()
{
	if (mInfo.Host().IsEmpty())
	{
		if (mysql_real_connect(mSql, NULL, NULL, NULL, mInfo.Database().c_str(), 0, NULL, 0) == NULL)
		{
			throw SqlException(mSql, "Error in Database::Connect");
		}
	}
	else
	{
		if (mysql_real_connect(mSql, mInfo.Host().c_str(), mInfo.User().c_str(), mInfo.Password().c_str(), mInfo.Database().c_str(), mInfo.Port(), mInfo.UnixSocket(), (ulong)mInfo.ClientFlags()) == NULL)
		{
			throw SqlException(mSql, "Error in Database::Connect");
		}
	}
	mIsConnected = true;

	if (mysql_set_character_set(mSql, "utf8") != 0)
	{
		throw SqlException(mSql, "Error in DatabaseConnect");
	}
	return mIsConnected;
}

void SqlConnection::StartTransaction() 
{
	if (mysql_query(mSql, "START TRANSACTION") != 0) {
		throw SqlException(mSql, "Error in Database::StartTransaction");
	}
}

void SqlConnection::Commit() 
{
	if (mysql_query(mSql, "COMMIT") != 0) 
	{
		throw SqlException(mSql, "Error in Database::Commit");
	}
}

void SqlConnection::Rollback() 
{
	if (mysql_query(mSql, "ROLLBACK") != 0) 
	{
		throw SqlException(mSql, "Error in Database::Rollback");
	}
}

void SqlConnection::UseDatabase(const StringRef& dbName) 
{
	if (mysql_select_db(mSql, dbName.c_str()) != 0) 
	{
		throw SqlException(mSql, "Error in Database::UseDatabase");
	}
}


my_ulonglong SqlConnection::Execute(const StringRef& statement)const
{
	if (mysql_query(mSql, statement.c_str()) != 0) 
	{
		throw SqlException(mSql, "Error in Database::Execute - query");
	}

	MYSQL_RES *res = mysql_store_result(mSql);
	if (res != NULL) {
		mysql_free_result(res);
		throw SqlException("Error in Database::Execute", 0, "----", "statements passed to Execute should never return results.");
	}

	return mysql_affected_rows(mSql);
}

MEDUSA_END;
#endif