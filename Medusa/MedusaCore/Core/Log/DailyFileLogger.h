// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Log/ILogger.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/Chrono/DateTime.h"
MEDUSA_BEGIN;

class DailyFileLogger :public ILogger
{
public:
	DailyFileLogger(const StringRef& dirPath=StringRef::Empty);
	virtual ~DailyFileLogger(void);

protected:
	virtual void Print(const Share<LogMessage>& message)override;
	virtual void Print(const Share<WLogMessage>& message)override;
protected:
	void GenerateLogFile();
	static HeapString GenerateFileName(const DateTime& date);
private:
	FileStream mWriter;
	DateTime mLogDate;
};

MEDUSA_END;
