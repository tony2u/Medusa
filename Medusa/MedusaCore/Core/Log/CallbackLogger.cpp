// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "CallbackLogger.h"
#include "Core/Log/LogMessage.h"
#include "Core/Pattern/Share.h"
MEDUSA_BEGIN;

void CallbackLogger::Print(const Share<LogMessage>& message)
{
	OnMessageA(message->Content());
}

void CallbackLogger::Print(const Share<WLogMessage>& message)
{
	OnMessageW(message->Content());
}



MEDUSA_END;
