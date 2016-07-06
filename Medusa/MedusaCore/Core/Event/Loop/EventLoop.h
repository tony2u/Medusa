// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/INonCopyable.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Command/Executor/TSyncCommandExecutor.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Threading/ThreadEvent.h"
#include "Core/Event/Timer/TimerQueue.h"

MEDUSA_BEGIN;

class EventLoop :public INonCopyable
{
public:
	const static uint PollTimeoutMilliseconds;
public:
	EventLoop();
	~EventLoop(void);
public:
	IPoller* Poller() const { return mPoller; }
	void SetPoller(IPoller* val);
	ThreadId CurrentThread() const { return mCurrentThread; }
	void SetCurrentThread(ThreadId val) { mCurrentThread = val; }
	void AttachToCurrentThread();

	bool IsInLoop()const;
	void AssertInLoopThread()const;
	bool LoopForever();
	bool LoopOnce();

	void Stop();
public:
	void AddChannel(IEventChannel* channel);
	bool RemoveChannel(IEventChannel* channel);
public:
	void RunInLoop(const Action& action);
	void QueueInLoop(const Action& action);

	void RunAfter(const Action& action, uint delayMilliseconds, uint repeatMilliseconds = 0, uint repeatCount = Math::UIntMaxValue);
	void RunWhen(const Action& action, TimerQueue::TimePoint timePointFromNow, uint repeatMilliseconds = 0, uint repeatCount = Math::UIntMaxValue);
protected:
	bool LoopOnceHelper();

protected:
	ThreadId mCurrentThread = 0;

	//channels
	IPoller* mPoller = nullptr;
	//events
	TSyncCommandExecutor<ICommand,ScopedLock> mCommandProcessor;
	//timers

	std::atomic_bool mIsLooping = false;
	std::atomic_bool mIsCanceld = false;

	ThreadEvent mStartEvent;

	TimerQueue mTimerQueue;
};

MEDUSA_END;
