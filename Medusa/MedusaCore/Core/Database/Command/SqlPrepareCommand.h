// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "SqlCommand.h"
#include "Core/Database/SqlDefines.h"

MEDUSA_BEGIN;

class SqlPrepareCommand :public SqlCommand
{
public:
	SqlPrepareCommand(SqlConnection* connection = nullptr, const StringRef& name = StringRef::Empty, const StringRef& statement = StringRef::Empty, bool checkStatementChanged = false);
	~SqlPrepareCommand(void);
	virtual bool OnExecute()override;

	std::future<Share<SqlPreparedStatement>> Future() { return mResult.get_future(); }
protected:
	HeapString mName;
	HeapString mStatement;
	bool mCheckStatementChanged = false;
	std::promise<Share<SqlPreparedStatement>> mResult;
};

MEDUSA_END;
#endif