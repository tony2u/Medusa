// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/PriorityQueue.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

template<typename TCallBack, size_t TInterval = 10,typename TDuration = std::chrono::milliseconds, typename TClock = std::chrono::high_resolution_clock>
class TTimerQueue
{
public:
	using TimePoint = std::chrono::time_point<TClock>;
	using Duration = TDuration;
public:
	struct Timer
	{
		Timer(TCallBack&& callback, TimePoint&& when, TDuration&& repeatDuration, uint repeatCount)
			:Callback(callback), When(when), RepeatDuration(repeatDuration), RepeatCount(repeatCount)
		{

		}

		TCallBack Callback;
		TimePoint When;
		uint RepeatCount = Math::UIntMaxValue;	//UIntMaxValue:repeat forever,others indicate a count
		TDuration RepeatDuration;	//0 

		bool IsRepeat()const
		{
			return RepeatDuration != TDuration::zero() && RepeatCount > 0;
		}

		void Fire()
		{
			if (RepeatCount != Math::UIntMaxValue)
			{
				--RepeatCount;
			}
		}

		int Compare(const Timer& val)const
		{
			return (int)(When - val.When).count();
		}

		bool IsHit(const TimePoint& val)const
		{
			return When <= val;
		}
	};
	using TimerList = PriorityQueue<Timer*, EqualCompare, CustomCompareForPointer>;
public:
	TTimerQueue()
		:mInterval(TDuration(TInterval))
	{

	}

	~TTimerQueue(void)
	{
		//clear all
		CancelAll();
	}

	void ScheduleDelay(TCallBack callback, TDuration delay, TDuration repeatDuration = TDuration::zero(), uint repeatCount = Math::UIntMaxValue)
	{
		TimePoint when = TClock::now() + delay;
		mUnscheduleds.Add(new Timer(std::move(callback), std::move(when), std::move(repeatDuration), repeatCount));
	}

	void Schedule(TCallBack callback, TimePoint when, TDuration repeatDuration = TDuration::zero(), uint repeatCount = Math::UIntMaxValue)
	{
		if (when <= TClock::now() && repeatDuration == TDuration::zero() && repeatCount == Math::UIntMaxValue)
		{
			callback();
			return;
		}
		mUnscheduleds.Add(new Timer(std::move(callback), std::move(when), std::move(repeatDuration), repeatCount));
	}

	bool Tick()
	{
		//schedule any timers added by other threads
		for (auto* t : mUnscheduleds)
		{
			mTimers.Push(t);
		}
		mUnscheduleds.Clear();

		RETURN_FALSE_IF_EMPTY(mTimers);
		auto now = TClock::now();

		Timer* timer = nullptr;
		while (true)
		{
			timer = mTimers.TopOr(nullptr);
			BREAK_IF_NULL(timer);

			if (timer->IsHit(now))
			{
				mTimers.Pop();
				timer->Callback();
				if (!timer->IsRepeat())
				{
					delete timer;
				}
				else
				{
					mTimers.Push(timer);
				}
			}
			else
			{
				break;
			}
		}

		return !mTimers.IsEmpty();
	}

	void CancelAll()
	{
		SAFE_DELETE_COLLECTION(mTimers);
		SAFE_DELETE_COLLECTION(mUnscheduleds);
	}
	void SleepInterval()
	{
		Thread::Sleep((long)std::chrono::duration_cast<std::chrono::milliseconds>(mInterval).count());
	}
	bool IsEmpty()const
	{
		return mTimers.IsEmpty();
	}
protected:
	TimePoint mLastTick;
	TimerList mTimers;
	List<Timer*> mUnscheduleds;
	TDuration mInterval;

};


//[PRE_DECLARE_BEGIN]
typedef TTimerQueue<Action> TimerQueue;
//[PRE_DECLARE_END]


MEDUSA_END;
