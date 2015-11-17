// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "PulseThread.h"
#include "Core/Threading/Semaphore.h"

MEDUSA_BEGIN;

PulseThread::PulseThread(const StringRef& name/*=StringRef::Empty*/)
	: mThread(name), mThreadingDisabled(false)
{
}

PulseThread::~PulseThread(void)
{

}

bool PulseThread::Initialize(bool disableThreading /*= false*/)
{
	mThreadingDisabled = disableThreading;
	mThread.SetCallback(Bind(&PulseThread::OnThreadCallback,this));

	if (!mThreadingDisabled)
	{
		mThread.Start();
		mStartEvent.Initialize(true,false);
		mCompleteEvent.Initialize();
	}
	return true;
}


bool PulseThread::Uninitialize()
{
	if (!mThreadingDisabled)
	{
		Stop();

		mStartEvent.Uninitialize();
		mCompleteEvent.Uninitialize();
	}

	return true;
}

void PulseThread::OnThreadCallback(Thread& thread)
{
	while (!thread.IsCancelled())
	{
		mStartEvent.Wait();
		if (thread.IsCancelled())
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

void PulseThread::Stop()
{
	if (!mThreadingDisabled)
	{
		mThread.PrepareToCancel();
		mStartEvent.Set();
		mCompleteEvent.Set();

		mThread.Join();
	}
	else
	{
	}

}





MEDUSA_END;