// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseMultipleCompositeInfiniteAction.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;

class SelectAction :public BaseMultipleCompositeInfiniteAction
{
public:
	typedef Delegate<uint(void*)> SelectDelegate;	//return action index
	SelectDelegate OnSelect;
public:
	SelectAction(SelectDelegate selector) :OnSelect(selector), mCurrentIndex(0) {}
	SelectAction(SelectDelegate selector, const List<IAction*>& actions) :BaseMultipleCompositeInfiniteAction(actions), OnSelect(selector), mCurrentIndex(0) {}
	SelectAction(SelectDelegate selector, IAction* a1, IAction* a2) :OnSelect(selector), mCurrentIndex(0)
	{
		this->mInnerActions.Add(a1);
		this->mInnerActions.Add(a2);
	}

	virtual ~SelectAction(void) {}
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Update(dt, blend));
		if (this->mInnerActions.IsEmpty())
		{
			this->Stop();
			return true;
		}

		uint newIndex = OnSelect(this->mTarget);
		newIndex = Math::Clamp(mCurrentIndex, 0U, (uint)this->mInnerActions.Count());
		if (newIndex != mCurrentIndex)
		{
			IAction* currentAction = this->mInnerActions[mCurrentIndex];
			currentAction->Stop();
			mCurrentIndex = newIndex;
		}

		IAction* currentAction = this->mInnerActions[mCurrentIndex];
		currentAction->Update(dt, blend);

		return true;
	}

	virtual bool Start()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Start());
		mCurrentIndex = 0;
		if (this->mInnerActions.IsEmpty())
		{
			this->Stop();
			return true;
		}
		IAction* currentAction = this->mInnerActions[mCurrentIndex];
		currentAction->Start();

		return true;
	}


	virtual bool Pause()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Pause());
		if (this->mInnerActions.IsEmpty())
		{
			this->Stop();
			return true;
		}
		IAction* currentAction = this->mInnerActions[mCurrentIndex];
		return currentAction->Pause();
	}
	virtual bool Resume()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Resume());
		if (this->mInnerActions.IsEmpty())
		{
			this->Stop();
			return true;
		}
		IAction* currentAction = this->mInnerActions[mCurrentIndex];
		return currentAction->Resume();
	}
	virtual bool Stop()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Stop());
		if (this->mInnerActions.IsEmpty())
		{
			this->mState=RunningState::Done;
			this->OnStop();
			return true;
		}

		IAction* currentAction = this->mInnerActions[mCurrentIndex];
		return currentAction->Stop();
	}

	virtual bool Reset()override
	{
		mCurrentIndex = 0;
		return BaseMultipleCompositeInfiniteAction::Reset();
	}
public:
	void ReverseSelf()
	{
		Reset();
		this->mInnerActions.Reverse();
	}

	virtual SelectAction* Clone()const override
	{
		return new SelectAction(OnSelect, this->mInnerActions);
	}
	virtual SelectAction* Reverse()const override
	{
		SelectAction* seq = new SelectAction(OnSelect, this->mInnerActions);
		seq->ReverseSelf();
		return seq;
	}

	static SelectAction* CreateEmpty(SelectDelegate switcher)
	{
		return new SelectAction(switcher);
	}

	static SelectAction* CreateWithNullEnd(SelectDelegate switcher, IAction* a1, ...) MEDUSA_REQUIRES_NULL_TERMINATION
	{
		va_list params;
		va_start(params, a1);
		SelectAction* seq = new SelectAction(switcher);
		seq->Add(a1);

		IAction* now = nullptr;
		while (true)
		{
			now = va_arg(params, IAction*);
			BREAK_IF_NULL(now);
			seq->Add(now);
		}
		va_end(params);

		return seq;
	}

		static SelectAction* Create(SelectDelegate switcher, const List<IAction*>& actions)
	{
		return new SelectAction(switcher, actions);
	}

	static SelectAction* Create(SelectDelegate switcher, IAction* a1)
	{
		SelectAction* seq = new SelectAction(switcher);
		seq->Add(a1);
		return seq;
	}

	static SelectAction* Create(SelectDelegate switcher, IAction* a1, IAction* a2)
	{
		SelectAction* seq = new SelectAction(switcher, a1, a2);

		return seq;
	}

	static SelectAction* Create(SelectDelegate switcher, IAction* a1, IAction* a2, IAction* a3)
	{
		SelectAction* seq = new SelectAction(switcher);
		seq->Add(a1);
		seq->Add(a2);
		seq->Add(a3);

		return seq;
	}

	static SelectAction* Create(SelectDelegate switcher, IAction* a1, IAction* a2, IAction* a3, IAction* a4)
	{
		SelectAction* seq = new SelectAction(switcher);
		seq->Add(a1);
		seq->Add(a2);
		seq->Add(a3);
		seq->Add(a4);

		return seq;
	}

protected:
	uint mCurrentIndex;
};
MEDUSA_END;
