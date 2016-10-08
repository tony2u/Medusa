// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;
class BaseFiniteRepeatableAction :public BaseFiniteAction
{
public:
	BaseFiniteRepeatableAction(float duration, intp repeatCount, const StringRef& name = StringRef::Empty)
		:BaseFiniteAction(duration, name), mCurrentCount(repeatCount), mRepeatCount(repeatCount)
	{
	}

	BaseFiniteRepeatableAction(float duration, bool isRepeatForever=false, const StringRef& name = StringRef::Empty)
		:BaseFiniteAction(duration, name), mCurrentCount(isRepeatForever ? -1 : 0), mRepeatCount(isRepeatForever ? -1 : 0)
	{
	}

	BaseFiniteRepeatableAction(float duration, intp currentCount, intp repeatCount, const StringRef& name = StringRef::Empty)
		:BaseFiniteAction(duration, name), mCurrentCount(currentCount), mRepeatCount(repeatCount)
	{
	}


	virtual ~BaseFiniteRepeatableAction(void) {}

	intp RepeatCount() const { return mRepeatCount; }
	void SetRepeatCount(intp val) { mRepeatCount = val; mCurrentCount = Math::Min(mCurrentCount, mRepeatCount); }

	bool IsRepeatForever()const
	{
		return mRepeatCount < 0;
	}

	void EnableRepeatForever(bool isRepeatForever)
	{
		if (isRepeatForever)
		{
			mRepeatCount = -1;
			mCurrentCount = -1;
		}
		else
		{
			mRepeatCount = Math::ClampAboveZero(mRepeatCount);
			mCurrentCount = Math::ClampAboveZero(mCurrentCount);
		}
	}
public:
	virtual bool Stop()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Stop());
		mCurrentCount = mRepeatCount;
		return true;
	}

	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Reset());
		mCurrentCount = mRepeatCount;

		return true;
	}

	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(IAction::Update(dt, blend));
		float prevElapsed = this->mElapsed;
		this->mElapsed += dt;
		if (this->mElapsed > this->mDuration)
		{
			float exceed = this->mElapsed - this->mDuration;
			this->mElapsed = this->mDuration;

			if (mCurrentCount == 0)
			{
				this->Stop();
				return OnUpdate(prevElapsed, dt - exceed, blend);
			}

			if (mCurrentCount > 0)
			{
				--mCurrentCount;
			}

			this->OnUpdate(prevElapsed, dt - exceed, blend);
			this->Start();	//this->mElapsed will reset to 0.f in start
			return this->OnUpdate(0.f, exceed, blend);
		}

		return this->OnUpdate(prevElapsed, dt, blend);
	}

protected:
	virtual bool OnUpdate(float prevElapsed, float dt, float blend = 1.f) = 0;
	virtual void BuildClone(IAction& obj) override
	{
		BaseFiniteAction::BuildClone(obj);
		auto& t = (BaseFiniteRepeatableAction&)obj;
		t.mCurrentCount = mCurrentCount;
		t.mRepeatCount = mRepeatCount;
	}
protected:
	intp mCurrentCount=0;
	intp mRepeatCount=0;	//<0:repeat forever  =0:don't repeat	>0:repeat count
};

MEDUSA_END;
