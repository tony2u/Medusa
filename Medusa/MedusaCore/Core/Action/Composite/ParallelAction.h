// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseMultipleCompositeInfiniteAction.h"

MEDUSA_BEGIN;
class ParallelAction :public BaseMultipleCompositeInfiniteAction
{
public:
	ParallelAction(const List<IAction*>& actions) :BaseMultipleCompositeInfiniteAction(actions) {}
	ParallelAction() {}

	ParallelAction(IAction* a1, IAction* a2)
	{
		this->mInnerActions.Add(a1);
		this->mInnerActions.Add(a2);
	}
	ParallelAction(IAction* a1, IAction* a2, IAction* a3) 
	{
		this->mInnerActions.Add(a1);
		this->mInnerActions.Add(a2);
		this->mInnerActions.Add(a3);
	}

	ParallelAction(IAction* a1, IAction* a2, IAction* a3, IAction* a4) 
	{
		this->mInnerActions.Add(a1);
		this->mInnerActions.Add(a2);
		this->mInnerActions.Add(a3);
		this->mInnerActions.Add(a4);
	}
	virtual ~ParallelAction(void) {}

public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Update(dt, blend));
		if (mInnerActions.IsEmpty())
		{
			this->Stop();
			return true;
		}

		bool isAllDone = true;
		for(auto currentAction: mInnerActions)
		{
			currentAction->Update(dt, blend);
			if (!currentAction->IsDone())
			{
				isAllDone = false;
			}
		}

		if (isAllDone)
		{
			this->Stop();
		}

		return true;
	}

	virtual bool Start()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Start());
		bool isAllDone = true;
		for (auto currentAction : mInnerActions)
		{
			currentAction->Start();
			if (!currentAction->IsDone())
			{
				isAllDone = false;
			}
		}

		if (isAllDone)
		{
			this->Stop();
		}

		return true;
	}

	virtual bool Pause()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Pause());

		for (auto currentAction : mInnerActions)
		{
			currentAction->Pause();
		}
		return true;
	}
	virtual bool Resume()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Resume());
		for (auto currentAction : mInnerActions)
		{
			currentAction->Resume();
		}
		return true;
	}
	virtual bool Stop()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Stop());
		for (auto currentAction : mInnerActions)
		{
			currentAction->Stop();
		}
		return true;
	}
public:

	virtual ParallelAction* Clone()const override
	{
		return new ParallelAction(mInnerActions);
	}
	virtual ParallelAction* Reverse()const override
	{
		return new ParallelAction(mInnerActions);
	}

	static ParallelAction* CreateEmpty()
	{
		return new ParallelAction();
	}

	static ParallelAction* CreateWithNullEnd(IAction* a1, ...) MEDUSA_REQUIRES_NULL_TERMINATION
	{
		va_list params;
		va_start(params, a1);
		ParallelAction* seq = new ParallelAction();
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

		static ParallelAction* Create(const List<IAction*>& actions)
	{
		return new ParallelAction(actions);
	}

	static ParallelAction* Create(IAction* a1)
	{
		ParallelAction* seq = new ParallelAction();
		seq->Add(a1);
		return seq;
	}

	static ParallelAction* Create(IAction* a1, IAction* a2)
	{
		ParallelAction* seq = new ParallelAction();
		seq->Add(a1);
		seq->Add(a2);

		return seq;
	}

	static ParallelAction* Create(IAction* a1, IAction* a2, IAction* a3)
	{
		ParallelAction* seq = new ParallelAction();
		seq->Add(a1);
		seq->Add(a2);
		seq->Add(a3);

		return seq;
	}

	static ParallelAction* Create(IAction* a1, IAction* a2, IAction* a3, IAction* a4)
	{
		ParallelAction* seq = new ParallelAction();
		seq->Add(a1);
		seq->Add(a2);
		seq->Add(a3);
		seq->Add(a4);

		return seq;
	}

};
MEDUSA_END;
