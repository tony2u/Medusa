// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "SqlCommand.h"
#include "Core/Database/SqlDefines.h"

MEDUSA_BEGIN;

template <typename... TArgs>
class SqlPreparedExecuteCommand :public SqlCommand
{
	using ArgsTuple = std::tuple<typename std::decay<TArgs>::type...>;
public:
	SqlPreparedExecuteCommand(SqlConnection* connection = nullptr, const Share<SqlPreparedStatement> statement = nullptr)
		:SqlCommand(connection), mStatement(statement)
	{

	}

	~SqlPreparedExecuteCommand(void)
	{
	
	}
	virtual bool OnExecute()override
	{
		auto result = mStatement->ExecuteBinds(mArgBinds);
		mResult.set_value(result);
		return true;
	}

	std::future<my_ulonglong> Future() { return mResult.get_future(); }

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
protected:
	Share<SqlPreparedStatement> mStatement;
	std::promise<my_ulonglong> mResult;
	ArgsTuple mArgs;	//we should keep a copy of args as this is running async
	NoCompareList<MYSQL_BIND> mArgBinds;
};


template <>
class SqlPreparedExecuteCommand<> :public SqlCommand
{
public:
	SqlPreparedExecuteCommand(SqlConnection* connection = nullptr,const Share<SqlPreparedStatement>& statement = nullptr)
		:SqlCommand(connection), mStatement(statement)
	{

	}

	~SqlPreparedExecuteCommand(void)
	{
		
	}

	virtual bool OnExecute()override
	{
		auto result = mStatement->Execute();
		mResult.set_value(result);
		return true;
	}

	std::future<my_ulonglong> Future() { return mResult.get_future(); }

	bool BindParameters()
	{
		return true;
	}
protected:
	Share<SqlPreparedStatement> mStatement = nullptr;
	std::promise<my_ulonglong> mResult;
};


MEDUSA_END;
#endif