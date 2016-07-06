// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL
#include "SqlException.h"
MEDUSA_BEGIN;

SqlException::SqlException(const StringRef& initialMessage)
	:std::exception(initialMessage.c_str())
{
}


SqlException::SqlException(const StringRef& initialMessage, const int errno, const char *sqlState, const char *errorMessage) 
	:std::exception(initialMessage.c_str())
{
	mErrno = errno;
	mSqlState = sqlState;
	mErrorMessage = errorMessage;
}


SqlException::SqlException(MYSQL *db, const StringRef& initialMessage)
	:std::exception(initialMessage.c_str())
{
	mErrno = mysql_errno(db);
	mErrorMessage = mysql_error(db);
	mSqlState = mysql_sqlstate(db);
}

SqlException::SqlException(MYSQL_STMT *stmt, const StringRef& initialMessage) 
	:std::exception(initialMessage.c_str())
{
	mErrno = mysql_stmt_errno(stmt);
	mErrorMessage = mysql_stmt_error(stmt);
	mSqlState = mysql_stmt_sqlstate(stmt);
}



MEDUSA_END;
#endif