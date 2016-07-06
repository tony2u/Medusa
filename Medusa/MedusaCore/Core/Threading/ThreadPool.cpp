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

ThreadPool::WorkType ThreadPool::TrySumbitWork(Action action)
{
	ShareCommand command = new DelegateCommand(action);
	return CreateWork(command);
}

ThreadPool::WorkType ThreadPool::TrySumbitWork(ActionWithUserData action, void* userData)
{
	ShareCommand command = new DelegateCommand(Bind(action, userData));
	return CreateWork(command);
}

ThreadPool::WorkType ThreadPool::CreateWork(const StringRef& name,const ShareCommand& command)
{
	WorkType work = new ThreadPoolWork(this,name, command);
	mNamedWorks.Add(name, work);
	return work;
}

ThreadPool::WorkType ThreadPool::CreateWork(const ShareCommand& command)
{
	WorkType work = new ThreadPoolWork(this,StringRef::Empty, command);
	mUnnamedWorks.Add(work);
	return work;

}

ThreadPool::WorkType ThreadPool::FindWork(const StringRef& name) const
{
	return mNamedWorks.GetOptional(name, nullptr);
}

void ThreadPool::SubmitWork(const ThreadPool::WorkType& work)
{
	work->Sumbit();
}

void ThreadPool::SubmitWork(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	WorkType work = FindWork(name);
	RETURN_IF_NULL(work);
	SubmitWork(work);
}

void ThreadPool::WaitWork(const ThreadPool::WorkType& work, bool cancelPending /*= false*/)
{
	work->Wait(cancelPending);
}

void ThreadPool::WaitWork(const StringRef& name, bool cancelPending /*= false*/)
{
	RETURN_IF_EMPTY(name);
	ThreadPool::WorkType work = FindWork(name);
	RETURN_IF_NULL(work);
	WaitWork(work, cancelPending);
}

void ThreadPool::DeleteWork(const ThreadPool::WorkType& work)
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
}

void ThreadPool::DeleteWork(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	mNamedWorks.RemoveKey(name);
}

void ThreadPool::WaitAllWork(bool cancelPending /*= false*/)
{
	for(auto i: mNamedWorks)
	{
		auto& work = i.Value;
		work->Wait(cancelPending);
	}

	for (auto& work : mUnnamedWorks)
	{
		work->Wait(cancelPending);
	}
}


void ThreadPool::ClearAllWork()
{
	mNamedWorks.Clear();
	mUnnamedWorks.Clear();
}

#pragma endregion Work

#pragma region Timer
ThreadPool::TimerType ThreadPool::CreateTimer(const StringRef& name,const ShareCommand& command, uint delay /*= 0*/, uint repeatCount /*= 0*/, uint repeatInterval /*= 0*/, uint repeatIntervalRange /*= 0*/)
{
	ThreadPool::TimerType timer = new ThreadPoolTimer(this,name, command, delay, repeatCount, repeatInterval, repeatIntervalRange);
	mNamedTimers.Add(name, timer);
	return timer;
}

ThreadPool::TimerType ThreadPool::CreateTimer(const ShareCommand& command, uint delay /*= 0*/, uint repeatCount /*= 0*/, uint repeatInterval /*= 0*/, uint repeatIntervalRange /*= 0*/)
{
	ThreadPool::TimerType timer = new ThreadPoolTimer(this,StringRef::Empty, command, delay, repeatCount, repeatInterval, repeatIntervalRange);
	mUnnamedTimers.Add(timer);

	return timer;
}

ThreadPool::TimerType ThreadPool::FindTimer(const StringRef& name) const
{
	return mNamedTimers.GetOptional(name, nullptr);
}

void ThreadPool::SubmitTimer(const ThreadPool::TimerType& timer)
{
	timer->Sumbit();
}

void ThreadPool::SubmitTimer(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	ThreadPool::TimerType timer = FindTimer(name);
	RETURN_IF_NULL(timer);
	SubmitTimer(timer);
}

void ThreadPool::WaitTimer(const ThreadPool::TimerType& timer, bool cancelPending /*= false*/)
{
	timer->Wait(cancelPending);
}

void ThreadPool::WaitTimer(const StringRef& name, bool cancelPending /*= false*/)
{
	RETURN_IF_EMPTY(name);
	ThreadPool::TimerType timer = FindTimer(name);
	RETURN_IF_NULL(timer);
	WaitTimer(timer, cancelPending);
}

void ThreadPool::DeleteTimer(const ThreadPool::TimerType& timer)
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

}

void ThreadPool::DeleteTimer(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	mNamedTimers.RemoveKey(name);
}

void ThreadPool::WaitAllTimer(bool cancelPending /*= false*/)
{
	for (auto i : mNamedTimers)
	{
		auto& item = i.Value;
		item->Wait(cancelPending);
	}

	for (auto& item : mUnnamedTimers)
	{
		item->Wait(cancelPending);
	}
}

void ThreadPool::ClearAllTimer()
{
	mNamedTimers.Clear();
	mUnnamedTimers.Clear();

}

#pragma endregion Timer

#pragma region Wait

ThreadPool::WaitType ThreadPool::CreateWait(const StringRef& name,const ShareCommand& command, IWaitable* waitable)
{
	ThreadPool::WaitType wait = new ThreadPoolWait(this,name, command, waitable);
	mNamedWaits.Add(name, wait);
	return wait;
}

ThreadPool::WaitType ThreadPool::CreateWait(const ShareCommand& command, IWaitable* waitable)
{
	ThreadPool::WaitType wait = new ThreadPoolWait(this,StringRef::Empty, command, waitable);
	mUnnamedWaits.Add(wait);
	return wait;
}

ThreadPool::WaitType ThreadPool::FindWait(const StringRef& name) const
{
	return mNamedWaits.GetOptional(name, nullptr);

}

void ThreadPool::SubmitWait(const ThreadPool::WaitType& wait)
{
	wait->Sumbit();
}

void ThreadPool::SubmitWait(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	ThreadPool::WaitType wait = FindWait(name);
	RETURN_IF_NULL(wait);
	SubmitWait(wait);
}

void ThreadPool::WaitWait(const ThreadPool::WaitType& wait, bool cancelPending /*= false*/)
{
	wait->Wait(cancelPending);
}

void ThreadPool::WaitWait(const StringRef& name, bool cancelPending /*= false*/)
{
	RETURN_IF_EMPTY(name);
	ThreadPool::WaitType wait = FindWait(name);
	RETURN_IF_NULL(wait);
	WaitWait(wait, cancelPending);
}

void ThreadPool::DeleteWait(const ThreadPool::WaitType& wait)
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
}

void ThreadPool::DeleteWait(const StringRef& name)
{
	RETURN_IF_EMPTY(name);
	mNamedWaits.RemoveKey(name);
}

void ThreadPool::WaitAllWait(bool cancelPending /*= false*/)
{
	for (auto& i : mNamedWaits)
	{
		auto& item = i.Value;
		item->Wait(cancelPending);
	}

	for (auto& item : mUnnamedWaits)
	{
		item->Wait(cancelPending);
	}
}

void ThreadPool::ClearAllWait()
{
	mNamedWaits.Clear();
	mUnnamedWaits.Clear();
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

