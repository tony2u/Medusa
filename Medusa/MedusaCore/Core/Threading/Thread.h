// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;


typedef Delegate<void(Thread&)> ThreadCallback;

class Thread :public ThreadImp
{
public:
	Thread(const StringRef& name = StringRef::Empty, ThreadCallback callback=nullptr, void* userData = nullptr);
	~Thread(void);
public:
	static ThreadHandle Current();
	static ThreadId CurrentId();

	static bool IsThreadEqual(ThreadHandle thread1, ThreadHandle thread2);

	static void Sleep(long milliSeconds);
public:
	bool Start();

	void PrepareToCancel() { mThreadState = ThreadState::Cancelled; }
	bool Join();
	static void YieldSelf();
	void Run()
	{
		mCallback.TryInvoke(*this);
	}

public:
	void SetCallback(const ThreadCallback& val) { mCallback = val; }

	void* UserData() const { return mUserData; }
	void SetUserData(void* val) { mUserData = val; }
	void* Result() const { return mResult; }
	bool IsRunning()const { return mThreadState != ThreadState::None; }
	bool IsCancelled()const { return mThreadState == ThreadState::Cancelled; }

	ThreadState State() const { return mThreadState; }
	void SetThreadState(ThreadState val) { mThreadState = val; }

	ThreadPriority::ThreadPriority_t Priority() const { return mPriority; }
	void SetPriority(ThreadPriority::ThreadPriority_t val);

	ThreadingSchedulePolicy Policy() const { return mPolicy; }
	void SetPolicy(ThreadingSchedulePolicy val) { mPolicy = val; }

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	ThreadId Id()const;
protected:
	ThreadCallback mCallback;

	void* mUserData=nullptr;
	void* mResult=nullptr;
	ThreadingSchedulePolicy mPolicy;
	ThreadPriority::ThreadPriority_t mPriority;

	volatile ThreadState mThreadState;
	HeapString mName;

};


MEDUSA_END;
