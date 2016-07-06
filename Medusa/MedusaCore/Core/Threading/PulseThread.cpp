// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "PulseThread.h"
#include "Core/Threading/Semaphore.h"

MEDUSA_BEGIN;

PulseThread::PulseThread(const StringRef& name/*=StringRef::Empty*/)
	: Thread(name), mThreadingDisabled(false)
{
}

PulseThread::~PulseThread(void)
{

}

bool PulseThread::OnBeforeStart()
{
	if (!mThreadingDisabled)
	{
		mStartEvent.Initialize(true, false);
		mCompleteEvent.Initialize();
	}
	
	return !mThreadingDisabled;
}

bool PulseThread::OnBeforeJoin()
{
	if (!mThreadingDisabled)
	{
		PrepareToCancel();
		mStartEvent.Set();
		mCompleteEvent.Set();
	}

	return !mThreadingDisabled;
}

void PulseThread::OnAfterJoin()
{
	if (!mThreadingDisabled)
	{
		mStartEvent.Uninitialize();
		mCompleteEvent.Uninitialize();
	}
}

void PulseThread::OnRun()
{
	while (!IsCancelled())
	{
		mStartEvent.Wait();
		if (IsCancelled())
		{
			break;
		}
		OnPulse();
		mCompleteEvent.Set();
	}
}


void PulseThread::OnPulse()
{

}

void PulseThread::Pulse()
{
	if (mThreadingDisabled)
	{
	}
	else
	{
		mStartEvent.Set();
	}

}


void PulseThread::WaitForComplete()
{
	if (mThreadingDisabled)
	{
		OnPulse();
	}
	else
	{
		mCompleteEvent.Wait();
	}

}


MEDUSA_END;