// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "SqlCommand.h"
#include "Core/Database/SqlDefines.h"

MEDUSA_BEGIN;

template<typename... TOutputArgs>
class SqlTextQueryCommand :public SqlCommand
{
	using ResultType = NoCompareList<std::tuple<TOutputArgs...>>;
public:
	SqlTextQueryCommand(SqlConnection* connection = nullptr, const Share<SqlTextStatement>& statement = nullptr)
	: SqlCommand(connection), mStatement(statement)
	{

	}
	~SqlTextQueryCommand(void)
	{
		
	}

	virtual bool OnExecute()override
	{
		ResultType result;
		mStatement->Query(mConnection->Sql(), result);
		mResult.set_value(std::move(result));
		return true;
	}

	std::future<ResultType> Future() { return mResult.get_future(); }
protected:
	Share<SqlTextStatement> mStatement;
	std::promise<ResultType> mResult;
};

MEDUSA_END;
#endif