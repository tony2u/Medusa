// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL
#include "Core/String/HeapString.h"
#include "SqlDefines.h"

MEDUSA_BEGIN;

class SqlException :public std::exception
{
public:
	SqlException(const StringRef& initialMessage);
	SqlException(const StringRef& initialMessage, const int errno, const char *sqlState, const char *errorMessage);
	SqlException(MYSQL *db, const StringRef& initialMessage);
	SqlException(MYSQL_STMT *stmt, const StringRef& initialMessage);
private:
	int mErrno;
	HeapString mSqlState;
	HeapString mErrorMessage;
};
MEDUSA_END;

#endif