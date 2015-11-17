// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "CallbackLogger.h"

MEDUSA_BEGIN;

CallbackLogger::CallbackLogger(LogCallback callback, StringRef name /*= StringRef::Empty*/,bool isLogHeader/*=true*/)
	:ILogger(name,isLogHeader),mCallback(callback)
{
}


CallbackLogger::~CallbackLogger(void)
{
}

void CallbackLogger::OutputLogString( StringRef inString ,LogType logType/*=LogType::Info*/ )
{
	if (mCallback!=nullptr)
	{
		mCallback((char*)inString.c_str());
	}
}


MEDUSA_END;
