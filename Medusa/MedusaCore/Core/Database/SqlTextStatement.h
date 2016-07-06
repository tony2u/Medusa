// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL
#include "ISqlStatement.h"
#include "Core/String/StringParser.h"
#include "SqlBinder.h"
#include "Core/Log/Log.h"
#include "SqlException.h"

MEDUSA_BEGIN;


class SqlTextStatement :public ISqlStatement
{
public:
	using ISqlStatement::ISqlStatement;
	virtual bool Prepare()override;
	my_ulonglong Execute(MYSQL* sql);
public:
	template <typename... TArgs>
	SqlTextStatement* Bind(const TArgs&... args)const
	{
		constexpr size_t argCount = sizeof...(args);	//text ? is bind to per arg,so no need to CountArgs
		if (argCount != mParamterCount)
		{
			LogError().Format("Inconsistent parameter count:{} for needed:{}", sizeof...(args), mParamterCount);
			return 0;
		}

		List<HeapString> argStrings;
		argStrings.ReserveSize(argCount);
		SqlBinder::SerializeToString(argStrings, args...);

		auto sql = ReplaceInsertions(argStrings);
		return new SqlTextStatement(sql, mName);
	}

	template <typename... TArgs>
	my_ulonglong Execute(MYSQL* sql, const TArgs&... args)const
	{
		constexpr size_t argCount = sizeof...(args);
		if (argCount != mParamterCount)
		{
			LogError().Format("Inconsistent parameter count:{} for needed:{}", sizeof...(args), mParamterCount);
			return 0;
		}

		List<HeapString> argStrings;
		argStrings.ReserveSize(argCount);
		SqlBinder::SerializeToString(argStrings, args...);

		HeapString text = ReplaceInsertions(argStrings);
		return OnExecute(sql,text);
	}

	template <typename... TInputArgs, typename... TOutputArgs>
	void Query(MYSQL* sql, NoCompareList<std::tuple<TOutputArgs...>>& outResults, const TInputArgs&... args) const
	{
		constexpr size_t argCount = sizeof...(args);

		if (argCount != mParamterCount)
		{
			LogError().Format("Inconsistent parameter count:{} for needed:{}", sizeof...(args), mParamterCount);
		}

		MYSQL_RES* resultSet = nullptr;
		if (mParamterCount > 0)
		{
			List<HeapString> argStrings;
			argStrings.ReserveSize(argCount);
			SqlBinder::SerializeToString(argStrings, args...);

			auto text = ReplaceInsertions(argStrings);
			resultSet = OnQuery(sql, text);
		}
		else
		{
			resultSet = OnQuery(sql, mStatement);
		}

		if (resultSet != nullptr)
		{
			auto fieldCount = mysql_field_count(sql);
			constexpr size_t outArgCount = SqlBinder::CountArgs<TOutputArgs...>::value;
			if (outArgCount != fieldCount)
			{
				LogError().Format("Inconsistent result column count:{} to output:{}", fieldCount, outArgCount);
			}

			auto resultRowCount = mysql_num_rows(resultSet);
			outResults.ReserveSize(resultRowCount);
			auto fileds = mysql_fetch_fields(resultSet);
			//check field type
			SqlBinder::CheckFieldTypes<0, TOutputArgs...>(fileds, fieldCount);
			MYSQL_ROW currentRow;
			while ((currentRow = mysql_fetch_row(resultSet)) != nullptr)
			{
				auto currentRowLengths = mysql_fetch_lengths(resultSet);
				if (currentRowLengths == nullptr)
				{
					throw SqlException(sql, "Error in SqlTextStatement::mysql_fetch_lengths return null");
				}

				auto& newItem = outResults.NewAdd();

				SqlBinder::StoreResults<0>(newItem, currentRow, currentRowLengths, fileds,fieldCount);
			}
			mysql_free_result(resultSet);
			resultSet = nullptr;
		}

	}
protected:
	HeapString ReplaceInsertions(List<HeapString>& args)const;
	my_ulonglong OnExecute(MYSQL* sql, const StringRef& statement)const;
	MYSQL_RES* OnQuery(MYSQL* sql, const StringRef& statement)const;
protected:

	List<HeapString> mSegments;
};

MEDUSA_END;
#endif