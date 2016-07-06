// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Task.h"
#include "Core/Command/ICommand.h"
#include "Core/Threading/ThreadPool.h"
#include "Core/Threading/ThreadPoolWork.h"
#include "Core/Command/SleepCommand.h"
#include "Core/Command/Executor/SyncCommandExecutor.h"


MEDUSA_BEGIN;

Task::Task(const ShareCommand& command /*= nullptr*/, ExecuteOption option /*= TaskOption::Async*/)
	:mCommand(command), mPoolWork(nullptr), mOption(option)
{

}

Task::~Task(void)
{
	Uninitialize();
}


bool Task::Uninitialize()
{
	if (mPoolWork != nullptr)
	{
		mPoolWork->Pool()->DeleteWork(mPoolWork);
		mPoolWork = nullptr;
	}
	mCommand = nullptr;
	SAFE_DELETE_COLLECTION(mThenTasks);
	return true;
}


void Task::SetCommand(const ShareCommand& val)
{
	mCommand = val;
}


void Task::OnTaskExecute()
{
	//wait parent tasks to complete
	Task::WaitAll(mWhenTasks);

	OnSelfExecute();

	//start child tasks
	for(auto task:mThenTasks)
	{
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
				if (mPool!=nullptr)
				{
					mPoolWork = mPool->TrySumbitWork(Bind(&Task::OnTaskExecute, this));
				}
				else
				{
					assert(false);	//TODO
				}
			}
			mPoolWork->Sumbit();
			break;
		case ExecuteOption::Deferred:
		{
			Action&& action = Bind(&Task::OnTaskExecute, this);
			SyncCommandExecutor::Instance().ExecuteAsync(action);
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

Task* Task::ContinueWith(const ShareCommand& command)
{
	Task* task = new Task(command, mOption);
	Then(task);
	return task;

}

void Task::WaitAll(const List<Task*>& tasks)
{
	for (auto task : tasks)
	{
		task->Wait();
	}
}

Task* Task::Run(const ShareCommand& command, ExecuteOption option /*= TaskOption::Async*/)
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


Task* Task::WhenAll(const List<Task*>& tasks, const ShareCommand& command, ExecuteOption option /*= TaskOption::Async*/)
{
	Task* task = new Task(command, option);
	task->When(tasks);
	return task;
}


MEDUSA_END;