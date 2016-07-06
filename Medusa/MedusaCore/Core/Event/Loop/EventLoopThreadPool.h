// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "EventLoopThread.h"

MEDUSA_BEGIN;


class EventLoopThreadPool
{
public:
	EventLoopThreadPool();
	~EventLoopThreadPool(void);
public:
	bool Start(uint threadCount, const StringRef& pollerName);
	void Stop();
	EventLoop* NextLoop();
	const List<EventLoopThread*>& Threads() const { return mThreads; }

protected:

	List<EventLoopThread*> mThreads;
	uint mCurrent = 0;
};

MEDUSA_END;
