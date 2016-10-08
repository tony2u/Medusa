// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseMultipleCompositeInfiniteAction.h"

MEDUSA_BEGIN;
class SequenceAction :public BaseMultipleCompositeInfiniteAction
{
public:
	SequenceAction() :mCurrentIndex(0) {}
	SequenceAction(const List<IAction*>& actions) :BaseMultipleCompositeInfiniteAction(actions), mCurrentIndex(0) {}
	SequenceAction(IAction* a1, IAction* a2) :mCurrentIndex(0)
	{
		this->mInnerActions.Add(a1);
		this->mInnerActions.Add(a2);
	}

	SequenceAction(IAction* a1, IAction* a2, IAction* a3) :mCurrentIndex(0)
	{
		this->mInnerActions.Add(a1);
		this->mInnerActions.Add(a2);
		this->mInnerActions.Add(a3);
	}

	SequenceAction(IAction* a1, IAction* a2, IAction* a3,IAction* a4) :mCurrentIndex(0)
	{
		this->mInnerActions.Add(a1);
		this->mInnerActions.Add(a2);
		this->mInnerActions.Add(a3);
		this->mInnerActions.Add(a4);
	}

	virtual ~SequenceAction(void) {}
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Update(dt, blend));
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

		++mCurrentIndex;

		dt = currentAction->ElapsedExceed();
		while (mCurrentIndex < this->mInnerActions.Count())
		{
			currentAction = this->mInnerActions[mCurrentIndex];
			currentAction->Start();
			if (currentAction->IsDone())
			{
				dt = currentAction->ElapsedExceed();
				++mCurrentIndex;
			}
			else
			{
				currentAction->Update(dt, blend);
				if (currentAction->IsDone())
				{
					dt = currentAction->ElapsedExceed();
					++mCurrentIndex;
				}
				else
				{
					return true;
				}
			}
		}

		this->Stop();
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

		while (mCurrentIndex < this->mInnerActions.Count())
		{
			IAction* currentAction = this->mInnerActions[mCurrentIndex];
			currentAction->Start();
			if (currentAction->IsDone())
			{
				++mCurrentIndex;
			}
			else
			{
				return true;
			}
		}

		this->Stop();
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
			this->mState = RunningState::Done;
			this->OnStop();
			return true;
		}

		if (mCurrentIndex<this->mInnerActions.Count())
		{
			IAction* currentAction = this->mInnerActions[mCurrentIndex];
			return currentAction->Stop();
		}
		return true;
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

	virtual SequenceAction* Clone()const override
	{
		return new SequenceAction(this->mInnerActions);
	}
	virtual SequenceAction* Reverse()const override
	{
		SequenceAction* seq = new SequenceAction(this->mInnerActions);
		seq->ReverseSelf();
		return seq;
	}

	static SequenceAction* CreateEmpty()
	{
		return new SequenceAction();
	}

	static SequenceAction* CreateWithNullEnd(IAction* a1, ...) MEDUSA_REQUIRES_NULL_TERMINATION
	{
		va_list params;
		va_start(params, a1);
		SequenceAction* seq = new SequenceAction();
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

		static SequenceAction* Create(const List<IAction*>& actions)
	{
		return new SequenceAction(actions);
	}

	static SequenceAction* Create(IAction* a1)
	{
		SequenceAction* seq = new SequenceAction();
		seq->Add(a1);
		return seq;
	}

	static SequenceAction* Create(IAction* a1, IAction* a2)
	{
		SequenceAction* seq = new SequenceAction();
		seq->Add(a1);
		seq->Add(a2);

		return seq;
	}

	static SequenceAction* Create(IAction* a1, IAction* a2, IAction* a3)
	{
		SequenceAction* seq = new SequenceAction();
		seq->Add(a1);
		seq->Add(a2);
		seq->Add(a3);

		return seq;
	}

	static SequenceAction* Create(IAction* a1, IAction* a2, IAction* a3, IAction* a4)
	{
		SequenceAction* seq = new SequenceAction();
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
