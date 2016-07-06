// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL
#include "SqlTextStatement.h"
#include "SqlConnection.h"
#include "SqlException.h"

MEDUSA_BEGIN;



bool SqlTextStatement::Prepare()
{
	HeapString temp;
	uint length = (ulong)mStatement.Length();
	char insideQuote = '\0';

	uint from = 0;
	FOR_EACH_UINT32(i, length)
	{
		char c = mStatement[i];
		switch (c)
		{
		case '\'':
		case '"':
			if (insideQuote == c)
			{
				insideQuote = '\0';
			}
			else if (insideQuote == '\0')
			{
				insideQuote = c;
			}
			break;
		case '?':
			if (insideQuote == L'\0')
			{
				//add prev
				mSegments.NewAdd().Append(mStatement.Buffer() + from, i - from);	//not include this ?
				from = i + 1;
				++mParamterCount;
			}
			break;
		default:
			break;
		}
	}

	if (from < mStatement.Length())
	{
		mSegments.NewAdd().Append(mStatement.Buffer() + from, mStatement.Length() - from);	//add left string
	}

	return true;
}

HeapString SqlTextStatement::ReplaceInsertions(List<HeapString>& args) const
{
	uint argCount = (uint)args.Count();
	if (mSegments.Count() != argCount + 1)
	{
		LogError().Format("Inconsistent parameter count:{} for needed:{}", args.Count(), mParamterCount);
		return HeapString::Empty;
	}

	HeapString result;
	FOR_EACH_SIZE(i, argCount)
	{
		result += mSegments[i];
		result += args[i];
	}
	result += mSegments.Last();

	return result;
}

my_ulonglong SqlTextStatement::Execute(MYSQL* sql)
{
	return OnExecute(sql,mStatement);
}

my_ulonglong SqlTextStatement::OnExecute(MYSQL* sql, const StringRef& statement)const
{

	if (mysql_real_query(sql, statement.c_str(), (ulong)statement.Length()) != 0)
	{
		throw SqlException(sql, "Error in SqlTextStatement::OnExecute");
	}
	//auto resultCount = mysql_field_count(sql);
	auto affectedRowCount = mysql_affected_rows(sql);
	return affectedRowCount;
}

MYSQL_RES* SqlTextStatement::OnQuery(MYSQL* sql, const StringRef& statement)const
{
	if (mysql_real_query(sql, statement.c_str(), (ulong)statement.Length()) != 0)
	{
		throw SqlException(sql, "Error in SqlTextStatement::OnExecute");
	}
	//auto affectedRowCount = mysql_affected_rows(sql);

	auto resultCount = mysql_field_count(sql);
	auto resultSet = mysql_store_result(sql);

	if (resultSet == nullptr && resultCount > 0)
	{
		throw SqlException(sql, "Error in SqlTextStatement::OnExecute");
	}

	if (resultCount == 0)
	{
		mysql_free_result(resultSet);
		resultSet = nullptr;
	}
	return resultSet;
}

MEDUSA_END;
#endif