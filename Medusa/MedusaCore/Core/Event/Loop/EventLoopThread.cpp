// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "EventLoopThread.h"
#include "Core/Command/ICommand.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Event/Poll/PollerFactory.h"

MEDUSA_BEGIN;

EventLoopThread::EventLoopThread(const StringRef& name, const StringRef& pollerName, void* userData/*=nullptr*/)
	: Thread(name, nullptr, userData=nullptr)
{
	IPoller* poller = PollerFactory::Instance().Create(pollerName, &mLoop);
	mLoop.SetPoller(poller);
}

EventLoopThread::~EventLoopThread(void)
{
	
}

void EventLoopThread::OnRun()
{
	mLoop.AttachToCurrentThread();
	while (!IsCancelled())
	{
		mLoop.LoopForever();
	}

}


bool EventLoopThread::OnBeforeJoin()
{
	mLoop.Stop();
	return true;
}


MEDUSA_END;