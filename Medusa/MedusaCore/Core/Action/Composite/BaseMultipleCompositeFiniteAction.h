// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
#include "Core/Collection/List.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

class BaseMultipleCompositeFiniteAction :public BaseFiniteAction
{
public:
	BaseMultipleCompositeFiniteAction(float duration, const StringRef& name = StringRef::Empty) :BaseFiniteAction(duration, name) {}
	BaseMultipleCompositeFiniteAction(float duration, const List<IAction*>& actions, const StringRef& name = StringRef::Empty)
		:BaseFiniteAction(duration, name), mInnerActions(actions)
	{
	}
	virtual ~BaseMultipleCompositeFiniteAction(void) { SAFE_DELETE_COLLECTION(mInnerActions); }
public:
	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Reset());
		if (mInnerActions.IsEmpty())
		{
			this->Stop();
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
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Initialize(target));
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
		mInnerActions.Add(action);
		if (mTarget!=nullptr)
		{
			action->Initialize(mTarget);
		}
	}

	void Remove(IAction* action)
	{
		mInnerActions.Remove(action);
	}

	bool Contains(IAction* action)
	{
		return mInnerActions.Contains(action);
	}

	IAction* FindActionByTag(int tag)const
	{
		for (auto action : mInnerActions)
		{
			if (action->Tag() == tag)
			{
				return action;
			}
		}
		return nullptr;
	}
	IAction* FindActionByName(const StringRef& name) const
	{
		RETURN_NULL_IF_EMPTY(name);
		for (auto action : mInnerActions)
		{
			if (action->Name() == name)
			{
				return action;
			}
		}
		return nullptr;
	}
protected:
	List<IAction*> mInnerActions;
};
MEDUSA_END;
