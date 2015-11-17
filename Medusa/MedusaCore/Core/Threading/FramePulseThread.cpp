// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FramePulseThread.h"

MEDUSA_BEGIN;

FramePulseThread::FramePulseThread()
{
	
}

FramePulseThread::~FramePulseThread(void)
{
	
}

void FramePulseThread::Update(float dt)
{
	mInterval = dt;
	Pulse();
}

MEDUSA_END;