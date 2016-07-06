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
	FileLogger(const StringRef& filePath);
	virtual ~FileLogger(void);

protected:
	virtual void Print(const Share<LogMessage>& message)override;
	virtual void Print(const Share<WLogMessage>& message)override;
private:
	FileStream mWriter;
};

MEDUSA_END;
