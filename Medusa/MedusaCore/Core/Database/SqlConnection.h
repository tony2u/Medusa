// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL
#include "Core/String/HeapString.h"
#include "Core/Pattern/INonCopyable.h"
#include "SqlDefines.h"
#include "SqlTextStatement.h"
#include "SqlPreparedStatement.h"
#include "Core/Collection/Dictionary.h"
#include "SqlConectionInfo.h"

MEDUSA_BEGIN;

class SqlConnection :public INonCopyable
{
public:
	SqlConnection();
	SqlConnection(const SqlConectionInfo& info);
	virtual ~SqlConnection();
	MYSQL* Sql() const { return mSql; }

	const SqlConectionInfo& Info() const { return mInfo; }
	SqlConectionInfo& MutableInfo() { return mInfo; }
	void SetInfo(const SqlConectionInfo& val) { mInfo = val; }

	bool AutoCommitEnabled() const { return mAutoCommit; }
	void EnableAutoCommit(bool val);

	bool Connect();
	void StartTransaction();
	void Commit();
	void Rollback();
	void UseDatabase(const StringRef& dbName);
	my_ulonglong Execute(const StringRef& statement)const;

	bool IsConnected()const { return mIsConnected; }
public:
	template <typename... TArgs>
	my_ulonglong Execute(const StringRef& command, const TArgs&... args)const	//return affected row count
	{
		SqlTextStatement statement(command);
		statement.Prepare();
		return statement.Execute(mSql, args...);
	}

	template <typename... TInputArgs, typename... TOutputArgs>
	void Query(const StringRef& query, List<std::tuple<TOutputArgs...>>& outResults, const TInputArgs&... args) const
	{
		SqlTextStatement statement(command);
		statement.Prepare();
		statement.Query(mSql, outResults, args...);
	}
public:
	Share<SqlPreparedStatement> Prepare(const StringRef& name, const StringRef& statement,bool checkStatementChanged=false)
	{
		auto result = FindPrepare(name);
		if (result == nullptr)
		{
			result = new SqlPreparedStatement(statement, name, this);
			result->Prepare();
			mPreparedStatements.Add(name, result);
		}
		else if (checkStatementChanged&&result->Statement() != statement)
		{
			
			result = new SqlPreparedStatement(statement, name, this);
			result->Prepare();
			mPreparedStatements.Set(name, result);
		}
		return result;
	}

	Share<SqlPreparedStatement> FindPrepare(const StringRef& name)const
	{
		return mPreparedStatements.GetOptionalByOtherKey(name, name.HashCode(), nullptr);
	}


	template <typename... TArgs>
	my_ulonglong ExecutePrepare(const StringRef& name, const TArgs&... args)
	{
		auto statement = FindPrepare(name);
		return statement->Execute(args...);
	}

	template <typename... TInputArgs, typename... TOutputArgs>
	void QueryPrepare(const StringRef& name, List<std::tuple<TOutputArgs...>>& outResults, const TInputArgs&... args) const
	{
		auto statement = FindPrepare(name);
		statement->Query(outResults, args...);
	}
private:
	MYSQL* mSql = nullptr;

	SqlConectionInfo mInfo;

	bool mIsConnected = false;
	bool mAutoCommit = true;

	Dictionary<HeapString, Share<SqlPreparedStatement>> mPreparedStatements;	//name-statement
};


MEDUSA_END;
#endif