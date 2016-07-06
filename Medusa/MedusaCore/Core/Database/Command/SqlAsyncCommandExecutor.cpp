// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL

#include "SqlAsyncCommandExecutor.h"

MEDUSA_BEGIN;

SqlAsyncCommandExecutor::SqlAsyncCommandExecutor()
{
	
}

SqlAsyncCommandExecutor::SqlAsyncCommandExecutor(const SqlConectionInfo& info)
	:mConnection(info)
{

}

SqlAsyncCommandExecutor::~SqlAsyncCommandExecutor(void)
{
	
}


bool SqlAsyncCommandExecutor::OnBeforeStart()
{
	return mConnection.Connect();
}

MEDUSA_END;
#endif