// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "PooledThread.h"
#include "Core/Command/ICommand.h"
#include "Core/Threading/ScopedLock.h"

MEDUSA_BEGIN;

PooledThread::PooledThread(const StringRef& name, CompleteDelegate completeDelegate, void* userData)
	: mThread(name,nullptr,userData),
	mStartEvent(false,true),
	mCommand(nullptr),
	mCompleteDelegate(completeDelegate)
{
}

PooledThread::~PooledThread(void)
{

}


bool PooledThread::Initialize()
{
	mThread.SetCallback(Bind(&PooledThread::OnThredCallback,this));
	return true;
}
void PooledThread::Start()
{
	mThread.Start();
}

bool PooledThread::Uninitialize()
{
	Stop();

	mStartEvent.Uninitialize();
	mCompleteEvent.Uninitialize();

	return true;
}

void PooledThread::OnThredCallback(Thread& thread)
{
	while (!thread.IsCancelled())
	{
		mStartEvent.Wait();
		if (thread.IsCancelled())
		{
			break;
		}
		OnRun();

		if (mCompleteDelegate)
		{
			if (!mCompleteDelegate(*this))
			{
				thread.SetThreadState(ThreadState::None);
				mStartEvent.Reset();
				return;
			}
		}
		mStartEvent.Reset();

	}
}


void PooledThread::OnRun()
{
	//no need to lock as it always run after start event
	ScopedLock lock(mCommandMutex);
	if (mCommand != nullptr)
	{
		mCommand->Execute();
		mCommand->Release();
		mCommand = nullptr;
	}

}

void PooledThread::WaitForComplete()
{
	mCompleteEvent.Wait();
}

void PooledThread::Stop()
{
	mThread.PrepareToCancel();
	mStartEvent.Set();

	mThread.Join();

}

void PooledThread::Activate(ICommand* val)
{
	{
		ScopedLock lock(mCommandMutex);
		SAFE_ASSIGN_REF(mCommand, val);
	}
	
	mStartEvent.Set();
}

bool PooledThread::IsIdle() const
{
	return !mStartEvent.IsSet();
}



MEDUSA_END;