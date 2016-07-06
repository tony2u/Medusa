// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL

#include "SqlPrepareCommand.h"
#include "Core/Database/SqlConnection.h"

MEDUSA_BEGIN;

SqlPrepareCommand::SqlPrepareCommand(SqlConnection* connection /*= nullptr*/, const StringRef& name /*= StringRef::Empty*/, const StringRef& statement /*= StringRef::Empty*/, bool checkStatementChanged /*= false*/)
	:SqlCommand(connection), 
	mName(name),
	mStatement(statement),
	mCheckStatementChanged(checkStatementChanged)
{

}

SqlPrepareCommand::~SqlPrepareCommand(void)
{
}

bool SqlPrepareCommand::OnExecute()
{
	auto statement=mConnection->Prepare(mName, mStatement, mCheckStatementChanged);
	mResult.set_value(statement);
	
	return true;
}

MEDUSA_END;
#endif