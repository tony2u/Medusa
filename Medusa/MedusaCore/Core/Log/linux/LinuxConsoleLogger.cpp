// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "CorePlatform/CorePlatform.h"
#include "LinuxConsoleLogger.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_LINUX

LinuxConsoleLogger::LinuxConsoleLogger(bool isLogHeader/*=true*/):ILogger(isLogHeader)
{
}


LinuxConsoleLogger::~LinuxConsoleLogger(void)
{
}

void LinuxConsoleLogger::OutputLogString( StringRef inString )
{
	printf(inString.c_str());
}

void LinuxConsoleLogger::OutputLogString( WStringRef inString )
{
	wprintf(inString.c_str());
}
#endif

MEDUSA_END;
