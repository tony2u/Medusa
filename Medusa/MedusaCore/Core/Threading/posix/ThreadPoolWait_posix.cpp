// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadPoolWait.h"
#include "Core/Threading/ThreadPool.h"

MEDUSA_BEGIN;

ThreadPoolWait::ThreadPoolWait(const StringRef& name, ICommand* command, IWaitable* waitable, uint timeoutMilliseconds /*= (uint)-1*/)
	:mName(name),
	mCommand(command),
	mWaitable(waitable),
	mResult(WaitResult::Success),
	mTimeout(timeoutMilliseconds)
{
	SAFE_RETAIN(command);

}

ThreadPoolWait::~ThreadPoolWait(void)
{
	SAFE_RELEASE(mCommand);
	
	mWaitable = nullptr;
}

void ThreadPoolWait::Sumbit()
{
	ThreadPool::Instance().Enqueue(this);
}

void ThreadPoolWait::Wait(bool cancelPending /*= false*/)
{
	if (cancelPending)
	{
		//find current pending work in thread pool
		ThreadPool::Instance().CancelPendingCommands(this);
	}
	mCompleteEvent.Wait();
}

void ThreadPoolWait::Cancel()
{
	mResult = WaitResult::Abandoned;
	ThreadPool::Instance().CancelPendingCommands(this);

	if (mWaitable!=nullptr)
	{
		mWaitable->Set();
	}
}

void ThreadPoolWait::Run(WaitResult result)
{
	RETURN_IF_NULL(mCommand);
	mResult = result;
	if (mResult == WaitResult::Success)
	{
		OnExecute();
	}
}

bool ThreadPoolWait::OnExecute()
{
	if (mWaitable!=nullptr)
	{
		bool isSuccess = mWaitable->WaitTimeout(mTimeout);
		if (mResult != WaitResult::Abandoned)
		{
			mResult = isSuccess ? WaitResult::Success : WaitResult::Timeout;
		}
	}
	else
	{
		if (mResult != WaitResult::Abandoned)
		{
			mResult = WaitResult::Success;
		}
	}

	if (mCommand != nullptr)
	{
		mCommand->Execute();
	}
	mCompleteEvent.Set();
	return true;
}


MEDUSA_END;

#endif
