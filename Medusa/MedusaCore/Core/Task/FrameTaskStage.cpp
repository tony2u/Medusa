// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FrameTaskStage.h"
#include "Core/Task/FrameTask.h"

MEDUSA_BEGIN;

FrameTaskStage::FrameTaskStage()
{

}

FrameTaskStage::~FrameTaskStage(void)
{

}

void FrameTaskStage::Add(FrameTask* task)
{
	mTasks.Add(task);
}
void FrameTaskStage::Clear()
{
	mTasks.Clear();
}

void FrameTaskStage::Update(float dt)
{
	for(auto task: mTasks)
	{
		task->Update(dt);
	}
}

void FrameTaskStage::Wait()
{
	for (auto task : mTasks)
	{
		task->Wait();
	}
}

void FrameTaskStage::ApplyOptionToAll(ExecuteOption option)
{
	for (auto task : mTasks)
	{
		task->SetOption(option);
	}
}

bool FrameTaskStage::Initialize()
{
	for (auto task : mTasks)
	{
		task->Initialize();
	}

	return true;
}

bool FrameTaskStage::Uninitialize()
{
	//in reverse order
	int count = (int)mTasks.Count();
	RETURN_TRUE_IF_ZERO(count);
	FOR_EACH_INT_END_BEGIN(i, count - 1, 0)
	{
		FrameTask* task = mTasks[i];
		RETURN_FALSE_IF_FALSE(task->Uninitialize());
	}
	return true;
}

void FrameTaskStage::UpdateAndWait(float dt)
{
	Update(dt);
	Wait();
}


MEDUSA_END;