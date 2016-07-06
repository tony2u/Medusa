// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#ifdef MEDUSA_WINDOWS
#include <WinSock2.h>
#endif

#include "CoreLib/win/mysql/mysql.h"
#include "CoreLib/win/mysql/mysql_time.h"

MEDUSA_BEGIN;


enum class SqlClientFlags
{
	None = 0,
	MulitipleStatements = CLIENT_MULTI_STATEMENTS,
	MulitipleResults = CLIENT_MULTI_RESULTS,


};


MEDUSA_END;

#endif