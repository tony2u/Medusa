// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING

#include "Core/Threading/ThreadEvent.h"

MEDUSA_BEGIN;



ThreadEvent::ThreadEvent(bool autoReset /*= true*/, bool isSet /*= false*/, bool isInitializeNow /*= true*/)
{
	mEvent = nullptr;
	mIsAutoReset = autoReset;
	if (isInitializeNow)
	{
		Initialize(autoReset);
	}
}

ThreadEvent::~ThreadEvent()
{
	Uninitialize();
}

void ThreadEvent::Initialize(bool autoReset /*= true*/, bool isSet /*= false*/)
{
	mIsAutoReset = autoReset;
	if (mEvent == nullptr)
	{
		mEvent = CreateEventW(nullptr, mIsAutoReset ? FALSE : TRUE, isSet ? TRUE : FALSE, nullptr);
	}
}

void ThreadEvent::Uninitialize()
{
	if (mEvent != nullptr)
	{
		CloseHandle(mEvent);
		mEvent = nullptr;
	}

}

void ThreadEvent::Set()
{
	SetEvent(mEvent);
}

bool ThreadEvent::IsSet()const
{
	return WaitForSingleObject(mEvent, 0) == WAIT_OBJECT_0;
}

void ThreadEvent::Reset()
{
	ResetEvent(mEvent);
}

bool ThreadEvent::Wait()
{
	return WaitForSingleObject(mEvent, INFINITE) == WAIT_OBJECT_0;
}

bool ThreadEvent::TryWait()
{
	return WaitForSingleObject(mEvent, 0) == WAIT_OBJECT_0;
}

bool ThreadEvent::WaitTimeout(long milliseconds)
{
	return WaitForSingleObject(mEvent, milliseconds) == WAIT_OBJECT_0;
}


#ifdef MEDUSA_THREADING_MULTIPLE_WAIT

bool ThreadEvent::WaitForMultipleEvents(const List<ThreadEvent*>& events, bool waitAll, long milliseconds, int& outWaitIndex)
{
	List<HANDLE> handleList;
	FOR_EACH_COLLECTION(i, events)
	{
		ThreadEvent* e = *i;
		handleList.Add(e->mEvent);
	}

	int result = WaitForMultipleObjects(handleList.Count(), handleList.Items(), waitAll, milliseconds);
	if (result == WAIT_TIMEOUT || result == WAIT_FAILED)
	{
		outWaitIndex = -1;
		return false;
	}

	if (result>=WAIT_ABANDONED_0)
	{
		if (waitAll)
		{
			outWaitIndex = 0;
		}
		else
		{
			outWaitIndex = result - WAIT_ABANDONED_0;
		}
		return false;
	}

	if (waitAll)
	{
		outWaitIndex = 0;
	}
	else
	{
		outWaitIndex = result - WAIT_OBJECT_0;
	}
	return true;
}

#endif

MEDUSA_END;

#endif