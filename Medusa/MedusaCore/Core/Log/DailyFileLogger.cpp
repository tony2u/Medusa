// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "DailyFileLogger.h"
#include "Core/Log/LogMessage.h"
#include "Core/IO/FileIdRef.h"
#include "Core/IO/FileSystem.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

DailyFileLogger::DailyFileLogger(const StringRef& dirPath /*= StringRef::Empty*/)
	:ILogger(dirPath)
{
	mLogDate = DateTime::Now();
	GenerateLogFile();
}


DailyFileLogger::~DailyFileLogger(void)
{
	mWriter.Close();
}

void DailyFileLogger::Print(const Share<LogMessage>& message)
{
	GenerateLogFile();
	mWriter.WriteString(message->Content(),false);
}

void DailyFileLogger::Print(const Share<WLogMessage>& message)
{
	GenerateLogFile();
	mWriter.WriteString(message->Content(),false);
}

void DailyFileLogger::GenerateLogFile()
{
	DateTime now= DateTime::Now();
	if (mLogDate.Years()!=now.Years()||mLogDate.Months()!=now.Months()||mLogDate.Days()!=now.Days())
	{
		mWriter.Close();
		mLogDate = now;
	}

	if (!mWriter.IsOpen())
	{
		HeapString filePath = GenerateFileName(mLogDate);
		mWriter.Open(filePath, FileOpenMode::AppendReadWriteClearEOFOrCreate, FileDataType::Text,FileShareMode::Read);
		mWriter.SetBuffer(FileBufferMode::None, nullptr, 0);
	}

}

HeapString DailyFileLogger::GenerateFileName(const DateTime& date)
{
	HeapString result;
	result+=date.ToString("%Y%m%d");
	result += ".log";
	return result;
}


MEDUSA_END;
