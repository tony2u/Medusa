// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "TaskStage.h"
#include "Core/Task/Task.h"

MEDUSA_BEGIN;

TaskStage::TaskStage()
{

}

TaskStage::~TaskStage(void)
{

}

void TaskStage::Register(Task* task)
{
	mTasks.Add(task);
}
void TaskStage::Clear()
{
	mTasks.Clear();
}

void TaskStage::Start()
{
	for (auto task : mTasks)
	{
		task->Start();
	}
}

void TaskStage::Wait()
{
	for (auto task : mTasks)
	{
		task->Wait();
	}
}

void TaskStage::SetOption(ExecuteOption option)
{
	for (auto task : mTasks)
	{
		task->SetOption(option);
	}
}

void TaskStage::StartAndWait()
{
	Start();
	Wait();
}


MEDUSA_END;