// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInfiniteAction.h"

MEDUSA_BEGIN;
class BaseSingleCompositeInfiniteAction :public BaseInfiniteAction
{
public:
	BaseSingleCompositeInfiniteAction(IAction* innerAction=nullptr) :mInnerAction(innerAction) {}
	virtual ~BaseSingleCompositeInfiniteAction(void) { SAFE_DELETE(mInnerAction); }
public:
	IAction* InnerAction() const { return mInnerAction; }
	void SetInnerAction(IAction* val) { SAFE_ASSIGN(mInnerAction,val); }

	virtual bool IsRunning()const override { return BaseInfiniteAction::IsRunning() && mInnerAction != nullptr&&mInnerAction->IsRunning(); }
	virtual bool IsDone()const override
	{
		return BaseInfiniteAction::IsDone() || (mInnerAction == nullptr || mInnerAction->IsDone());
	}

	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Update(dt, blend));
		float newDT = TransformUpdateDuration(dt);
		bool val = mInnerAction->Update(newDT, blend);
		if (mInnerAction->IsDone())
		{
			Stop();
		}
		return val;
	}

	virtual bool Start()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Start());
		return mInnerAction->Start();
	}
	virtual bool Pause()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Pause());
		return mInnerAction->Pause();
	}
	virtual bool Resume()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Resume());
		return mInnerAction->Resume();
	}
	virtual bool Stop()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Stop());
		return mInnerAction->Stop();
	}
	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Reset());
		return mInnerAction->Reset();
	}

	virtual bool Initialize(void* target)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Initialize(target));
		return mInnerAction->Initialize(target);
	}
	virtual IAction* FindActionByTagRecursively(int tag)const override
	{
		if (mInnerAction->Tag() == tag)
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
	IAction* mInnerAction;
	
};
MEDUSA_END;
