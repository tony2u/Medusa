// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;



class Task:public IInitializable
{
public:
	Task(ICommand* command = nullptr, ExecuteOption option = ExecuteOption::Async);
	virtual ~Task(void);

	virtual bool Uninitialize();

	ICommand* Command() const { return mCommand; }
	void SetCommand(ICommand* val);

	ExecuteOption Option() const { return mOption; }
	void SetOption(ExecuteOption val) { mOption = val; }

	void Start();
	void Wait();
	bool IsSync()const { return mPoolWork == nullptr; }
public:
	Task* ContinueWith(ICommand* command);

	void When(Task* task);
	void When(const List<Task*>& tasks);
	void Then(Task* task);
public:
	static Task* Delay(long milliseconds, ExecuteOption option = ExecuteOption::Async);
	static Task* Run(ICommand* command, ExecuteOption option = ExecuteOption::Async);
	static Task* YieldSelf(ExecuteOption option = ExecuteOption::Async);

	static Task* WhenAll(const List<Task*>& tasks, ICommand* command, ExecuteOption option = ExecuteOption::Async);
	static void WaitAll(const List<Task*>& tasks);
protected:
	void OnTaskExecute();
	virtual void OnSelfExecute();

protected:
	ICommand* mCommand;
	
	ThreadPoolWork* mPoolWork;
	ExecuteOption mOption;
	
	List<Task*> mWhenTasks;	//weak ref
	List<Task*> mThenTasks;	//strong ref
};

MEDUSA_END;
