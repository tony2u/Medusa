// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FrameTask.h"

MEDUSA_BEGIN;

FrameTask::FrameTask(ExecuteOption option /*= TaskOption::Async*/)
	:Task(nullptr, option), mInterval(0)
{
	
}

FrameTask::~FrameTask(void)
{
	
}



void FrameTask::Update(float dt)
{
	mInterval = dt;
	Start();
}

void FrameTask::OnSelfExecute()
{
	OnUpdate(mInterval);
}

void FrameTask::OnUpdate(float dt)
{

}

MEDUSA_END;