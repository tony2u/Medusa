// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL

#include "SqlTextExecuteCommand.h"
#include "Core/Database/SqlTextStatement.h"
#include "Core/Database/SqlConnection.h"

MEDUSA_BEGIN;



SqlTextExecuteCommand::SqlTextExecuteCommand(SqlConnection* connection /*= nullptr*/, const Share<SqlTextStatement>& statement /*= nullptr*/)
	:SqlCommand(connection),mStatement(statement)
{

}

SqlTextExecuteCommand::~SqlTextExecuteCommand(void)
{
	
}

bool SqlTextExecuteCommand::OnExecute()
{
	auto result= mStatement->Execute(mConnection->Sql());
	mResult.set_value(result);
	
	return true;
}

MEDUSA_END;
#endif