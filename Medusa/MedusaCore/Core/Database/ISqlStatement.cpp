// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL
#include "ISqlStatement.h"
#include "SqlConnection.h"

MEDUSA_BEGIN;

ISqlStatement::ISqlStatement(const StringRef& statement, const StringRef& name /*= StringRef::Empty*/)
	:ISharableThreadSafeWithName(name),
	mStatement(statement)
{

}

ISqlStatement::~ISqlStatement(void)
{

}


MEDUSA_END;
#endif