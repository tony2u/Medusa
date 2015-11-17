// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

struct IActionRunnable
{
	typedef IAction ActionItemType;
	bool IsActionRunningByTag(int tag)const { return FindActionByTag(tag) != nullptr; }
	bool IsActionRunningByName(const StringRef& name)const { return FindActionByName(name) != nullptr; }
	bool IsActionRunningByTagRecursively(int tag)const { return FindActionByTagRecursively(tag) != nullptr; }
	bool IsActionRunningByNameRecursively(const StringRef& name)const { return FindActionByNameRecursively(name) != nullptr; }

	virtual ActionItemType* RunAction(ActionItemType* action) = 0;
	virtual ActionItemType* RunActionAsync(ActionItemType* action) = 0;

	virtual ActionItemType* FindActionByTag(int tag)const = 0;
	virtual ActionItemType* FindActionByName(const StringRef& name) const = 0;

	virtual ActionItemType* FindActionByTagRecursively(int tag)const = 0;
	virtual ActionItemType* FindActionByNameRecursively(const StringRef& name) const = 0;


	virtual void PauseAllActions() = 0;
	virtual void ResumeAllActions() = 0;
	virtual void StopAllActions() = 0;
	virtual void ResetAllActions() = 0;
	virtual void StartAllActions() = 0;
	virtual void RestartAllActions() = 0;


	virtual bool PauseActionsByTag(int tag) = 0;
	virtual bool ResumeActionsByTag(int tag) = 0;
	virtual bool StopActionsByTag(int tag) = 0;
	virtual bool ResetActionsByTag(int tag) = 0;
	virtual bool StartActionsByTag(int tag) = 0;
	virtual bool RestartActionsByTag(int tag) = 0;



	bool PauseActionByTag(int tag)
	{
		ActionItemType* action = FindActionByTag(tag);
		return PauseAction(action);
	}
	bool ResumeActionByTag(int tag)
	{
		ActionItemType* action = FindActionByTag(tag);
		return ResumeAction(action);
	}
	bool StopActionByTag(int tag)
	{
		ActionItemType* action = FindActionByTag(tag);
		return StopAction(action);
	}
	bool ResetActionByTag(int tag)
	{
		ActionItemType* action = FindActionByTag(tag);
		return ResetAction(action);
	}
	bool RestartActionByTag(int tag)
	{
		ActionItemType* action = FindActionByTag(tag);
		return RestartAction(action);
	}

	bool StartActionByTag(int tag)
	{
		ActionItemType* action = FindActionByTag(tag);
		return StartAction(action);
	}

	bool PauseActionByName(const StringRef& name)
	{
		ActionItemType* action = FindActionByName(name);
		return PauseAction(action);
	}
	bool ResumeActionByName(const StringRef& name)
	{
		ActionItemType* action = FindActionByName(name);
		return ResumeAction(action);
	}
	bool StopActionByName(const StringRef& name)
	{
		ActionItemType* action = FindActionByName(name);
		return StopAction(action);
	}

	bool ResetActionByName(const StringRef& name)
	{
		ActionItemType* action = FindActionByName(name);
		return ResetAction(action);
	}
	bool RestartActionByName(const StringRef& name)
	{
		ActionItemType* action = FindActionByName(name);
		return RestartAction(action);
	}

	bool StartActionByName(const StringRef& name)
	{
		ActionItemType* action = FindActionByName(name);
		return StartAction(action);
	}


	virtual bool IsActionRunning()const = 0;

	virtual bool RemoveAction(ActionItemType* action) = 0;
	virtual bool PauseAction(ActionItemType* action) = 0;
	virtual bool ResumeAction(ActionItemType* action) = 0;
	virtual bool StopAction(ActionItemType* action) = 0;
	virtual bool ResetAction(ActionItemType* action) = 0;
	virtual bool RestartAction(ActionItemType* action) = 0;
	virtual bool StartAction(ActionItemType* action) = 0;

};

MEDUSA_END;