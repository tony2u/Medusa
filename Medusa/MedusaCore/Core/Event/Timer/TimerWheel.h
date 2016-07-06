// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Math/Math.h"
#include "Core/Memory/Memory.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

//http://www.cs.columbia.edu/~nahum/w6998/papers/sosp87-timing-wheels.pdf

//TODO: still have bugs
template<typename TCallBack, size_t TBucketCount = 4, size_t TWheelCount = 256, size_t TInterval = 10, typename TDuration = std::chrono::milliseconds, typename TClock = std::chrono::high_resolution_clock>
class TTimerWheel	
{
public:
	using TimePoint = std::chrono::time_point<TClock>;
	using Duration = TDuration;
public:
	struct Timer
	{
		Timer(TCallBack&& callback, TimePoint&& when, TDuration&& repeatDuration, size_t repeatCount)
			:Callback(callback), When(when), RepeatDuration(repeatDuration), RepeatCount(repeatCount)
		{

		}

		Timer* Next=nullptr;
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
	};

public:
	constexpr static uint BucketCount = TBucketCount;
	constexpr static uint WheelCount = TWheelCount;
	constexpr static uint WheelMask = WheelCount - 1;
	constexpr static uint TotalWheelCount = TBucketCount*WheelCount;

public:
	TTimerWheel()
		:mLastTick(TClock::now()),
		mUnscheduled(nullptr), mInterval(TDuration(TInterval))
	{
		uint64 maxTickCount = 1;
		for (size_t i = 0; i < TBucketCount; ++i)
		{
			maxTickCount *= TWheelCount;
		}
		mMaxTickCount = (size_t)(maxTickCount - 1);	//from 0 to count

		memset(mWheel, 0, TBucketCount*TWheelCount * sizeof(Timer*));
		memset(mWheelIndex, 0, TBucketCount* sizeof(size_t));

	}

	~TTimerWheel(void)
	{
		//clear all
		CancelAll();
	}

	void ScheduleDelay(TCallBack callback, TDuration delay, TDuration repeatDuration = TDuration::zero(), size_t repeatCount = Math::UIntMaxValue)
	{
		TimePoint when = TClock::now() + delay;
		Queue(new Timer(std::move(callback), std::move(when), std::move(repeatDuration), repeatCount), mUnscheduled);
	}

	void Schedule(TCallBack callback, TimePoint when, TDuration repeatDuration = TDuration::zero(), size_t repeatCount = Math::UIntMaxValue)
	{
		Queue(new Timer(std::move(callback), std::move(when), std::move(repeatDuration), repeatCount), mUnscheduled);
	}

	bool Tick()
	{
		auto now = TClock::now();
		auto delta = now - mLastTick;
		auto count = delta / mInterval;
		size_t ticksToGo = std::min<size_t>((size_t)count, mMaxTickCount);

		mLastTick = now;

		size_t curWheelIndex = mWheelIndex;
		size_t curBucketIndex = mBucketIndex;

		for (size_t i = 0; i < ticksToGo; ++i)
		{
			curWheelIndex = mWheelIndex + i;

			if (curWheelIndex >= TWheelCount)
			{
				curWheelIndex = 0;
				curBucketIndex = (++curBucketIndex) % TBucketCount;
			}
			else
			{
				curWheelIndex = curWheelIndex%TWheelCount;
			}

			//invoke timer list
			Timer* next = nullptr;
			for (Timer* t = mWheel[curBucketIndex][curWheelIndex]; t != nullptr; t = next)
			{
				t->Callback();
				next = t->Next;
				if (!t->IsRepeat())
				{
					--mCount;
					delete t;
				}
				else
				{
					Schedule(t, now+t->RepeatDuration);
				}
			}
			mWheel[curBucketIndex][curWheelIndex] = nullptr;
		}

		mWheelIndex = curWheelIndex;
		mBucketIndex = curBucketIndex;
		//schedule any timers added by other threads
		Timer* next = nullptr;
		for (Timer* t = mUnscheduled; t != nullptr; t = next)
		{
			next = t->Next;
			--mCount;
			Schedule(t, t->When);
		}

		mUnscheduled = nullptr;

		return mCount>0;
	}

	void CancelAll()
	{
		FOR_EACH_SIZE(i, TBucketCount)
		{
			FOR_EACH_SIZE(j, TWheelCount)
			{
				//invoke timer list
				Timer* next = nullptr;
				for (Timer* t = mWheel[mBucketIndex][mWheelIndex]; t != nullptr; t = next)
				{
					delete t;
				}

				mWheel[mBucketIndex][mWheelIndex] = nullptr;
			}
		}
		
	}
protected:
	void Queue(Timer* timer, Timer*& on)
	{
		timer->Next = on;
		on = timer;
		++mCount;
	}


	void Schedule(Timer* timer, TimePoint when)
	{
		auto delta = when - mLastTick;
		auto count= delta / mInterval;
		size_t ticks = std::min<size_t>((size_t)count, mMaxTickCount);


		size_t temp = mWheelIndex + ticks;
		size_t wheelIndex = temp%TWheelCount;
		size_t bucketIndex = mBucketIndex;

		while (temp >= TWheelCount)
		{
			temp /= TWheelCount;
			bucketIndex = (++bucketIndex) % TBucketCount;
		}
		Queue(timer, mWheel[bucketIndex][wheelIndex]);
	}

	Timer* GetTimer(size_t tickIndex)const
	{
		size_t wheelIndex = tickIndex%TWheelCount;
		size_t bucketIndex=0;
		while (tickIndex >= TWheelCount)
		{
			tickIndex /= TWheelCount;
			bucketIndex = (++bucketIndex) % TBucketCount;
		}

		return mWheel[bucketIndex][wheelIndex];
	}
protected:
	TimePoint mLastTick;
	size_t mIndex;
	size_t mBucketIndex = 0;
	size_t mMaxTickCount;

	Timer* mWheel[TBucketCount][TWheelCount];	//from 0 to high
	size_t mWheelIndex[TBucketCount];

	Timer* mUnscheduled=nullptr;

	TDuration mInterval;
	uint mCount = 0;

};


//[PRE_DECLARE_BEGIN]
typedef TTimerWheel<Action> TimerWheel;
//[PRE_DECLARE_END]


MEDUSA_END;
