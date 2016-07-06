// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "Core/Command/Executor/TAsyncCommandExecutor.h"
#include "SqlCommand.h"
#include "Core/Database/SqlConnection.h"

MEDUSA_BEGIN;


class SqlAsyncCommandExecutor :public TAsyncCommandExecutor<SqlCommand>
{
public:
	SqlAsyncCommandExecutor();
	SqlAsyncCommandExecutor(const SqlConectionInfo& info);
	virtual ~SqlAsyncCommandExecutor(void);

	const SqlConnection& Connection() const { return mConnection; }
	SqlConnection& MutableConnection() { return mConnection; }
protected:
	virtual bool OnBeforeStart() override;
	virtual bool OnBeforeJoin()
	{
		PrepareToCancel();
		mStartEvent.Set();
		return true;
	}
protected:
	SqlConnection mConnection;
};

MEDUSA_END;
#endif