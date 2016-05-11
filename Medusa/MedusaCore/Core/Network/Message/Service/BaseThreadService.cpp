// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BaseThreadService.h"
#include "Core/Log/Log.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;

BaseThreadService::BaseThreadService(size_t id, StringRef host, ushort port)
	:IService(id, host, port)
{
	mThread.SetCallback(Bind(&BaseThreadService::OnThread, this));
	mThreadEvent.Initialize();
}

BaseThreadService::~BaseThreadService()
{
	mThreadEvent.Uninitialize();
}

bool BaseThreadService::Start()
{
	mThread.Start();

	if (mState== ServiceState::Failed)
	{
		mState = ServiceState::None;	//restart
	}

	return true;
}

void BaseThreadService::Stop()
{
	mThread.PrepareToCancel();
	mThreadEvent.Set();

	mThread.Join();
}

void BaseThreadService::OnThread(Thread& thread)
{
	while (true)
	{
		switch (mState)
		{
		case ServiceState::Failed:
			//sleep
			break;
		case ServiceState::None:
			OnStart();
			break;
		case ServiceState::Running:
		{
			OnRun();
			if (mMessageQueue.IsEmpty())
			{

			}
			else
			{
				//select
				ScopedLock lock(mMessageMutex);
			}

		}
		break;
		default:
			break;
		}

		if (!thread.IsCancelled())
		{
			mThreadEvent.Wait();
		}
		else
		{
			break;
		}
	}

	mState = ServiceState::None;
}

void BaseThreadService::Submit(IMessage* message)
{
	ScopedLock lock(mMessageMutex);
	mMessageQueue.Push(message);
	message->SetState(MessageState::Running);
	mThreadEvent.Set();	//wakeup thread
}


MEDUSA_END;
