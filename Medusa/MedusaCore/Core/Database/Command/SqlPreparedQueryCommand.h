// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "SqlCommand.h"
#include "Core/Database/SqlDefines.h"

MEDUSA_BEGIN;

template <typename TTuple, typename... TArgs>
class SqlPreparedQueryCommand :public SqlCommand
{
	using ArgsTuple = std::tuple<typename std::decay<TArgs>::type...>;
	using ResultType = NoCompareList<TTuple>;
public:
	SqlPreparedQueryCommand(SqlConnection* connection = nullptr, const Share<SqlPreparedStatement>& statement = nullptr)
	: SqlCommand(connection), mStatement(statement)
	{

	}
	~SqlPreparedQueryCommand(void)
	{
		
	}

	bool BindParameters(const TArgs&... args)
	{
		constexpr size_t argCount = SqlBinder::CountArgs<TArgs...>::value;

		if (argCount == 0)
		{
			return true;
		}

		if (argCount != mStatement->ParamterCount())
		{
			LogError().Format("Inconsistent parameter count:{} for needed:{}", sizeof...(args), mStatement->ParamterCount());
			return false;
		}
		mArgBinds.ReserveSize(argCount);
		mArgBinds.ForceSetCount(argCount);
		Memory::ClearZero(mArgBinds.MutableItems(), argCount);

		mArgs = std::move(std::make_tuple(std::decay_t<TArgs>(args)...));
		SqlBinder::BindParametersFromTuple<0>(mArgBinds, mArgs);
		return true;
	}

	virtual bool OnExecute()override
	{
		ResultType result;
		mStatement->QueryBinds(result,mArgBinds);
		mResult.set_value(std::move(result));
		return true;
	}

	std::future<ResultType> Future() { return mResult.get_future(); }
protected:
	Share<SqlPreparedStatement> mStatement = nullptr;
	std::promise<ResultType> mResult;
	ArgsTuple mArgs;	//we should keep a copy of args as this is running async
	NoCompareList<MYSQL_BIND> mArgBinds;
};

template <typename TTuple>
class SqlPreparedQueryCommand<TTuple> :public SqlCommand
{
	using ResultType = NoCompareList<TTuple>;
public:
	SqlPreparedQueryCommand(SqlConnection* connection = nullptr, const Share<SqlPreparedStatement>& statement = nullptr)
		: SqlCommand(connection), mStatement(statement)
	{

	}
	~SqlPreparedQueryCommand(void)
	{
		
	}

	bool BindParameters()
	{
		return true;
	}

	virtual bool OnExecute()override
	{
		ResultType result;
		mStatement->Query(result);
		mResult.set_value(std::move(result));
		return true;
	}

	std::future<ResultType> Future() { return mResult.get_future(); }
protected:
	Share<SqlPreparedStatement> mStatement;
	std::promise<ResultType> mResult;
};

MEDUSA_END;
#endif