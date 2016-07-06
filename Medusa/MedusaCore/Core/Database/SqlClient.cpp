// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL
#include "SqlClient.h"
#include "Core/Log/Log.h"
#include "SqlConnection.h"
#include "Core/Pattern/Share.h"



MEDUSA_BEGIN;

SqlClient::SqlClient()
{
	if (mysql_library_init(0, NULL, NULL) != 0)
	{
		LogError() << "Failed to init mysql library.";
	}
}

SqlClient::SqlClient(const SqlConectionInfo& info)
	:mConnectionInfo(info)
{
	if (mysql_library_init(0, NULL, NULL) != 0)
	{
		LogError() << "Failed to init mysql library.";
	}
}

SqlClient::SqlClient(const StringRef& host, const StringRef& user, const StringRef& password, const StringRef& database, ushort port /*= 3306*/, const char *unixSocket /*= nullptr*/, SqlClientFlags clientFlags /*= SqlClientFlags::None*/)
	:mConnectionInfo(host,user,password,database,port,unixSocket,clientFlags)
{
	if (mysql_library_init(0, NULL, NULL) != 0)
	{
		LogError() << "Failed to init mysql library.";
	}
}

SqlClient::~SqlClient(void)
{
	mysql_library_end();
}

bool SqlClient::Initialize(uint count /*= 4*/)
{
	FOR_EACH_SIZE(i, count)
	{
		SqlAsyncCommandExecutor* executor = new SqlAsyncCommandExecutor(mConnectionInfo);
		mExecutors.Add(executor);
	}

	return true;
}


void SqlClient::Uninitialize()
{
	for (auto executor : mExecutors)
	{
		executor->StopAndClear();
		delete executor;
	}
	mExecutors.Clear();

	mTextStatements.Clear();
}


std::future<my_ulonglong> SqlClient::Execute(SqlTextExecuteCommand* command)const
{
	auto executor = NextExecutor();
	executor->Execute(command);
	return command->Future();
}


std::future<my_ulonglong> SqlClient::Execute(const StringRef& name)const
{
	auto statement = Find(name);
	auto executor = NextExecutor();
	Share<SqlTextExecuteCommand> command = new SqlTextExecuteCommand(&executor->MutableConnection(), statement);
	executor->Execute(command);
	return command->Future();

}


std::future<my_ulonglong> SqlClient::ExecuteText(const StringRef& text)const
{
	auto executor = NextExecutor();
	SqlTextStatement* statement = new SqlTextStatement(text);
	Share<SqlTextExecuteCommand> command = new SqlTextExecuteCommand(&executor->MutableConnection(), statement);
	executor->Execute(command);
	return command->Future();
}


SqlAsyncCommandExecutor* SqlClient::NextExecutor()const
{
	auto* executor = mExecutors[mExecutorIndex];
	mExecutorIndex = (mExecutorIndex + 1) % mExecutors.Count();
	return executor;
}

SqlAsyncCommandExecutor* SqlClient::CurrentExecutor()const
{
	return mExecutors[mExecutorIndex];
}

bool SqlClient::Connect()
{
	for (auto executor : mExecutors)
	{
		executor->Start();
	}
	return true;
}

Share<SqlTextStatement> SqlClient::Find(const StringRef& name) const
{
	return mTextStatements.GetOptionalByOtherKey(name, name.HashCode(), nullptr);
}


Share<SqlTextStatement> SqlClient::RegisterText(const StringRef& name, const StringRef& statement)
{
	Share<SqlTextStatement> result = Find(name);
	if (result == nullptr)
	{
		result = new SqlTextStatement(statement, name);
		result->Prepare();
		mTextStatements.Add(name, result);
	}
	return result;
}

bool SqlClient::Prepare(const StringRef& name, const StringRef& statement, bool checkStatementChanged /*= false*/)
{
	mPreparedStatements.Set(name, statement);
	for (auto* executor : mExecutors)
	{
		Share<SqlPrepareCommand> command = new SqlPrepareCommand(&executor->MutableConnection(), name, statement, checkStatementChanged);
		executor->Execute(command);
		auto result = command->Future().get();
		if (result == nullptr)
		{
			Log::Throw<SqlException>("Cannot prepare:{} with {}", name, statement);
			return false;
		}
	}
	return true;
}
Share<SqlPreparedStatement> SqlClient::FindOrCreatePreparedStatement(const StringRef& name)const
{
	auto executor = NextExecutor();
	auto statement = executor->Connection().FindPrepare(name);
	if (statement == nullptr)
	{
		executor->WaitForComplete();	//wait for async prepare command to finish
		statement = executor->Connection().FindPrepare(name);	//re find
	}

	if (statement == nullptr)
	{
		//still cannot find, try to add a new one
		auto* statementText = mPreparedStatements.TryGetByOtherKey(name, name.HashCode());
		Log::AssertOrThrow<SqlException>(statementText != nullptr, "Cannot find prepared statement:{}", name);

		Share<SqlPrepareCommand> command = new SqlPrepareCommand(&executor->MutableConnection(), name, *statementText);
		executor->Execute(command);
		command->Future().wait();
		statement = executor->Connection().FindPrepare(name);	//re find
	}

	Log::AssertOrThrow<SqlException>(statement != nullptr, "Cannot find or create prepared statement:{}", name);
	return statement;
}


MEDUSA_END;

#endif