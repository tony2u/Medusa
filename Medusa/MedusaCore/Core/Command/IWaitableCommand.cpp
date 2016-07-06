// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IWaitableCommand.h"

MEDUSA_BEGIN;

IWaitableCommand::IWaitableCommand()
{
	mCompleteEvent.Initialize();
}

IWaitableCommand::~IWaitableCommand(void)
{
	mCompleteEvent.Uninitialize();
}

bool IWaitableCommand::OnExit()
{
	mCompleteEvent.Set();
	return true;
}

bool IWaitableCommand::Wait()
{
	return mCompleteEvent.Wait();
}


MEDUSA_END;