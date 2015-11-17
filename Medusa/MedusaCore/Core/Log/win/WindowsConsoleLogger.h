// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Log/ILogger.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS

class WindowsConsoleLogger :public ILogger
{
public:
	using ILogger::ILogger;
	virtual ~WindowsConsoleLogger(void);

protected:
	virtual void OutputLogString(StringRef inString,LogType logType=LogType::Info);
	virtual void OutputLogString(WStringRef inString,LogType logType=LogType::Info);
	virtual void SetLogColor(LogType logType);
protected:
	LogType mCurrentLogType;
};
#endif

MEDUSA_END;
