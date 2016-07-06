// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "EventLoop.h"
#include "Core/Threading/Thread.h"
#include "Core/Log/Log.h"
#include "Core/Event/Poll/IPoller.h"

MEDUSA_BEGIN;
const uint EventLoop::PollTimeoutMilliseconds = 1000U;

EventLoop::EventLoop()
{
	AttachToCurrentThread();
	mStartEvent.Initialize(true, true);
}

EventLoop::~EventLoop(void)
{
	SAFE_DELETE(mPoller);
}

void EventLoop::SetPoller(IPoller* val)
{
	SAFE_ASSIGN(mPoller, val);
	mPoller->SetLoop(this);
}

void EventLoop::AttachToCurrentThread()
{
	mCurrentThread = Thread::CurrentId();
}

bool EventLoop::IsInLoop() const
{
	return Thread::IsCurrent(mCurrentThread);
}


void EventLoop::AssertInLoopThread() const
{
	Log::AssertFormat(IsInLoop(), "AssertInLoopThread failed.Current:{} vs self:{}", Thread::CurrentId(), mCurrentThread);
}


bool EventLoop::LoopForever()
{
	AssertInLoopThread();
	mIsLooping = true;
	mIsCanceld = false;

	while (!mIsCanceld.load(std::memory_order_acquire))
	{
		LoopOnceHelper();
	}

	mIsLooping = false;
	return true;
}

bool EventLoop::LoopOnce()
{
	AssertInLoopThread();
	mIsLooping = true;

	bool result = LoopOnceHelper();

	mIsLooping = false;
	return result;
}


bool EventLoop::LoopOnceHelper()
{
	mCommandProcessor.WaitForComplete();
	mTimerQueue.Tick();

	if (mPoller != nullptr && !mPoller->IsEmpty())
	{
		auto result= mPoller->Poll(10);
		if (result==ChannelEventResult::None&&mCommandProcessor.HasBack() && mTimerQueue.IsEmpty())
		{
			//no event
			Thread::Sleep(1);
		}
	}
	else
	{
		if (!mCommandProcessor.HasBack()&&mTimerQueue.IsEmpty())
		{
			mStartEvent.Wait();
		}
		else
		{
			mTimerQueue.SleepInterval();
		}
	}

	return true;
}


void EventLoop::Stop()
{
	mIsCanceld = true;
}

void EventLoop::AddChannel(IEventChannel* channel)
{
	mPoller->AddChannel(channel);
	mStartEvent.Set();
}

bool EventLoop::RemoveChannel(IEventChannel* channel)
{
	mCommandProcessor.WaitForComplete();	//have to complete all events to prevent delegates still using this channel
	return mPoller->RemoveChannel(channel);
}

void EventLoop::RunInLoop(const Action& action)
{
	if (IsInLoop())
	{
		action();
	}
	else
	{
		QueueInLoop(action);
	}
}

void EventLoop::QueueInLoop(const Action& action)
{
	mCommandProcessor.ExecuteAsync(action);
	mStartEvent.Set();

}


void EventLoop::RunAfter(const Action& action, uint delayMilliseconds, uint repeatMilliseconds /*= 0*/, uint repeatCount /*= Math::UIntMaxValue*/)
{
	mTimerQueue.ScheduleDelay(action, TimerQueue::Duration(delayMilliseconds), TimerQueue::Duration(repeatMilliseconds), repeatCount);
	mStartEvent.Set();

}

void EventLoop::RunWhen(const Action& action, TimerQueue::TimePoint timePointFromNow, uint repeatMilliseconds /*= 0*/, uint repeatCount /*= Math::UIntMaxValue*/)
{
	mTimerQueue.Schedule(action, timePointFromNow, TimerQueue::Duration(repeatMilliseconds), repeatCount);
}

MEDUSA_END;
