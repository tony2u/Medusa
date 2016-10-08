// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteRepeatableAction.h"

MEDUSA_BEGIN;
class BaseFiniteRepeatableCountDownDelayAction :public BaseFiniteRepeatableAction
{
	enum class RepeateModeStep
	{
		Before = 0,
		Repeat = 1,
		After = 2
	};
public:
	BaseFiniteRepeatableCountDownDelayAction(float duration, intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty)
		:BaseFiniteRepeatableAction(duration, repeatCount, name), mBeforeDelay(beforeDelay), mRepeatDuration(repeatDuration), mAfterDelay(afterDelay)
	{
		Init();
	}

	BaseFiniteRepeatableCountDownDelayAction(float duration, bool isRepeatForever=false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty)
		:BaseFiniteRepeatableAction(duration, isRepeatForever, name), mBeforeDelay(beforeDelay), mRepeatDuration(repeatDuration), mAfterDelay(afterDelay)
	{
		Init();
	}

	BaseFiniteRepeatableCountDownDelayAction(float duration, intp currentCount, intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty)
		:BaseFiniteRepeatableAction(duration, currentCount, repeatCount, name), mBeforeDelay(beforeDelay), mRepeatDuration(repeatDuration), mAfterDelay(afterDelay)
	{
		Init();
	}

	virtual ~BaseFiniteRepeatableCountDownDelayAction(void) {}

	void InitializeEx(intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f)
	{
		SetRepeatCount(repeatCount);
		mBeforeDelay = beforeDelay;
		mRepeatDuration = repeatDuration;
		mAfterDelay = afterDelay;
		Init();
	}

	void InitializeEx(bool isRepeatForever, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f)
	{
		EnableRepeatForever(isRepeatForever);
		mBeforeDelay = beforeDelay;
		mRepeatDuration = repeatDuration;
		mAfterDelay = afterDelay;
		Init();
	}
public:
	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteRepeatableAction::Reset());
		Init2();
		return true;
	}

	virtual bool Update(float dt, float blend = 1.f)override;
public:
	float BeforeDelay() const { return mBeforeDelay; }
	void SetBeforeDelay(float val) { mBeforeDelay = val; mHasBeforeDelay = !Math::IsZero(mBeforeDelay); }

	float RepeatDuration() const { return mRepeatDuration; }	//other limit repeat duration, even in repeat forever mode, will stop when reaching this duration
	void SetRepeatDuration(float val) { mRepeatDuration = val; mHasRepeatDuration = !Math::IsZero(mRepeatDuration); }

	float AfterDelay() const { return mAfterDelay; }
	void SetAfterDelay(float val) { mAfterDelay = val; mHasAfterDelay = !Math::IsZero(mAfterDelay); }

	virtual float ElapsedExceed()const override;
protected:

	virtual void BuildClone(IAction& obj) override;
private:
	void Init()
	{
		mHasBeforeDelay = !Math::IsZero(mBeforeDelay);
		mHasRepeatDuration = !Math::IsZero(mRepeatDuration);
		mHasAfterDelay = !Math::IsZero(mAfterDelay);

		Init2();
	}

	void Init2()
	{
		mBeforeDelayElapsed = 0.f;
		mAfterDelayElapsed = 0.f;
		mRepeatElapsed = 0.f;
		mMode = mHasBeforeDelay ? RepeateModeStep::Before : RepeateModeStep::Repeat;
	}
protected:
	float mBeforeDelay;
	float mRepeatDuration;
	float mAfterDelay;

	float mBeforeDelayElapsed;
	float mAfterDelayElapsed;
	float mRepeatElapsed;

	bool mHasRepeatDuration;
	bool mHasAfterDelay;
	bool mHasBeforeDelay;

	RepeateModeStep mMode;
};

MEDUSA_END;
