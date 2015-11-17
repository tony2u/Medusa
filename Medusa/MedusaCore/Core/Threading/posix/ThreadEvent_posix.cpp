// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING

#include "Core/Threading/ThreadEvent.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Threading/ScopedUnlock.h"
#include "Core/Profile/PerformanceCounter.h"


MEDUSA_BEGIN;

/*
recommended pthread_cond_wait() and pthread_cond_signal() usage:
pthread_mutex_lock(&m);
while( condition_is_false )
pthread_cond_wait(&cond, &m);
pthread_mutex_unlock(&m);

another side:
pthread_mutex_lock(&m); // pthread_cond_wait unlock automatically
......
pthread_cond_signal(&v);
pthread_mutex_unlock(&m); // make pthread_cond_wait can get lock automatically

pthread_cond_wait() return don't have to means condition's value has been changed,also maybe error occurs, so have to recheck condition's value, use while() to check for example
*/

ThreadEvent::ThreadEvent(bool autoReset /*= true*/, bool isSet /*= false*/, bool isInitializeNow /*= true*/)
{
	mIsAutoReset = autoReset;
	mCond = PTHREAD_COND_INITIALIZER;
	if (isInitializeNow)
	{
		mState = isSet;
		Initialize(autoReset, isSet);
	}
}

ThreadEvent::~ThreadEvent()
{
	Uninitialize();
}

void ThreadEvent::Initialize(bool autoReset /*= true*/, bool isSet /*= false*/)
{
	mIsAutoReset = autoReset;
	
		mMutex.Initialize();
		::pthread_cond_init(&mCond, nullptr);
		mState = isSet;
	
}

void ThreadEvent::Uninitialize()
{
    ::pthread_cond_destroy(&mCond);
    mCond = PTHREAD_COND_INITIALIZER;

}

void ThreadEvent::Set()
{
	ScopedLock lock(mMutex);

	mState = true;
	if (mIsAutoReset)
	{
#ifdef MEDUSA_THREADING_MULTIPLE_WAIT
		if (!mRegisteredWaits.IsEmpty())
		{
			ThreadEventMultipleWaiterIndex& waiterIndex = mRegisteredWaits.First();
			mRegisteredWaits.RemoveFirst();
			ThreadEventMultipleWaiter* waiter = waiterIndex.Waiter;
			waiter->Mutex.Lock();

			//only open one wait
			mState = false;

			if (waiter->IsWaitAll)
			{
				--waiter->EventsLeftCount;
			}
			else
			{
				waiter->FiredEventIndex = waiterIndex.Index;
			}


			//wake up wait for multiple events
			pthread_cond_signal(&waiter->Cond);
			waiter->Mutex.Unlock();
			return;
		}
#endif
		//wake up single wait
		mState = false;
		pthread_cond_signal(&mCond);

	}
	else
	{
#ifdef MEDUSA_THREADING_MULTIPLE_WAIT

		if (!mRegisteredWaits.IsEmpty())
		{
			FOR_EACH_COLLECTION(i, mRegisteredWaits)
			{
				ThreadEventMultipleWaiterIndex& waiterIndex = *i;
				ThreadEventMultipleWaiter* waiter = waiterIndex.Waiter;
				waiter->Mutex.Lock();

				if (waiter->IsWaitAll)
				{
					--waiter->EventsLeftCount;
				}
				else
				{
					waiter->FiredEventIndex = waiterIndex.Index;
				}

				//wake up wait for multiple events
				pthread_cond_signal(&waiter->Cond);
				waiter->Mutex.Unlock();

			}
			mRegisteredWaits.Clear();
		}
#endif

		//also wake up others if itself is a manual set event
		::pthread_cond_broadcast(&mCond);
	}
}

void ThreadEvent::Reset()
{
	ScopedLock lock(mMutex);
	mState = false;
}


bool ThreadEvent::Wait()
{
	ScopedLock lock(mMutex);

	int r = 0;
	while (!mState&&r == 0)
	{
		r = pthread_cond_wait(&mCond, &mMutex.mMutex);
	}
	if (mIsAutoReset)
	{
		mState = false;
	}
	return true;
}

bool ThreadEvent::IsSet()const
{
	ScopedLock lock(mMutex);
	return mState;
}

bool ThreadEvent::TryWait()
{
	if (!mMutex.TryLock())
	{
		return false;
	}

	ScopedUnlock unlock(mMutex);
	return TryWaitWithoutLock();
}

bool ThreadEvent::WaitTimeout(long milliseconds)
{
	ScopedLock lock(mMutex);
	if (!mState)
	{
		int result = 0;

		if (milliseconds == -1)
		{
			//infinite wait

			do
			{
				result = pthread_cond_wait(&mCond, &mMutex.mMutex);
			} while (!mState&&result == 0);
		}
		else
		{
			struct timespec abstime = PerformanceCounter::ToAbsoluteTime(milliseconds);
			do
			{
				result = pthread_cond_timedwait(&mCond, &mMutex.mMutex, &abstime);

			} while (!mState&&result == 0);
		}

		if (result == 0 && mIsAutoReset)
		{
			//We've only acquired the event if the wait succeeded
			mState = false;
		}
		return true;
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
bool ThreadEvent::WaitForMultipleEvents(const List<ThreadEvent*>& events, bool waitAll, long milliseconds, int& outWaitIndex)
{
	outWaitIndex = -1;
	uint count = events.Count();

	ThreadEvent::ThreadEventMultipleWaiter waiter(count, waitAll);
	waiter.Mutex.Lock();

	bool isComplete = false;

	//register all events to wait 
	FOR_EACH_SIZE(i, count)
	{
		ThreadEvent* threadEvent = events[i];
		threadEvent->mMutex.Lock();
		if (threadEvent->TryWaitWithoutLock())
		{
			//this event has been set
			threadEvent->mMutex.Unlock();
			if (waitAll)
			{
				isComplete = i == count - 1;
			}
			else
			{
				waiter.FiredEventIndex = i;
				outWaitIndex = i;
				isComplete = true;
				break;
			}
		}
		else if (milliseconds != 0)
		{
			threadEvent->RegisterWaitWithoutLock(&waiter, i);
			threadEvent.mMutex.Unlock();
		}
	}

	//wait waiter's event to be signaled
	bool waitResult = true;
	if (!isComplete)
	{
		if (milliseconds == 0)
		{
			//timeout,do nothings
			waitResult = false;
		}
		else if (milliseconds == -1)
		{
			int r = 0;
			while (!isComplete&&r == 0)
			{
				r = pthread_cond_wait(&waiter.Cond, &waiter.Mutex.mMutex);
				isComplete = (waitAll&&waiter.EventsLeftCount == 0) || (!waitAll&&waiter.FiredEventIndex != -1);
			}
			waitResult = r == 0;
		}
		else
		{
			struct timespec abstime = PerformanceCounter::ToAbsoluteTime(milliseconds);

			int r = 0;
			while (!isComplete&&r == 0)
			{
				r = pthread_cond_timedwait(&waiter.Cond, &waiter.Mutex.mMutex, &abstime);
				isComplete = (waitAll&&waiter.EventsLeftCount == 0) || (!waitAll&&waiter.FiredEventIndex != -1);

			}
			waitResult = r == 0;
		}
	}

	outWaitIndex = waiter.EventsLeftCount;

	//remove expired event registered wait
	if (milliseconds != 0)
	{
		FOR_EACH_SIZE(i, count)
		{
			ThreadEvent* threadEvent = events[i];
			threadEvent->mMutex.Lock();
			threadEvent->TryRemoveExpiredWaitsWithoutLock(&waiter);
			threadEvent->.mMutex.Unlock();
		}

	}

	waiter.Mutex.Unlock();
	return waitResult;

}

#endif

MEDUSA_END;
#endif