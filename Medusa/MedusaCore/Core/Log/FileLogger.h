// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Log/ILogger.h"
#include "Core/IO/Stream/FileStream.h"

MEDUSA_BEGIN;

class FileLogger :public ILogger
{
public:
	FileLogger(StringRef filePath, StringRef name = StringRef::Empty,bool isLogHeader=true);
	virtual ~FileLogger(void);

protected:
	virtual void OutputLogString(StringRef inString,LogType logType=LogType::Info);
	virtual void OutputLogString(WStringRef inString,LogType logType=LogType::Info);

private:
	
	FileStream mWriter;
};

MEDUSA_END;
