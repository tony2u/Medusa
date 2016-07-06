// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "SqlCommand.h"
#include "Core/Database/SqlDefines.h"

MEDUSA_BEGIN;

class SqlTextExecuteCommand :public SqlCommand
{
public:
	SqlTextExecuteCommand(SqlConnection* connection = nullptr, const Share<SqlTextStatement>& statement = nullptr);
	~SqlTextExecuteCommand(void);
	virtual bool OnExecute()override;

	std::future<my_ulonglong> Future() { return mResult.get_future(); }
protected:
	Share<SqlTextStatement> mStatement;
	std::promise<my_ulonglong> mResult;
};

MEDUSA_END;
#endif