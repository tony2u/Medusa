// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Log/ILogger.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_IOS

class IOSConsoleLogger :public ILogger
{
public:
	using ILogger::ILogger;
	virtual ~IOSConsoleLogger(void);

protected:
	virtual void OutputLogString(StringRef inString,LogType logType=LogType::Info);
	virtual void OutputLogString(WStringRef inString,LogType logType=LogType::Info);


};

#endif
MEDUSA_END;
