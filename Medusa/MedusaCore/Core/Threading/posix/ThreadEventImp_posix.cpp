// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING

#include "Core/Threading/posix/ThreadEventImp_posix.h"

MEDUSA_BEGIN;

ThreadEventImp::ThreadEventImp()
{

}

ThreadEventImp::~ThreadEventImp(void)
{

}


ThreadEventImp::ThreadEventMultipleWaiter::ThreadEventMultipleWaiter(uint count, bool isWaitAll)
{
	pthread_cond_init(&Cond, nullptr);
	IsWaitAll = isWaitAll;
	if (isWaitAll)
	{
		EventsLeftCount = count;
	}
	else
	{
		FiredEventIndex = -1;
	}
}

ThreadEventImp::ThreadEventMultipleWaiter::~ThreadEventMultipleWaiter()
{
	pthread_cond_destroy(&Cond);

}


ThreadEventImp::ThreadEventMultipleWaiterIndex::ThreadEventMultipleWaiterIndex(ThreadEventMultipleWaiter* waiter, int index)
	:Waiter(waiter), Index(index)
{

}

bool ThreadEventImp::TryWaitWithoutLock()
{
	if (!mState)
	{
		return false;
	}
	else
	{
		if (mIsAutoReset)
		{
			//It's an auto-reset event that's currently available;
			//we need to stop anyone else from using it
			mState = false;
		}
		//Else we're trying to obtain a manual reset event with a signaled state;
		//don't do anything
		return true;
	}
}

#ifdef MEDUSA_THREADING_MULTIPLE_WAIT

void ThreadEventImp::TryRemoveExpiredWaitsWithoutLock(ThreadEventMultipleWaiter* waiter)
{
	RETURN_IF_EMPTY(mRegisteredWaits);

	//has been locked outside
	uint waitCount = mRegisteredWaits.Count();
	FOR_EACH_SIZE(i, waitCount)
	{
		ThreadEventMultipleWaiterIndex& index = mRegisteredWaits[i];

		if (index.Waiter == waiter)
		{
			mRegisteredWaits.RemoveAt(i);
			break;
		}
	}

}

void ThreadEventImp::RegisterWaitWithoutLock(ThreadEventMultipleWaiter* waiter, int index)
{
	ThreadEventMultipleWaiterIndex waiterIndex(waiter, index);
	mRegisteredWaits.Push(waiterIndex);
}
#endif


MEDUSA_END;

#endif