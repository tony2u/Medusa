// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL
#include "ISqlStatement.h"
#include "SqlBinder.h"
#include "SqlException.h"
MEDUSA_BEGIN;


class SqlPreparedStatement :public ISqlStatement
{
public:
	SqlPreparedStatement(const StringRef& statement, const StringRef& name = StringRef::Empty, SqlConnection* connection = nullptr);
	~SqlPreparedStatement();
	SqlConnection* Connection() const { return mConnection; }
	void SetConnection(SqlConnection* val) { mConnection = val; }
	MYSQL* Sql() const;

	virtual bool Prepare()override;

public:
	my_ulonglong ExecuteBinds(NoCompareList<MYSQL_BIND>& argBinds)const
	{
		if (mysql_stmt_bind_param(mSTMT, argBinds.MutableItems()) != 0)
		{
			throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_bind_param");
		}

		if (mysql_stmt_execute(mSTMT) != 0)
		{
			throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_execute");
		}

		my_ulonglong affectedRows = mysql_stmt_affected_rows(mSTMT);
		if (affectedRows == (my_ulonglong)-1)
		{
			throw SqlException(mSTMT, "Failed to SqlPreparedStatement::mysql_stmt_execute");
		}

		return affectedRows;
	}

	template <typename... TArgs>
	my_ulonglong Execute(const TArgs&... args)const
	{
		constexpr size_t argCount = SqlBinder::CountArgs<TArgs...>::value;

		if (argCount != mParamterCount)
		{
			LogError().Format("Inconsistent parameter count:{} for needed:{}", argCount, mParamterCount);
			return 0;
		}
		if (argCount ==0)
		{
			if (mysql_stmt_execute(mSTMT) != 0)
			{
				throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_execute");
			}

			my_ulonglong affectedRows = mysql_stmt_affected_rows(mSTMT);
			if (affectedRows == (my_ulonglong)-1)
			{
				throw SqlException(mSTMT, "Failed to SqlPreparedStatement::mysql_stmt_execute");
			}

			return affectedRows;
		}
		else
		{
			NoCompareList<MYSQL_BIND> argBinds;
			argBinds.ReserveSize(argCount);
			argBinds.ForceSetCount(argCount);
			Memory::ClearZero(argBinds.MutableItems(), argCount);

			SqlBinder::BindParameters<0>(argBinds, args...);

			return ExecuteBinds(argBinds);
		}
	}

	template <typename... TOutputArgs>
	bool QueryBinds(NoCompareList<std::tuple<TOutputArgs...>>& outResults, NoCompareList<MYSQL_BIND>& argBinds) const
	{
		constexpr size_t resultCount = SqlBinder::CountArgs<TOutputArgs...>::value;

		//uint resultCount = std::tuple_size<std::tuple<TOutputArgs...>>::value;
		if (resultCount != mResultCount)
		{
			LogError().Format("Inconsistent result count:{} for needed:{}", resultCount, mResultCount);
			return false;
		}

		if (mysql_stmt_bind_param(mSTMT, argBinds.MutableItems()) != 0)
		{
			throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_bind_param");
		}

		if (mysql_stmt_execute(mSTMT) != 0)
		{
			throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_execute");
		}

		if (mysql_stmt_store_result(mSTMT) != 0)
		{
			throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_store_result");
		}

		my_ulonglong affectedRows = mysql_stmt_affected_rows(mSTMT);
		if (affectedRows == (my_ulonglong)-1)
		{
			throw SqlException(mSTMT, "Failed to SqlPreparedStatement::mysql_stmt_execute");
		}

		NoCompareList<MYSQL_BIND> resultBinds;
		resultBinds.ReserveSize(resultCount);
		resultBinds.ForceSetCount(resultCount);
		Memory::ClearZero(resultBinds.MutableItems(), resultCount);

		FOR_EACH_SIZE(i, affectedRows)
		{
			auto& newItem = outResults.NewAdd();
			SqlBinder::BindResults<0, std::tuple<TOutputArgs...>>(newItem, resultBinds, mResultFields);

			if (mysql_stmt_bind_result(mSTMT, resultBinds.MutableItems()) != 0)
			{
				throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_bind_result");
			}

			int rowStatus = mysql_stmt_fetch(mSTMT);
			if (rowStatus == 1)
			{
				outResults.RemoveLast();
				throw SqlException(mSTMT, "Error in SqlPreparedStatement::mysql_stmt_fetch");
			}
			else if (rowStatus == MYSQL_NO_DATA)
			{
				outResults.RemoveLast();
				break;
			}
			else if (rowStatus == MYSQL_DATA_TRUNCATED)
			{
				RefetchTruncatedColumns(resultBinds);
			}
			

		}

		return true;
	}


	template <typename... TInputArgs, typename... TOutputArgs>
	bool Query(NoCompareList<std::tuple<TOutputArgs...>>& outResults, const TInputArgs&... args) const
	{
		constexpr size_t paramCount = SqlBinder::CountArgs<TInputArgs...>::value;
		constexpr size_t resultCount = SqlBinder::CountArgs<TOutputArgs...>::value;

		//uint paramCount = sizeof...(args);
		//uint resultCount = std::tuple_size<std::tuple<TOutputArgs...>>::value;

		if (paramCount != mParamterCount)
		{
			LogError().Format("Inconsistent parameter count:{} for needed:{}", paramCount, mParamterCount);
			return false;
		}

		if (resultCount != mResultCount)
		{
			LogError().Format("Inconsistent result count:{} for needed:{}", resultCount, mResultCount);
			return false;
		}

		NoCompareList<MYSQL_BIND> argBinds;
		argBinds.ReserveSize(paramCount);
		argBinds.ForceSetCount(paramCount);
		Memory::ClearZero(argBinds.MutableItems(), paramCount);
		SqlBinder::BindParameters<0>(argBinds, args...);

		return QueryBinds(outResults, argBinds);
	}

	void RefetchTruncatedColumns(NoCompareList<MYSQL_BIND>& resultBinds)const;

protected:
	SqlConnection* mConnection = nullptr;
	MYSQL_STMT* mSTMT;

	MYSQL_RES* mResultMetadata = nullptr;
	NoCompareList<MYSQL_FIELD*> mResultFields;

	uint mResultCount = 0;
};

MEDUSA_END;
#endif