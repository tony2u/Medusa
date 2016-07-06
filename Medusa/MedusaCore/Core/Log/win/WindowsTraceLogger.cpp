// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "WindowsTraceLogger.h"
#include "Core/Log/LogMessage.h"
#include "Core/Pattern/Share.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS

void WindowsTraceLogger::Print(const Share<LogMessage>& message)
{
	WHeapString text = StringParser::ToW(message->Content());
	OutputDebugStringW(text.c_str());
}

void WindowsTraceLogger::Print(const Share<WLogMessage>& message)
{
	OutputDebugStringW(message->Content().c_str());
}

#endif
MEDUSA_END;
