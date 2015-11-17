// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileLogger.h"

MEDUSA_BEGIN;

FileLogger::FileLogger(StringRef filePath, StringRef name /*= StringRef::Empty*/,bool isLogHeader/*=true*/):ILogger(name,isLogHeader),mWriter(filePath)
{
	
}


FileLogger::~FileLogger(void)
{
	
}

void FileLogger::OutputLogString( StringRef inString ,LogType logType/*=LogType::Info*/ )
{
	mWriter.WriteString(inString,false);
}

void FileLogger::OutputLogString( WStringRef inString ,LogType logType/*=LogType::Info*/ )
{
	mWriter.WriteString(inString,false);
}

MEDUSA_END;
