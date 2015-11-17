// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BasefiniteAction.h"

MEDUSA_BEGIN;
class ReverseAction :public BaseFiniteAction
{
public:
	ReverseAction(BaseFiniteAction* innerAction) :BaseFiniteAction(innerAction->Duration()), mInnerAction(innerAction) {}
	virtual ~ReverseAction(void) { SAFE_DELETE(mInnerAction); }
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(IAction::Update(dt));
		float curPercent = this->Percent();
		this->mElapsed += dt;
		float nowPercent = this->Percent();
		nowPercent = TransformUpdatePercent(nowPercent);
		float newDT = (nowPercent - curPercent)*this->mDuration;

		if (this->mElapsed > this->mDuration)
		{
			this->ForceSetState(RunningState::Done);
		}

		return mInnerAction->Update(newDT);
	}

	virtual RunningState State() const override { return mInnerAction->State(); }
	virtual bool IsRunning()const override { return mInnerAction->IsRunning(); }
	virtual bool IsDone()const override { return mInnerAction->IsDone(); }

	virtual bool Start()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Start());
		return mInnerAction->Start();
	}
	virtual bool Pause()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Pause());
		return mInnerAction->Pause();
	}
	virtual bool Resume()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Resume());
		return mInnerAction->Resume();
	}
	virtual bool Stop()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Stop());
		return mInnerAction->Stop();
	}
	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Reset());
		return mInnerAction->Reset();
	}

	virtual bool Initialize(void* target)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Initialize(target));
		return mInnerAction->Initialize(target);
	}

	virtual ReverseAction* Reverse()const override { return new ReverseAction((BaseFiniteAction*)this); }
protected:
	virtual float TransformUpdatePercent(float percent)const { return percent; }
protected:
	BaseFiniteAction* mInnerAction;
};
MEDUSA_END;
