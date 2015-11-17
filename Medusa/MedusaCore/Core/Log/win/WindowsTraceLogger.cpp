// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "WindowsTraceLogger.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS


WindowsTraceLogger::~WindowsTraceLogger(void)
{
}

void WindowsTraceLogger::OutputLogString( StringRef inString ,LogType logType/*=LogType::Info*/ )
{
	WHeapString text= StringParser::ToW(inString);
	OutputDebugStringW(text.c_str());
}

void WindowsTraceLogger::OutputLogString( WStringRef inString ,LogType logType/*=LogType::Info*/ )
{
	OutputDebugStringW(inString.c_str());
}

#endif
MEDUSA_END;
