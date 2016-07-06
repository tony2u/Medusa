// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;


typedef Delegate<void(Thread&)> ThreadCallback;

class Thread :public ThreadImp, public INonCopyable
{
public:
	Thread(const StringRef& name = StringRef::Empty, ThreadCallback callback = nullptr, void* userData = nullptr);
	virtual ~Thread(void);
public:
	static ThreadHandle Current();
	static ThreadId CurrentId();

	static bool IsCurrent(ThreadId val) { return CurrentId() == val; }

#ifdef MEDUSA_WINDOWS
	static bool IsThreadEqual(ThreadHandle thread1, ThreadHandle thread2);
#endif
	static bool IsThreadEqual(ThreadId thread1, ThreadId thread2);

	static void Sleep(long milliSeconds);

	template< class Rep, class Period >
	static void Sleep(const std::chrono::duration<Rep, Period>& sleep_duration)
	{
		auto milliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(sleep_duration).count();
		Sleep(milliSeconds);
	}

	template< class Clock, class Duration >
	static void SleepUntil(const std::chrono::time_point<Clock, Duration>& sleep_time)
	{
		auto duration = sleep_time - Clock::now();
		auto milliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		Sleep(milliSeconds);
	}
public:
	bool Start();

	void PrepareToCancel() { mThreadState = ThreadState::Cancelled; }
	bool Join();
	static void YieldSelf(){ std::this_thread::yield(); }
	void Run()
	{
		RETURN_IF_FALSE(OnBeforeRun());
		mCallback.TryInvoke(*this);
		OnRun();
		OnAfterRun();
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

	ThreadPriority Priority() const { return mPriority; }
	void SetPriority(ThreadPriority val);

	ThreadingSchedulePolicy Policy() const { return mPolicy; }
	void SetPolicy(ThreadingSchedulePolicy val) { mPolicy = val; }

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	ThreadId Id()const;
protected:
	virtual bool OnBeforeRun() { return true; }
	virtual void OnRun() {}
	virtual void OnAfterRun() {}

	virtual bool OnBeforeStart() { return true; }
	virtual void OnAfterStart() {}
	virtual bool OnBeforeJoin() { return true; }
	virtual void OnAfterJoin() {}

protected:
	ThreadCallback mCallback;
	void* mUserData = nullptr;
	void* mResult = nullptr;
	ThreadingSchedulePolicy mPolicy;
	ThreadPriority mPriority;

	volatile ThreadState mThreadState;
	HeapString mName;

};


/*
#include <stack> 
#include <function>

void on_thread_exit(std::function<void()> func)
{
	class ThreadExiter
	{
		std::stack<std::function<void()>> exit_funcs;
	public:
		ThreadExiter() = default;
		ThreadExiter(ThreadExiter const&) = delete;
		void operator=(ThreadExiter const&) = delete;
		~ThreadExiter()
		{
			while (!exit_funcs.empty())
			{
				exit_funcs.top()();
				exit_funcs.pop();
			}
		}
		void add(std::function<void()> func)
		{
			exit_funcs.push(std::move(func));
		}
	};

	thread_local ThreadExiter exiter;
	exiter.add(std::move(func));
}

*/

MEDUSA_END;
