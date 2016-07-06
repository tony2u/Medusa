// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Action/IActionRunnable.h"
#include "Core/Action/IAction.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Linq.h"

MEDUSA_BEGIN;
template<typename TTarget>
class BaseActionRunner :public IActionRunnable
{
public:
	typedef List<ActionItemType*> ActionListType;
	virtual ~BaseActionRunner()
	{
		SAFE_DELETE_COLLECTION(mActions);
	}

	virtual bool UpdateActions(float dt)
	{
		RETURN_TRUE_IF_EMPTY(mActions);
		size_t count = mActions.Count();
		//use constant count so that even if we invoke RunAction inner UpdateActions callbacks, we don't update new in actions
		FOR_EACH_SIZE(i, count)
		{
			ActionItemType* action = mActions[i];
			MEDUSA_ASSERT_NOT_NULL(action, "");
			if (action->ForceGetState() == RunningState::None)
			{
				if (!action->Start() || action->IsDone())
				{
					mCompletedActionIndices.Add(i);
					continue;
				}

			}
			bool isContinue = action->Update(dt);
			if (action->IsDone())
			{
				mCompletedActionIndices.Add(i);
			}
			BREAK_IF_FALSE(isContinue);
		}

		Linq::DeleteIndexes(mActions, mCompletedActionIndices);
		mCompletedActionIndices.Clear();

		return true;
	}

	virtual bool TryStartAsyncActions()
	{
		RETURN_TRUE_IF_EMPTY(mActions);

		//allow to start next actions
		FOR_EACH_SIZE(i, mActions.Count())
		{
			ActionItemType* action = mActions[i];
			CONTINUE_IF(action->IsRunning());
			if (!action->Start() || action->IsDone())
			{
				mCompletedActionIndices.Add(i);
				continue;
			}
		}

		Linq::DeleteIndexes(mActions, mCompletedActionIndices);
		mCompletedActionIndices.Clear();

		return true;
	}
public:
	virtual ActionItemType* RunAction(ActionItemType* action)override
	{
		//it's safe to invoke RunAction inner UpdateActions callback
		//have to use TTarget to convert ptr, or target ptr will be interrupted 
		if (action->Initialize((TTarget*)this) && action->Start())
		{
			if (!action->IsDone())	//instant action
			{
				mActions.Append(action);
				return action;
			}
		}

		ActionItemType* p = action;
		SAFE_DELETE(p);
		return nullptr;
	}

	virtual ActionItemType* RunActionAsync(ActionItemType* action)override
	{
		//it's safe to invoke RunAction inner UpdateActions callback
		//have to use TTarget to convert ptr, or target ptr will be interrupted 
		if (action->Initialize((TTarget*)this))
		{
			mActions.Append(action);
			return action;
		}

		ActionItemType* p = action;
		SAFE_DELETE(p);
		return nullptr;
	}

	virtual ActionItemType* FindActionByTag(int tag)const override
	{
		for(auto action: mActions)
		{
			if (action->Tag() == tag)
			{
				return action;
			}
		}
		return nullptr;
	}
	virtual ActionItemType* FindActionByName(const StringRef& name)const override
	{
		RETURN_NULL_IF_EMPTY(name);
		for (auto action : mActions)
		{
			if (action->Name() == name)
			{
				return action;
			}
		}
		return nullptr;
	}

	virtual ActionItemType* FindActionByTagRecursively(int tag)const override
	{
		ActionItemType* result = FindActionByTag(tag);
		RETURN_SELF_IF_NOT_NULL(result);

		for (auto action : mActions)
		{
			result = action->FindActionByTagRecursively(tag);
			RETURN_SELF_IF_NOT_NULL(result);
		}

		return nullptr;
	}
	virtual ActionItemType* FindActionByNameRecursively(const StringRef& name)const override
	{
		ActionItemType* result = FindActionByName(name);
		RETURN_SELF_IF_NOT_NULL(result);
		for (auto action : mActions)
		{
			ActionItemType* tempResult = action->FindActionByNameRecursively(name);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}
		return nullptr;
	}


	virtual void PauseAllActions()override
	{
		FOR_EACH_TO(mActions, Pause());
	}
	virtual void ResumeAllActions()override
	{
		FOR_EACH_TO(mActions, Resume());
	}
	virtual void StopAllActions()override
	{
		RETURN_IF_EMPTY(mActions);
		for (auto action : mActions)
		{
			action->Stop();
			delete action;
		}
		mActions.Clear();
	}

	virtual void ResetAllActions()override
	{
		FOR_EACH_TO(mActions, Reset());
	}
	virtual void StartAllActions()override
	{
		FOR_EACH_TO(mActions, Start());
	}

	virtual void RestartAllActions()override
	{
		FOR_EACH_TO(mActions, Restart());
	}


	virtual bool PauseActionsByTag(int tag) override
	{
		bool isFound = false;
		for (auto action : mActions)
		{
			if (action->Tag() == tag)
			{
				action->Pause();
				isFound = true;
			}
		}
		return isFound;
	}
	virtual bool ResumeActionsByTag(int tag) override
	{
		bool isFound = false;
		for (auto action : mActions)
		{
			if (action->Tag() == tag)
			{
				action->Stop();
				isFound = true;
			}
		}
		return isFound;
	}
	virtual bool ResetActionsByTag(int tag) override
	{
		bool isFound = false;
		for (auto action : mActions)
		{
			if (action->Tag() == tag)
			{
				action->Reset();
				isFound = true;
			}
		}
		return isFound;
	}

	virtual bool StartActionsByTag(int tag) override
	{
		bool isFound = false;
		for (auto action : mActions)
		{
			if (action->Tag() == tag)
			{
				action->Start();
				isFound = true;
			}
		}
		return isFound;
	}

	virtual bool RestartActionsByTag(int tag) override
	{
		bool isFound = false;
		for (auto action : mActions)
		{
			if (action->Tag() == tag)
			{
				action->Restart();
				isFound = true;
			}
		}
		return isFound;
	}

	virtual bool StopActionsByTag(int tag) override
	{
		size_t count = mActions.Count();
		RETURN_FALSE_IF_ZERO(count);
		FOR_EACH_SIZE(i, count)
		{
			ActionItemType* action = mActions[i];
			if (action->Tag() == tag)
			{
				action->Stop();
				mCompletedActionIndices.Add(i);
			}
		}

		if (!mCompletedActionIndices.IsEmpty())
		{
			Linq::DeleteIndexes(mActions, mCompletedActionIndices);
			mCompletedActionIndices.Clear();

			return true;
		}

		return false;
	}

	virtual bool RemoveAction(ActionItemType* action) override
	{
		bool result = mActions.Remove(action);
		return result;
	}

	virtual bool PauseAction(ActionItemType* action) override
	{
		RETURN_FALSE_IF_NULL(action);
		action->Resume();
		return true;
	}
	virtual bool ResumeAction(ActionItemType* action)override
	{
		RETURN_FALSE_IF_NULL(action);
		action->Resume();
		return true;
	}
	virtual bool ResetAction(ActionItemType* action)override
	{
		RETURN_FALSE_IF_NULL(action);
		action->Reset();
		return true;
	}

	virtual bool StartAction(ActionItemType* action)override
	{
		RETURN_FALSE_IF_NULL(action);
		action->Start();
		return true;
	}
	virtual bool RestartAction(ActionItemType* action)override
	{
		RETURN_FALSE_IF_NULL(action);
		action->Restart();
		return true;
	}

	virtual bool StopAction(ActionItemType* action) override
	{
		RETURN_FALSE_IF_NULL(action);
		action->Stop();
		mActions.Remove(action);
		SAFE_DELETE(action);

		return true;
	}

	virtual bool IsActionRunning()const override
	{
		return !mActions.IsEmpty();
	}

	const ActionListType& Actions() const { return mActions; }
protected:
	ActionListType mActions;
private:
	List<size_t> mCompletedActionIndices;

};

MEDUSA_END;