// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;
class BaseSingleCompositeFiniteAction :public BaseFiniteAction
{
public:
	BaseSingleCompositeFiniteAction(IAction* innerAction, float duration)	//duration could be different from innerAction->Duration()
		:BaseFiniteAction(duration), mInnerAction(innerAction)
	{
	}
	virtual ~BaseSingleCompositeFiniteAction(void) { SAFE_DELETE(mInnerAction); }
public:
	virtual bool IsRunning()const override { return BaseFiniteAction::IsRunning() && mInnerAction != nullptr&&mInnerAction->IsRunning(); }
	virtual bool IsDone()const override
	{
		return BaseFiniteAction::IsDone() || (mInnerAction == nullptr || mInnerAction->IsDone());
	}

	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		if (!BaseFiniteAction::IsDone())
		{
			float newDT = TransformUpdateDuration(dt);
			return mInnerAction->Update(newDT, blend);
		}
		else
		{
			mInnerAction->Stop();
		}
		return true;
	}

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

	virtual IAction* FindActionByTagRecursively(int tag)const override
	{
		if (mInnerAction->Tag()==tag)
		{
			return mInnerAction;
		}
		return mInnerAction->FindActionByTagRecursively(tag);
	}
	virtual IAction* FindActionByNameRecursively(const StringRef& name) const override
	{
		if (mInnerAction->Name() == name)
		{
			return mInnerAction;
		}
		return mInnerAction->FindActionByNameRecursively(name);
	}
protected:
	virtual float TransformUpdateDuration(float dt)const { return dt; }
protected:
	IAction* mInnerAction=nullptr;
};
MEDUSA_END;
