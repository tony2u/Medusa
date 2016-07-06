// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "EventLoopThreadPool.h"

MEDUSA_BEGIN;

EventLoopThreadPool::EventLoopThreadPool()
{

}

EventLoopThreadPool::~EventLoopThreadPool(void)
{

}


bool EventLoopThreadPool::Start(uint threadCount, const StringRef& pollerName)
{
	HeapString threadName;
	FOR_EACH_SIZE(i, threadCount)
	{
		threadName.Format("EventLoopThread-{}", i);
		EventLoopThread* thread = new EventLoopThread(threadName, pollerName);
		mThreads.Add(thread);
		thread->Start();
	}
	return true;
}



void EventLoopThreadPool::Stop()
{
	for (auto item:mThreads)
	{
		item->Join();
	}
	SAFE_DELETE_COLLECTION(mThreads);
}

EventLoop* EventLoopThreadPool::NextLoop()
{
	auto* thread = mThreads[mCurrent];
	auto* loop = &thread->MutableLoop();
	mCurrent = (mCurrent + 1) % mThreads.Count();
	return loop;
}

MEDUSA_END;