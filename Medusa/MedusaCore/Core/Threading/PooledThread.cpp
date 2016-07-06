// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "PooledThread.h"
#include "Core/Command/ICommand.h"
#include "Core/Threading/ScopedLock.h"

MEDUSA_BEGIN;

PooledThread::PooledThread(const StringRef& name, CompleteDelegate completeDelegate, void* userData/*=nullptr*/)
	: Thread(name,nullptr,userData),
	mStartEvent(false,true),
	mCommand(nullptr),
	mCompleteDelegate(completeDelegate)
{
}

PooledThread::~PooledThread(void)
{

}


bool PooledThread::OnBeforeJoin()
{
	PrepareToCancel();
	mStartEvent.Set();
	return true;
}

void PooledThread::OnAfterJoin()
{
	mStartEvent.Uninitialize();
	mCompleteEvent.Uninitialize();
}

void PooledThread::OnRun()
{
	while (!IsCancelled())
	{
		mStartEvent.Wait();
		if (IsCancelled())
		{
			break;
		}
		OnRunCommands();

		if (mCompleteDelegate)
		{
			if (!mCompleteDelegate(*this))
			{
				SetThreadState(ThreadState::None);
				mStartEvent.Reset();
				return;
			}
		}
		mStartEvent.Reset();

	}
}


void PooledThread::OnRunCommands()
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



void PooledThread::Activate(const ShareCommand& val)
{
	{
		ScopedLock lock(mCommandMutex);
		mCommand = val;
	}
	
	mStartEvent.Set();
}

bool PooledThread::IsIdle() const
{
	return !mStartEvent.IsSet();
}



MEDUSA_END;