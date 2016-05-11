// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Threading/ThreadPool.h"
#include "Core/Command/ICommand.h"
#include "Core/Command/DelegateCommand.h"

#include "Core/Threading/ThreadPoolWork.h"
#include "Core/Threading/ThreadPoolTimer.h"
#include "Core/Threading/ThreadPoolWait.h"
#include "Core/System/Environment.h"


MEDUSA_BEGIN;


ThreadPool::ThreadPool()
{
	
}

ThreadPool::~ThreadPool(void)
{

}

bool ThreadPool::Initialize(uint minCount /*= ThreadPool::MinCount*/, uint maxCount /*= ThreadPool::MaxCount*/, bool autoManaged /*= true*/)
{
	return InitializeHelper(minCount, maxCount, autoManaged);
}

void ThreadPool::Uninitialize()
{
	ClearAll();
	UninitialzieHelper();
}

#pragma region Work

ThreadPoolWork* ThreadPool::TrySumbitWork(Action0 action)
{
	DelegateCommand* command = new DelegateCommand(action);
	return CreateWork(command);
}

ThreadPoolWork* ThreadPool::TrySumbitWork(Action1 action, void* userData)
{
	DelegateCommand* command = new DelegateCommand(Bind(action, userData));
	return CreateWork(command);
}

ThreadPoolWork* ThreadPool::CreateWork(const StringRef& name, ICommand* command)
{
	ThreadPoolWork* work = new ThreadPoolWork(name, command);
	mNamedWorks.Add(name, work);
	return work;
}

ThreadPoolWork* ThreadPool::CreateWork(ICommand* command)
{
	ThreadPoolWork* work = new ThreadPoolWork(StringRef::Empty, command);
	mUnnamedWorks.Add(work);
	return work;

}

ThreadPoolWork* ThreadPool::FindWork(const StringRef& name) const
{
	return mNamedWorks.GetOptional(name, nullptr);
}

void ThreadPool::SubmitWork(ThreadPoolWork& work)
{
	work.Sumbit();
}

void ThreadPool::SubmitWork(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolWork* work = FindWork(name);
	RETURN_IF_NULL(work);
	SubmitWork(*work);
}

void ThreadPool::WaitWork(ThreadPoolWork& work, bool cancelPending /*= false*/)
{
	work.Wait(cancelPending);
}

void ThreadPool::WaitWork(const StringRef& name, bool cancelPending /*= false*/)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolWork* work = FindWork(name);
	RETURN_IF_NULL(work);
	WaitWork(*work, cancelPending);
}

void ThreadPool::DeleteWork(ThreadPoolWork* work)
{
	RETURN_IF_NULL(work);
	StringRef name = work->Name();
	if (name.IsEmpty())
	{
		mUnnamedWorks.Remove(work);
	}
	else
	{
		mNamedWorks.RemoveKey(name);
	}

	SAFE_RELEASE(work);
}

void ThreadPool::DeleteWork(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolWork* work = mNamedWorks.RemoveKeyOptional(name, nullptr);
	SAFE_RELEASE(work);
}

void ThreadPool::WaitAllWork(bool cancelPending /*= false*/)
{
	FOR_EACH_COLLECTION(i, mNamedWorks)
	{
		ThreadPoolWork* work = i->Value;
		work->Wait(cancelPending);
	}

	FOR_EACH_COLLECTION(i, mUnnamedWorks)
	{
		ThreadPoolWork* work = *i;
		work->Wait(cancelPending);
	}
}


void ThreadPool::ClearAllWork()
{
	SAFE_RELEASE_DICTIONARY_VALUE(mNamedWorks);
	SAFE_RELEASE_COLLECTION(mUnnamedWorks);
}

#pragma endregion Work

#pragma region Timer
ThreadPoolTimer* ThreadPool::CreateTimer(const StringRef& name, ICommand* command, uint delay /*= 0*/, uint repeatCount /*= 0*/, uint repeatInterval /*= 0*/, uint repeatIntervalRange /*= 0*/)
{
	ThreadPoolTimer* timer = new ThreadPoolTimer(name, command, delay, repeatCount, repeatInterval, repeatIntervalRange);
	mNamedTimers.Add(name, timer);
	return timer;
}

ThreadPoolTimer* ThreadPool::CreateTimer(ICommand* command, uint delay /*= 0*/, uint repeatCount /*= 0*/, uint repeatInterval /*= 0*/, uint repeatIntervalRange /*= 0*/)
{
	ThreadPoolTimer* timer = new ThreadPoolTimer(StringRef::Empty, command, delay, repeatCount, repeatInterval, repeatIntervalRange);
	mUnnamedTimers.Add(timer);

	return timer;
}

ThreadPoolTimer* ThreadPool::FindTimer(const StringRef& name) const
{
	return mNamedTimers.GetOptional(name, nullptr);
}

void ThreadPool::SubmitTimer( ThreadPoolTimer& timer)
{
	timer.Sumbit();
}

void ThreadPool::SubmitTimer(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolTimer* timer = FindTimer(name);
	RETURN_IF_NULL(timer);
	SubmitTimer(*timer);
}

void ThreadPool::WaitTimer( ThreadPoolTimer& timer, bool cancelPending /*= false*/)
{
	timer.Wait(cancelPending);
}

void ThreadPool::WaitTimer(const StringRef& name, bool cancelPending /*= false*/)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolTimer* timer = FindTimer(name);
	RETURN_IF_NULL(timer);
	WaitTimer(*timer, cancelPending);
}

void ThreadPool::DeleteTimer(ThreadPoolTimer* timer)
{
	RETURN_IF_NULL(timer);
	StringRef name = timer->Name();
	if (name.IsEmpty())
	{
		mUnnamedTimers.Remove(timer);
	}
	else
	{
		mNamedTimers.RemoveKey(name);
	}

	SAFE_RELEASE(timer);

}

void ThreadPool::DeleteTimer(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolTimer* timer = mNamedTimers.RemoveKeyOptional(name, nullptr);
	SAFE_RELEASE(timer);
}

void ThreadPool::WaitAllTimer(bool cancelPending /*= false*/)
{
	FOR_EACH_COLLECTION(i, mNamedTimers)
	{
		ThreadPoolTimer* item = i->Value;
		item->Wait(cancelPending);
	}

	FOR_EACH_COLLECTION(i, mUnnamedTimers)
	{
		ThreadPoolTimer* item = *i;
		item->Wait(cancelPending);
	}
}

void ThreadPool::ClearAllTimer()
{
	SAFE_RELEASE_DICTIONARY_VALUE(mNamedTimers);
	SAFE_RELEASE_COLLECTION(mUnnamedTimers);
}

#pragma endregion Timer

#pragma region Wait

ThreadPoolWait* ThreadPool::CreateWait(const StringRef& name, ICommand* command, IWaitable* waitable)
{
	ThreadPoolWait* wait = new ThreadPoolWait(name, command, waitable);
	mNamedWaits.Add(name, wait);
	return wait;
}

ThreadPoolWait* ThreadPool::CreateWait(ICommand* command, IWaitable* waitable)
{
	ThreadPoolWait* wait = new ThreadPoolWait(StringRef::Empty, command, waitable);
	mUnnamedWaits.Add(wait);
	return wait;
}

ThreadPoolWait* ThreadPool::FindWait(const StringRef& name) const
{
	return mNamedWaits.GetOptional(name, nullptr);

}

void ThreadPool::SubmitWait( ThreadPoolWait& wait)
{
	wait.Sumbit();
}

void ThreadPool::SubmitWait(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolWait* wait = FindWait(name);
	RETURN_IF_NULL(wait);
	SubmitWait(*wait);
}

void ThreadPool::WaitWait( ThreadPoolWait& wait, bool cancelPending /*= false*/)
{
	wait.Wait(cancelPending);
}

void ThreadPool::WaitWait(const StringRef& name, bool cancelPending /*= false*/)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolWait* wait = FindWait(name);
	RETURN_IF_NULL(wait);
	WaitWait(*wait, cancelPending);
}

void ThreadPool::DeleteWait(ThreadPoolWait* wait)
{
	RETURN_IF_NULL(wait);
	StringRef name = wait->Name();
	if (name.IsEmpty())
	{
		mUnnamedWaits.Remove(wait);
	}
	else
	{
		mNamedWaits.RemoveKey(name);
	}

	SAFE_RELEASE(wait);
}

void ThreadPool::DeleteWait(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	ThreadPoolWait* wait = mNamedWaits.RemoveKeyOptional(name, nullptr);
	SAFE_RELEASE(wait);
}

void ThreadPool::WaitAllWait(bool cancelPending /*= false*/)
{
	FOR_EACH_COLLECTION(i, mNamedWaits)
	{
		ThreadPoolWait* item = i->Value;
		item->Wait(cancelPending);
	}

	FOR_EACH_COLLECTION(i, mUnnamedWaits)
	{
		ThreadPoolWait* item = *i;
		item->Wait(cancelPending);
	}
}

void ThreadPool::ClearAllWait()
{
	SAFE_RELEASE_DICTIONARY_VALUE(mNamedWaits);
	SAFE_RELEASE_COLLECTION(mUnnamedWaits);
}


#pragma endregion Wait

void ThreadPool::WaitAll(bool cancelPending /*= false*/)
{
	WaitAllWork(cancelPending);
	WaitAllTimer(cancelPending);
	WaitAllWait(cancelPending);
}

void ThreadPool::ClearAll()
{
	ClearAllWork();
	ClearAllTimer();
	ClearAllWait();
}

MEDUSA_END;

