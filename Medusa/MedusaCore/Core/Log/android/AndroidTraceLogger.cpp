// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "AndroidTraceLogger.h"


MEDUSA_BEGIN;


#ifdef MEDUSA_ANDROID



AndroidTraceLogger::~AndroidTraceLogger(void)
{
}

void AndroidTraceLogger::OutputLogString( StringRef inString,LogType logType/*=LogType::Info*/ )
{
	
	__android_log_write(ANDROID_LOG_DEBUG,mName.c_str(),inString.c_str());

	//assert(false);

}

void AndroidTraceLogger::OutputLogString( WStringRef inString ,LogType logType/*=LogType::Info*/ )
{
	auto&& str= StringParser::ToA(inString);
	__android_log_write(ANDROID_LOG_DEBUG, mName.c_str(), str.c_str());

	//__android_log_print(ANDROID_LOG_DEBUG, mName.c_str(),inString.c_str());
	//CCLog( "OutputLog" );

	//assert(false);
	//__android_log_print(ANDROID_LOG_DEBUG,"Medusa",inString.c_str());
}

#endif

MEDUSA_END;
