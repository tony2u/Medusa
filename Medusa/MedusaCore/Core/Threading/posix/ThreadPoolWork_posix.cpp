// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadPoolWork.h"
#include "Core/Threading/ThreadPool.h"

MEDUSA_BEGIN;

ThreadPoolWork::ThreadPoolWork(const StringRef& name, ICommand* command)
	:mName(name), mCommand(command)
{
	SAFE_RETAIN(command);
}

ThreadPoolWork::~ThreadPoolWork(void)
{
	SAFE_RELEASE(mCommand);
}

void ThreadPoolWork::Sumbit()
{
	ThreadPool::Instance().Enqueue(this);
}

void ThreadPoolWork::Wait(bool cancelPending /*= false*/)
{
	if (cancelPending)
	{
		//find current pending work in thread pool
		ThreadPool::Instance().CancelPendingCommands(this);
	}
	mCompleteEvent.Wait();
}

bool ThreadPoolWork::OnExecute()
{
	if (mCommand != nullptr)
	{
		mCommand->Execute();
	}
	mCompleteEvent.Set();
	return true;
}

MEDUSA_END;

#endif
