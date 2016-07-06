// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileLogger.h"
#include "Core/Log/LogMessage.h"
#include "Core/IO/FileIdRef.h"
#include "Core/IO/FileSystem.h"
#include "Core/Pattern/Share.h"
MEDUSA_BEGIN;

FileLogger::FileLogger(const StringRef& filePath)
	:ILogger(filePath)
{
	mWriter.Open(filePath, FileOpenMode::AppendReadWriteClearEOFOrCreate, FileDataType::Text);
}


FileLogger::~FileLogger(void)
{
	
}

void FileLogger::Print(const Share<LogMessage>& message)
{
	mWriter.WriteString(message->Content());
}

void FileLogger::Print(const Share<WLogMessage>& message)
{
	mWriter.WriteString(message->Content());
}



MEDUSA_END;
