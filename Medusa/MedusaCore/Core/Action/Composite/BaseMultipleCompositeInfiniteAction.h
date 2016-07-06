// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInfiniteAction.h"
#include "Core/Collection/List.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;
class BaseMultipleCompositeInfiniteAction :public BaseInfiniteAction
{
public:
	BaseMultipleCompositeInfiniteAction() {}
	BaseMultipleCompositeInfiniteAction(const List<IAction*>& actions) :mInnerActions(actions) {}
	virtual ~BaseMultipleCompositeInfiniteAction(void) { SAFE_DELETE_COLLECTION(mInnerActions); }
public:
	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Reset());
		if (mInnerActions.IsEmpty())
		{
			this->ForceSetState(RunningState::Done);
			return true;
		}

		for (auto currentAction : mInnerActions)
		{
			currentAction->Reset();
		}

		return true;
	}

	virtual bool Initialize(void* target)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Initialize(target));
		bool isSuccess = true;
		for (auto currentAction : mInnerActions)
		{
			if (!currentAction->Initialize(target))
			{
				isSuccess = false;
				break;
			}
		}

		return isSuccess;
	}
	virtual IAction* FindActionByTagRecursively(int tag)const override
	{
		for (auto action : mInnerActions)
		{
			if (action->Tag() == tag)
			{
				return action;
			}
		}

		for (auto action : mInnerActions)
		{
			IAction* result = action->FindActionByTagRecursively(tag);
			RETURN_SELF_IF_NOT_NULL(result);
		}

		return nullptr;
	}
	virtual IAction* FindActionByNameRecursively(const StringRef& name) const override
	{
		RETURN_NULL_IF_EMPTY(name);
		for (auto action : mInnerActions)
		{
			if (action->Name() == name)
			{
				return action;
			}
		}

		for (auto action : mInnerActions)
		{
			IAction* result = action->FindActionByNameRecursively(name);
			RETURN_SELF_IF_NOT_NULL(result);
		}
		return nullptr;
	}
public:
	const List<IAction*>& InnerActions() const { return mInnerActions; }
	List<IAction*>& MutableInnerActions() { return mInnerActions; }

	void Add(IAction* action)
	{
		Log::AssertFormat(this->mState == RunningState::None, "Cannot add action when running");
		mInnerActions.Add(action);
	}

	void Remove(IAction* action)
	{
		Log::AssertFormat(this->mState == RunningState::None, "Cannot Remove action when running");
		mInnerActions.Remove(action);
	}

	bool Contains(IAction* action)
	{
		return mInnerActions.Contains(action);
	}
protected:
	List<IAction*> mInnerActions;
};
MEDUSA_END;
