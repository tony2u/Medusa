// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/IAction.h"
#include "Core/Math/Math.h"
#include "Core/Math/Random/Random.h"

MEDUSA_BEGIN;
class BaseFiniteAction :public IAction
{
public:

	BaseFiniteAction(float duration, const StringRef& name = StringRef::Empty) :IAction(name), mDuration(duration), mElapsed(0.f)
	{

	}
	virtual ~BaseFiniteAction(void) {}
	virtual ActionType Type()const override{ return ActionType::Finite; }

public:
	virtual bool Start()override
	{
		RETURN_FALSE_IF_FALSE(DefaultRunnable::Start());
		mElapsed = 0.f;

		return true;
	}
	virtual bool Stop()override
	{
		RETURN_FALSE_IF_FALSE(DefaultRunnable::Stop());
		mElapsed = mDuration;
		return true;
	}
	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(DefaultRunnable::Reset());
		mElapsed = 0.f;
		return true;
	}

	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(IAction::Update(dt, blend));

		mElapsed += dt;
		if (mElapsed > mDuration)
		{
			this->ForceSetState(RunningState::Done);
		}
		return true;
	}

	bool PauseToTime(float timestamp, float blend = 1.f)
	{
		bool isSucceed = JumpToTime(timestamp, blend);
		bool isPaused = Pause();
		return isSucceed&&isPaused;
	}

	bool JumpToTime(float timestamp, float blend = 1.f)
	{
		timestamp = Math::Clamp(timestamp, 0.f, mDuration);
		float delta = timestamp - mElapsed;
		return Update(delta, blend);
	}

	bool JumpForwardRandomly(float blend = 1.f)
	{
		float timestamp = Random::Global().NextFloat(mElapsed, mDuration);
		float delta = timestamp - mElapsed;
		return Update(delta, blend);
	}

	float Percent()const { return Math::Min(mElapsed / mDuration, 1.f); }

	float Duration() const { return mDuration; }
	void SetDuration(const float val) { mDuration = val; }

	float Elapsed() const { return mElapsed; }
	float LeftDuration() const { return mDuration - mElapsed; }

	virtual float ElapsedExceed()const override{ return Math::ClampAboveZero(mElapsed - mDuration); }
protected:
	float mDuration;
	float mElapsed;
};

MEDUSA_END;
