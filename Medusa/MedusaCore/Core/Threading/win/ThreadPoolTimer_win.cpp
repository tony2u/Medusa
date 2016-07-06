// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadPoolTimer.h"
#include "Core/Threading/ThreadPool.h"

MEDUSA_BEGIN;
namespace ThreadingPrivate
{
	void NTAPI OnThreadpoolTimerCallback(PTP_CALLBACK_INSTANCE pInstance, PVOID pvContext, PTP_TIMER timer)
	{
		ThreadPoolTimer* myTimer = (ThreadPoolTimer*)pvContext;
		RETURN_IF_NULL(myTimer);
		if (!myTimer->Execute())
		{
			myTimer->Cancel();
		}
	}
}

ThreadPoolTimer::ThreadPoolTimer(ThreadPool* pool, const StringRef& name, const ShareCommand& command, uint delay /*= 0*/, uint repeatCount /*= 0*/, uint repeatInterval /*= 0*/, uint repeatIntervalRange/*=0*/)
	:mPool(pool),mName(name), mCommand(command), mDelay(delay), mRepeatCount(repeatCount), mRepeatInterval(repeatInterval), mRepeatIntervalRange(repeatIntervalRange)

{
	mTimer = CreateThreadpoolTimer(ThreadingPrivate::OnThreadpoolTimerCallback, this, &mPool->mCallBackEnviron);
}


ThreadPoolTimer::~ThreadPoolTimer(void)
{
	
	if (mTimer != nullptr)
	{
		CloseThreadpoolTimer(mTimer);
		mTimer = nullptr;
	}
}

bool ThreadPoolTimer::OnExecute()
{
	RETURN_FALSE_IF_NULL(mCommand);
	mCommand->Execute();
	if (mRepeatCount != uint(-1))
	{
		RETURN_FALSE_IF_ZERO(mRepeatCount);
		--mRepeatCount;
		RETURN_FALSE_IF_ZERO(mRepeatCount);
	}

	return true;
}
void ThreadPoolTimer::Sumbit()
{
	FILETIME startFileTime;
	ULARGE_INTEGER startTime;

	if (mDelay == 0)
	{
		startTime.QuadPart = (ULONGLONG)-1;

	}
	else
	{
		//1s==1000ms==1000*1000 qs==1000*1000*1000ns
		//in 100ns
		startTime.QuadPart = (ULONGLONG)-((int)mDelay * 1000 * 10);

	}
	startFileTime.dwLowDateTime = startTime.LowPart;
	startFileTime.dwHighDateTime = startTime.HighPart;

	SetThreadpoolTimer(mTimer, &startFileTime, mRepeatCount > 0 ? mRepeatInterval : 0, mRepeatCount > 0 ? mRepeatIntervalRange : 0);
}

void ThreadPoolTimer::Cancel()
{
	SetThreadpoolTimer(mTimer, nullptr, 0, 0);
}

void ThreadPoolTimer::Wait(bool cancelPending /*= false*/)
{
	WaitForThreadpoolTimerCallbacks(mTimer, cancelPending);
}

bool ThreadPoolTimer::IsSubmitted() const
{
	return IsThreadpoolTimerSet(mTimer) == TRUE;
}



MEDUSA_END;

#endif
