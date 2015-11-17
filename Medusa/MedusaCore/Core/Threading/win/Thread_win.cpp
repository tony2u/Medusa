// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING

#include "Core/Threading/Thread.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_DEBUG
namespace ThreadingPrivate
{
	/// See <http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx> 
	/// and <http://blogs.msdn.com/b/stevejs/archive/2005/12/19/505815.aspx> for
	/// more information on the code below.

	const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType;     // Must be 0x1000.
		LPCSTR szName;    // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags;    // Reserved for future use, must be zero.
	} THREADNAME_INFO;
#pragma pack(pop)

	void SetThreadName(DWORD dwThreadID, const char* threadName)
	{
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName;
		info.dwThreadID = dwThreadID;
		info.dwFlags = 0;

		__try
		{
			RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
		}
		__except (EXCEPTION_CONTINUE_EXECUTION)
		{
		}
	}
}

#endif


#if defined(_DLL)
typedef DWORD(WINAPI *ThreadCallbackHelper)(LPVOID);
DWORD WINAPI OnThreadCallback(LPVOID userData)
#else
typedef unsigned(__stdcall *ThreadCallbackHelper)(void*);
unsigned __stdcall OnThreadCallback(void* userData)
#endif
{
	Thread* currentThread = (Thread*)userData;
#ifdef MEDUSA_DEBUG
	ThreadingPrivate::SetThreadName((DWORD)-1, currentThread->Name().c_str());
#endif

	currentThread->Run();

	return 0;
}

Thread::Thread(const StringRef& name/*=StringRef::Empty*/, ThreadCallback callback/*=ThreadCallback::Empty*/, void* userData /*= nullptr*/)
	:mName(name), mCallback(callback), 
	mUserData(userData),
	mPolicy(ThreadingSchedulePolicy::Default),
	mPriority(ThreadPriority::Normal),
	mResult(nullptr),
	mThreadState(ThreadState::None)

{
	mThread = nullptr;
}


Thread::~Thread(void)
{
	if (mThread != nullptr)
	{
		CloseHandle(mThread);
		mThread = nullptr;
	}
}


void Thread::SetPriority(ThreadPriority::ThreadPriority_t val)
{
	RETURN_IF_EQUAL(mPriority, val);
	mPriority = val;
	if (mThread != nullptr)
	{
		SetThreadPriority(mThread, val);
	}
}

ThreadHandle Thread::Current()
{
	return ::GetCurrentThread();
}

ThreadId Thread::CurrentId()
{
	return ::GetCurrentThreadId();
}

bool Thread::IsThreadEqual(ThreadHandle thread1, ThreadHandle thread2)
{
	return thread1 == thread2;
}


void Thread::Sleep(long milliSeconds)
{
	::Sleep(milliSeconds);
}
void Thread::YieldSelf()
{
	Sleep(0);
}

bool Thread::Start()
{
	if (mThreadState != ThreadState::None)
	{
		return true;
	}

#ifdef _DLL
	mThread = CreateThread(nullptr, 0, OnThreadCallback, this, 0, &mThreadId);
#else
	mThread = (HANDLE)_beginthreadex(nullptr, 0, OnThreadCallback, this, 0, (uint*)&mThreadId);
#endif
	if (mThread != 0)
	{
		if (mPriority != ThreadPriority::Normal)
		{
			SetThreadPriority(mThread, mPriority);
		}
		mThreadState = ThreadState::Running;
		return true;
	}

	return false;
}

bool Thread::Join()
{
	RETURN_TRUE_IF_FALSE(mThreadState == ThreadState::Running);
	mThreadState = ThreadState::Cancelled;

	if (WaitForSingleObject(mThread, INFINITE) == WAIT_OBJECT_0)
	{
		mThreadState = ThreadState::None;
		return true;
	}

	return false;
}

ThreadId Thread::Id() const
{
	return mThreadId;
}


MEDUSA_END;
#endif