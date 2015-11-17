// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadPoolWait.h"
#include "Core/Threading/ThreadPool.h"

MEDUSA_BEGIN;
namespace ThreadingPrivate
{
	void NTAPI OnThreadpoolWaitCallback(PTP_CALLBACK_INSTANCE pInstance, PVOID pvContext, PTP_WAIT wait, TP_WAIT_RESULT waitResult)
	{
		ThreadPoolWait* myWait = (ThreadPoolWait*)pvContext;
		RETURN_IF_NULL(myWait);
		ThreadPoolWait::WaitResult result;
		switch (waitResult)
		{
			case WAIT_OBJECT_0:
				result = ThreadPoolWait::WaitResult::Success;
				break;
			case WAIT_TIMEOUT:
				result = ThreadPoolWait::WaitResult::Timeout;
				break;
			case WAIT_ABANDONED_0:
				result = ThreadPoolWait::WaitResult::Abandoned;
				break;
			default:
				result = ThreadPoolWait::WaitResult::Success;
				break;
		}
		myWait->Run(result);
	}
}


ThreadPoolWait::ThreadPoolWait(const StringRef& name, ICommand* command, IWaitable* waitable, uint timeoutMilliseconds /*= (uint)-1*/)
	:mName(name),
	mCommand(command),
	mWaitable(waitable),
	mTimeout(timeoutMilliseconds),
	mResult(WaitResult::Success)
{
	SAFE_RETAIN(command);
	mWait = CreateThreadpoolWait(ThreadingPrivate::OnThreadpoolWaitCallback, this, &ThreadPool::Instance().mCallBackEnviron);

}

ThreadPoolWait::~ThreadPoolWait(void)
{
	SAFE_RELEASE(mCommand);

	if (mWait != nullptr)
	{
		CloseThreadpoolWait(mWait);
		mWait = nullptr;
	}

	mWaitable = nullptr;
}

void ThreadPoolWait::Sumbit()
{
	RETURN_IF_NULL(mWaitable);
	FILETIME startFileTime;
	ULARGE_INTEGER startTime;

	if (mTimeout == (uint)-1)
	{
		startTime.QuadPart = (ULONGLONG)-1;
	}
	else
	{
		//1s==1000ms==1000*1000 qs==1000*1000*1000ns
		//in 100ns
		startTime.QuadPart = (ULONGLONG)-((int)mTimeout * 1000 * 10);
	}


	startFileTime.dwLowDateTime = startTime.LowPart;
	startFileTime.dwHighDateTime = startTime.HighPart;

	SetThreadpoolWait(mWait, mWaitable->NativeHandle(), &startFileTime);
}

void ThreadPoolWait::Wait(bool cancelPending /*= false*/)
{
	WaitForThreadpoolWaitCallbacks(mWait, cancelPending);
}

void ThreadPoolWait::Cancel()
{
	SetThreadpoolWait(mWait, nullptr, nullptr);
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
	if (mCommand!=nullptr)
	{
		mCommand->Execute();
	}
	return true;
}


MEDUSA_END;

#endif
