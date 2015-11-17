// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Log/ILogger.h"
#include "Core/Pattern/Delegate.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS
#define MEDUSA_STD_CALL _stdcall
#else
#define MEDUSA_STD_CALL 
#endif
typedef void (MEDUSA_STD_CALL *LogCallback)(char*);


class CallbackLogger :public ILogger
{
public:
	CallbackLogger(LogCallback callback=nullptr, StringRef name = StringRef::Empty,bool isLogHeader=true);
	virtual ~CallbackLogger(void);

	LogCallback GetCallback() const { return mCallback; }
	void SetCallback(LogCallback val) { mCallback = val; }
protected:
	virtual void OutputLogString(StringRef inString,LogType logType=LogType::Info);
	LogCallback mCallback;
	

};

MEDUSA_END;
