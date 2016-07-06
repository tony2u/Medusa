// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Log/ILogger.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class CallbackLogger :public ILogger
{
public:
	using ILogger::ILogger;
	Event<void(const StringRef&)> OnMessageA;
	Event<void(const WStringRef&)> OnMessageW;

protected:
	virtual void Print(const Share<LogMessage>& message)override;
	virtual void Print(const Share<WLogMessage>& message)override;

};

MEDUSA_END;
