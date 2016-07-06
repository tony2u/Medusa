// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "IOSConsoleLogger.h"
#include "Core/Log/LogMessage.h"
#include "Core/Pattern/SharePtr.h"
#ifdef MEDUSA_IOS
MEDUSA_BEGIN;


void IOSConsoleLogger::Print(const SharePtr<LogMessage>& message)
{
	printf(message->Content().c_str());
}

void IOSConsoleLogger::Print(const SharePtr<WLogMessage>& message)
{
	wprintf(message->Content().c_str());
}


MEDUSA_END;
#endif