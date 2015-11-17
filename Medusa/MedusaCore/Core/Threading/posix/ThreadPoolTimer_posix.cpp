// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadPoolTimer.h"
#include "Core/Threading/ThreadPool.h"
#include "Core/Threading/Thread.h"
#include "Core/Math/Random/Random.h"

MEDUSA_BEGIN;


ThreadPoolTimer::ThreadPoolTimer(const StringRef& name, ICommand* command, uint delay /*= 0*/, uint repeatCount /*= 0*/, uint repeatInterval /*= 0*/, uint repeatIntervalRange/*=0*/)
	:mName(name), mCommand(command), mDelay(delay), mRepeatCount(repeatCount), mRepeatInterval(repeatInterval), mRepeatIntervalRange(repeatIntervalRange)
{
	SAFE_RETAIN(command);
	mIsSubmitted = false;
	mIsCancelled = false;
}


ThreadPoolTimer::~ThreadPoolTimer(void)
{
	SAFE_RELEASE(mCommand);
}

bool ThreadPoolTimer::OnExecute()
{
	if (mIsCancelled)
	{
		mCompleteEvent.Set();
		return false;
	}

	mWatch.Shot();
	if (mDelay > 0)
	{
		uint elapsed = (uint)mWatch.ElapsedMilliseconds();
		if (elapsed < mDelay)
		{
			Thread::Sleep(mDelay - elapsed);
		}
	}
	mWatch.Step();
	Random random;
	do 
	{
		//check to avoid execute
		if (mIsCancelled)
		{
			mCompleteEvent.Set();
			return false;
		}

		if (mCommand != nullptr)
		{
			mCommand->Execute();
		}

		//double check to avoid sleep
		if (mIsCancelled)
		{
			mCompleteEvent.Set();
			return false;
		}

		if (mRepeatCount != uint(-1))
		{
			BREAK_IF_ZERO(mRepeatCount);
			--mRepeatCount;
			BREAK_IF_ZERO(mRepeatCount);
		}

		//wait repeat interval
		uint interval = mRepeatInterval;
		if (mRepeatIntervalRange!=0)
		{
			interval += random.Next(-(int)mRepeatIntervalRange, (int)mRepeatIntervalRange);
		}

		if (interval>0)
		{
			Thread::Sleep(interval);
		}
	} while (true);
	

	mCompleteEvent.Set();
	return true;
}
void ThreadPoolTimer::Sumbit()
{
	mWatch.Start();
	ThreadPool::Instance().Enqueue(this);
	mIsSubmitted = true;
}

void ThreadPoolTimer::Cancel()
{
	mIsCancelled = true;
}

void ThreadPoolTimer::Wait(bool cancelPending /*= false*/)
{
	if (cancelPending)
	{
		//find current pending work in thread pool
		ThreadPool::Instance().CancelPendingCommands(this);
	}
	mCompleteEvent.Wait();
}

bool ThreadPoolTimer::IsSubmitted() const
{
	return mIsSubmitted;
}



MEDUSA_END;

#endif
