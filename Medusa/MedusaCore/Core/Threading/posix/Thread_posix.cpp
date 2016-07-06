// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/Thread.h"

MEDUSA_BEGIN;


namespace ThreadingPrivate
{
#ifdef MEDUSA_DEBUG
	void SetThreadName(pthread_t thread, const char* threadName)
	{
#ifdef MEDUSA_IOS
		pthread_setname_np(threadName); // __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2)
#else
#ifndef MEDUSA_WINDOWS
		pthread_setname_np(thread, threadName);

#endif
#endif
	}

#endif


	int ToOSThreadPriority(ThreadPriority priority, ThreadingSchedulePolicy policy)
	{
		int min = sched_get_priority_min((int)policy);
		int max = sched_get_priority_max((int)policy);
		switch (priority)
		{
			case ThreadPriority::Lowest:
				return min;
			case ThreadPriority::Low:
				return min + (max - min) / 4;
			case ThreadPriority::Normal:
				return  (max + min) / 2;
			case ThreadPriority::High:
				return max - (max - min) / 4;
			case ThreadPriority::Highest:
				return max;
			default:
				return priority;
		}
	}

	void* OnThreadCallback(void* userData)
	{
		Thread* currentThread = (Thread*)userData;
#ifdef MEDUSA_DEBUG
		ThreadingPrivate::SetThreadName(currentThread->Id(),currentThread->Name().c_str());
#endif

		currentThread->Run();

		return nullptr;
	}
}



Thread::Thread(const StringRef& name/*=StringRef::Empty*/, ThreadCallback callback/*=ThreadCallback::Empty*/, void* userData /*= nullptr*/)
	: mCallback(callback),
	mUserData(userData),
	mResult(nullptr),
	mPolicy(ThreadingSchedulePolicy::Default),
	mPriority(ThreadPriority::Normal),
	mThreadState(ThreadState::None),
	mName(name)
{
	mThread = 0;
}


Thread::~Thread(void)
{
	mThread = 0;
}

ThreadHandle Thread::Current()
{
    return pthread_self();
}

ThreadId Thread::CurrentId()
{
	return pthread_self();
}

bool Thread::IsThreadEqual(ThreadHandle thread1, ThreadHandle thread2)
{
	return pthread_equal(thread1, thread2) != 0;
}


void Thread::Sleep(long milliSeconds)
{
#ifndef MEDUSA_WINDOWS
	::sleep((uint)milliSeconds);
#endif

}

void Thread::SetPriority(ThreadPriority val)
{
	RETURN_IF_EQUAL(mPriority, val);
	mPriority = val;
	if (mThread!=0)
	{
		sched_param par;
		par.sched_priority = ThreadingPrivate::ToOSThreadPriority(mPriority, mPolicy);
		pthread_setschedparam(mThread, (int)mPolicy, &par);
	}
}

bool Thread::Start()
{
	if (mThreadState != ThreadState::None)
	{
		return true;
	}
	OnBeforeStart();

	int result = pthread_create(&mThread, nullptr, ThreadingPrivate::OnThreadCallback, this);
	if (result == 0)
	{
		mThreadState = ThreadState::Running;
		if (mPriority != ThreadPriority::Normal)
		{
			SetPriority(mPriority);
		}
	}
	OnAfterStart();
	return result == 0;
}

bool Thread::Join()
{
	RETURN_TRUE_IF_FALSE(mThreadState != ThreadState::Running);
	OnBeforeJoin();
	mThreadState = ThreadState::Cancelled;
	if (pthread_join(mThread, &mResult) == 0)
	{
		mThreadState = ThreadState::None;
		OnAfterJoin();
		return true;
	}

	return false;
}

ThreadId Thread::Id() const
{
	return mThread;
}


MEDUSA_END;
#endif
