// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SleepCommand.h"
#include "Core/Threading/Thread.h"

MEDUSA_BEGIN;

SleepCommand::SleepCommand(long milliseconds /*= 0*/)
	:mMilliseconds(milliseconds)
{
	
}

SleepCommand::~SleepCommand(void)
{
}

bool SleepCommand::OnExecute()
{
	if (mMilliseconds == 0)
	{
		Thread::YieldSelf();
	}
	else
	{
		Thread::Sleep(mMilliseconds);
	}
	return true;
}
MEDUSA_IMPLEMENT_RTTI(SleepCommand, ICommand);

MEDUSA_END;