// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ILogger.h"
#include "Core/String/StdString.h"


MEDUSA_BEGIN;

ILogger::ILogger(StringRef name /*= StringRef::Empty*/,bool isLogHeader/*=true*/)
	:mName(name)
{
	mCurrentLevel = LogLevel::All;	//open all logs
	mIsLogHeaderEnabled = isLogHeader;

	mBufferA.ReserveSize(512);
	mBufferW.ReserveSize(512);

}

ILogger::~ILogger(void)
{
}

//////////////////////////////////////////////////////////////////////////

void ILogger::LogHeaderInBufferA(LogType logType/*=LogType::Info*/)
{
	time_t tNowTime;
	time(&tNowTime);

	tm localTime;
#ifdef WIN32
	localtime_s(&localTime, &tNowTime);
#else
	localtime_r(&tNowTime, &localTime);
#endif
	mBufferA.Format("{}-{}-{} {}:{}:{} => ", localTime.tm_year + 1900, localTime.tm_mon + 1, localTime.tm_mday, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

	OutputLogString(mBufferA.Buffer(), logType);
}



void ILogger::Info(StringRef inString)
{
	RETURN_IF_FALSE(IsLogInfo());

	if (mIsLogHeaderEnabled)
	{
		LogHeaderInBufferA();
	}

	OutputLogString(inString);
	OutputLogString("\n");
}


void ILogger::Error(StringRef inString)
{

	RETURN_IF_FALSE(IsLogError());

	if (mIsLogHeaderEnabled)
	{
		LogHeaderInBufferA(LogType::Error);
	}

	OutputLogString("ERROR: ", LogType::Error);

	OutputLogString(inString, LogType::Error);
	OutputLogString("\n", LogType::Error);
}


void ILogger::Assert(bool condition, StringRef inString)
{
	if (!condition)
	{
		Error(inString);
		assert(false);
	}

}


void ILogger::AssertFailed(StringRef inString)
{
	Error(inString);
	assert(false);
}

//////////////////////////////////////////////////////////////////////////

void ILogger::LogHeaderInBufferW(LogType logType/*=LogType::Info*/)
{
	time_t tNowTime;
	time(&tNowTime);

	tm localTime;
#ifdef WIN32
	localtime_s(&localTime, &tNowTime);
#else
	localtime_r(&tNowTime, &localTime);
#endif

	mBufferW.Format(L"{}-{}-{} {}:{}:{} => ",localTime.tm_year + 1900, localTime.tm_mon + 1, localTime.tm_mday, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

	OutputLogString(mBufferW.Buffer(), logType);
}



void ILogger::Info(WStringRef inString)
{
	RETURN_IF_FALSE(IsLogInfo());

	if (mIsLogHeaderEnabled)
	{
		LogHeaderInBufferW();
	}

	OutputLogString(inString);
	OutputLogString(L"\n");
}



void ILogger::Error(WStringRef inString)
{

	RETURN_IF_FALSE(IsLogError());

	if (mIsLogHeaderEnabled)
	{
		LogHeaderInBufferW(LogType::Error);
	}

	OutputLogString(L"ERROR: ", LogType::Error);

	OutputLogString(inString, LogType::Error);
	OutputLogString(L"\n", LogType::Error);
}

void ILogger::Assert(bool condition, WStringRef inString)
{
	if (!condition)
	{
		Error(inString);
		assert(false);
	}

}

void ILogger::AssertFailed(WStringRef inString)
{
	Error(inString);
	assert(false);
}
MEDUSA_END;
