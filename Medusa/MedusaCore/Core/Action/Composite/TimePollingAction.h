// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseMultipleCompositeFiniteAction.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;

class TimePollingAction :public BaseMultipleCompositeFiniteAction
{
public:
	typedef Delegate<uint(void*)> SelectDelegate;	//return action index
public:
	TimePollingAction(float duration, uint currentIndex = 0, const StringRef& name = StringRef::Empty)
		:BaseMultipleCompositeFiniteAction(duration, name), mCurrentIndex(currentIndex)
	{
	}
	TimePollingAction(float duration, const List<IAction*>& actions, uint currentIndex = 0, const StringRef& name = StringRef::Empty)
		:BaseMultipleCompositeFiniteAction(duration, actions, name), mCurrentIndex(currentIndex)
	{
	}
	TimePollingAction(float duration, IAction* a1, IAction* a2, uint currentIndex = 0, const StringRef& name = StringRef::Empty)
		:BaseMultipleCompositeFiniteAction(duration, name), mCurrentIndex(currentIndex)
	{
		this->mInnerActions.Add(a1);
		this->mInnerActions.Add(a2);
	}

	virtual ~TimePollingAction(void) {}


public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		if (this->mInnerActions.IsEmpty())
		{
			this->Stop();
			return true;
		}

		IAction* currentAction = this->mInnerActions[mCurrentIndex];
		currentAction->Update(dt, blend);

		if (!currentAction->IsDone())
		{
			return true;
		}
		dt = currentAction->ElapsedExceed();

		while (dt > 0.f)
		{
			//polling all actions
			mCurrentIndex = (mCurrentIndex + 1) % this->mInnerActions.Count();
			currentAction = this->mInnerActions[mCurrentIndex];
			currentAction->Start();

			if (currentAction->IsDone())
			{
				continue;
			}
			else
			{
				currentAction->Update(dt, blend);
				if (currentAction->IsDone())
				{
					dt = currentAction->ElapsedExceed();
					continue;
				}
				else
				{
					return true;
				}
			}
		}

		return true;
	}

	virtual bool Start()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Start());
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
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Pause());
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
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Resume());
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
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Stop());
		if (this->mInnerActions.IsEmpty())
		{
			this->mState = RunningState::Done;
			this->OnStop();
			return true;
		}

		IAction* currentAction = this->mInnerActions[mCurrentIndex];
		return currentAction->Stop();
	}

	virtual bool Reset()override
	{
		mCurrentIndex = 0;
		return BaseMultipleCompositeFiniteAction::Reset();
	}
public:
	uint CurrentIndex() const { return mCurrentIndex; }

	void SwitchToIndex(uint index)
	{
		RETURN_IF_EQUAL(mCurrentIndex, index);
		//stop original action
		IAction* currentAction = this->mInnerActions[mCurrentIndex];
		currentAction->Stop();

		mCurrentIndex = index;
		currentAction = this->mInnerActions[mCurrentIndex];
		currentAction->Start();
	}

	void ReverseSelf()
	{
		Reset();
		this->mInnerActions.Reverse();
	}

	virtual TimePollingAction* Clone()const override
	{
		return new TimePollingAction(this->mDuration, this->mInnerActions);
	}
	virtual TimePollingAction* Reverse()const override
	{
		TimePollingAction* seq = new TimePollingAction(this->mDuration, this->mInnerActions);
		seq->ReverseSelf();
		return seq;
	}

	static TimePollingAction* CreateEmpty(float duraion)
	{
		return new TimePollingAction(duraion);
	}

	static TimePollingAction* CreateWithNullEnd(float duraion, IAction* a1, ...) MEDUSA_REQUIRES_NULL_TERMINATION
	{
		va_list params;
		va_start(params, a1);
		TimePollingAction* seq = new TimePollingAction(duraion);
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

		static TimePollingAction* Create(float duraion, const List<IAction*>& actions)
	{
		return new TimePollingAction(duraion, actions);
	}

	static TimePollingAction* Create(float duraion, IAction* a1)
	{
		TimePollingAction* seq = new TimePollingAction(duraion);
		seq->Add(a1);
		return seq;
	}

	static TimePollingAction* Create(float duraion, IAction* a1, IAction* a2)
	{
		TimePollingAction* seq = new TimePollingAction(duraion, a1, a2);

		return seq;
	}

	static TimePollingAction* Create(float duraion, IAction* a1, IAction* a2, IAction* a3)
	{
		TimePollingAction* seq = new TimePollingAction(duraion);
		seq->Add(a1);
		seq->Add(a2);
		seq->Add(a3);

		return seq;
	}

	static TimePollingAction* Create(float duraion, IAction* a1, IAction* a2, IAction* a3, IAction* a4)
	{
		TimePollingAction* seq = new TimePollingAction(duraion);
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
