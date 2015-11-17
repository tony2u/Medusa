// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Task.h"
#include "Core/Command/ICommand.h"
#include "Core/Threading/ThreadPool.h"
#include "Core/Threading/ThreadPoolWork.h"
#include "Core/Command/SleepCommand.h"
#include "Core/Command/Processor/MainCommandProcessor.h"


MEDUSA_BEGIN;

Task::Task(ICommand* command /*= nullptr*/, ExecuteOption option /*= TaskOption::Async*/)
	:mCommand(command), mPoolWork(nullptr), mOption(option)
{
	SAFE_RETAIN(mCommand);
}

Task::~Task(void)
{
	Uninitialize();
}


bool Task::Uninitialize()
{
	if (mPoolWork != nullptr)
	{
		ThreadPool::Instance().DeleteWork(mPoolWork);
		mPoolWork = nullptr;
	}
	SAFE_RELEASE(mCommand);
	SAFE_DELETE_COLLECTION(mThenTasks);
	return true;
}


void Task::SetCommand(ICommand* val)
{
	SAFE_ASSIGN_REF(mCommand, val);
}


void Task::OnTaskExecute()
{
	//wait parent tasks to complete
	Task::WaitAll(mWhenTasks);

	OnSelfExecute();

	//start child tasks
	FOR_EACH_COLLECTION(i, mThenTasks)
	{
		Task* task = *i;
		task->Start();
	}
}


void Task::OnSelfExecute()
{
	if (mCommand != nullptr)
	{
		mCommand->Execute();
	}
}

void Task::Start()
{
	switch (mOption)
	{
		case ExecuteOption::Sync:
			OnTaskExecute();
			break;
		case ExecuteOption::Async:
			if (mPoolWork == nullptr)
			{
				mPoolWork = ThreadPool::Instance().TrySumbitWork(Bind(&Task::OnTaskExecute,this));
			}
			mPoolWork->Sumbit();
			break;
		case ExecuteOption::Deferred:
		{
			Action0&& action = Bind(&Task::OnTaskExecute, this);
			MainCommandProcessor::Instance().ReceiveAsync(action);
			break;
		}
	}
	
}

void Task::Wait()
{
	if (mPoolWork != nullptr)
	{
		mPoolWork->Wait();
	}
}

void Task::When(Task* task)
{
	mWhenTasks.Add(task);
}

void Task::When(const List<Task*>& tasks)
{
	mWhenTasks.AddRange(tasks);
}

void Task::Then(Task* task)
{
	mThenTasks.Add(task);
}

Task* Task::ContinueWith(ICommand* command)
{
	Task* task = new Task(command, mOption);
	Then(task);
	return task;

}

void Task::WaitAll(const List<Task*>& tasks)
{
	FOR_EACH_COLLECTION(i, tasks)
	{
		Task* task = *i;
		task->Wait();
	}
}

Task* Task::Run(ICommand* command, ExecuteOption option /*= TaskOption::Async*/)
{
	Task* task = new Task(command, option);
	task->Start();
	return task;
}

Task* Task::Delay(long milliseconds, ExecuteOption option /*= TaskOption::Async*/)
{
	return new Task(new SleepCommand(milliseconds), option);
}

Task* Task::YieldSelf(ExecuteOption option /*= TaskOption::Async*/)
{
	return new Task(new SleepCommand(0), option);
}


Task* Task::WhenAll(const List<Task*>& tasks, ICommand* command, ExecuteOption option /*= TaskOption::Async*/)
{
	Task* task = new Task(command, option);
	task->When(tasks);
	return task;
}


MEDUSA_END;