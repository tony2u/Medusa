// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "AndroidTraceLogger.h"
#include "Core/Log/LogMessage.h"
#include "Core/Pattern/Share.h"
MEDUSA_BEGIN;


#ifdef MEDUSA_ANDROID

void AndroidTraceLogger::Print(const Share<LogMessage>& message)
{
	__android_log_write(ANDROID_LOG_DEBUG, mName.c_str(), message->Content().c_str());
}

void AndroidTraceLogger::Print(const Share<WLogMessage>& message)
{
	auto&& str = StringParser::ToA(message->Content());
	__android_log_write(ANDROID_LOG_DEBUG, mName.c_str(), str.c_str());
}


#endif

MEDUSA_END;
