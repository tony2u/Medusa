// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL
#include "Core/Collection/List.h"
#include "SqlConectionInfo.h"
#include "Core/Collection/Dictionary.h"
#include "SqlTextStatement.h"
#include "Core/Database/Command/SqlAsyncCommandExecutor.h"
#include "Core/Database/Command/SqlTextExecuteCommand.h"
#include "Core/Database/Command/SqlTextQueryCommand.h"
#include "Core/Database/Command/SqlPrepareCommand.h"
#include "Core/Database/Command/SqlPreparedExecuteCommand.h"
#include "Core/Database/Command/SqlPreparedQueryCommand.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;


class SqlClient
{
public:
	SqlClient();
	SqlClient(const SqlConectionInfo& info);
	SqlClient(const StringRef& host, const StringRef& user, const StringRef& password, const StringRef& database, ushort port = 3306, const char *unixSocket = nullptr, SqlClientFlags clientFlags = SqlClientFlags::None);

	~SqlClient(void);
public:
	const SqlConectionInfo& ConnectionInfo() const { return mConnectionInfo; }
	SqlConectionInfo& MutableConnectionInfo() { return mConnectionInfo; }
	void SetConnectionInfo(const SqlConectionInfo& val) { mConnectionInfo = val; }
public:
	bool Initialize(uint count = 4);
	bool Connect();
	void Uninitialize();
public:
	std::future<my_ulonglong> Execute(SqlTextExecuteCommand* command)const;
	std::future<my_ulonglong> Execute(const StringRef& name)const;
	std::future<my_ulonglong> ExecuteText(const StringRef& text)const;

	template <typename... TArgs>
	std::future<my_ulonglong> Execute(const StringRef& name, const TArgs&... args)const
	{
		SqlTextStatement* statement = Find(name);
		auto* realStatement = statement->Bind(args...);
		auto executor = NextExecutor();
		SqlTextExecuteCommand* command = new SqlTextExecuteCommand(&executor->MutableConnection(), statement);
		executor->Execute(command);
		return command->Future();
	}

	template <typename... TArgs>
	std::future<my_ulonglong> ExecuteText(const StringRef& text, const TArgs&... args)const
	{
		auto executor = NextExecutor();
		SqlTextStatement statement(text);
		statement.Prepare();
		auto* realStatement = statement.Bind(args...);
		SqlTextExecuteCommand* command = new SqlTextExecuteCommand(&executor->MutableConnection(), realStatement);
		executor->Execute(command);
		return command->Future();
	}


	template < typename... TOutputArgs, typename... TInputArgs>
	std::future<NoCompareList<std::tuple<TOutputArgs...>>> QueryText(const StringRef& text, const TInputArgs&... args) const
	{
		auto executor = NextExecutor();
		SqlTextStatement statement(text);
		statement.Prepare();
		auto* realStatement = statement.Bind(args...);
		auto command = new SqlTextQueryCommand<TOutputArgs...>(&executor->MutableConnection(), realStatement);
		executor->Execute(command);
		return command->Future();
	}


	Share<SqlTextStatement> RegisterText(const StringRef& name, const StringRef& statement);
	Share<SqlTextStatement> Find(const StringRef& name)const;

public:
	bool Prepare(const StringRef& name, const StringRef& statement, bool checkStatementChanged = false);

	template <typename... TArgs>
	std::future<my_ulonglong> ExecutePrepare(const StringRef& name, const TArgs&... args)
	{
		auto* statement = FindOrCreatePreparedStatement(name);
		auto executor = CurrentExecutor();
		using commandType = SqlPreparedExecuteCommand<TArgs...>;
		Share<commandType> command = new commandType(&executor->MutableConnection(), statement);
		command->BindParameters(args...);
		executor->Execute(command);
		return command->Future();
	}

	template < typename... TOutputArgs, typename... TInputArgs>
	std::future<NoCompareList<std::tuple<TOutputArgs...>>> QueryPrepare(const StringRef& name, const TInputArgs&... args) const
	{
		auto* statement = FindOrCreatePreparedStatement(name);
		auto executor = CurrentExecutor();
		using ResultType = std::tuple<TOutputArgs...>;
		using commandType = SqlPreparedQueryCommand<ResultType, TInputArgs...>;
		Share<commandType> command = new commandType(&executor->MutableConnection(), statement);
		command->BindParameters(args...);
		executor->Execute(command);
		return command->Future();
	}

protected:
	Share<SqlPreparedStatement> FindOrCreatePreparedStatement(const StringRef& name)const;
	SqlAsyncCommandExecutor* NextExecutor()const;
	SqlAsyncCommandExecutor* CurrentExecutor()const;
protected:
	SqlConectionInfo mConnectionInfo;
	List<SqlAsyncCommandExecutor*> mExecutors;
	mutable uint mExecutorIndex = 0;

	Dictionary<HeapString, Share<SqlTextStatement>> mTextStatements;	//name-statements
	Dictionary<HeapString, HeapString> mPreparedStatements;	//name-prepared statements
};

MEDUSA_END;
#endif