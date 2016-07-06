// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/Thread.h"
#include "EventLoop.h"

MEDUSA_BEGIN;


class EventLoopThread:public Thread
{
public:
	EventLoopThread(const StringRef& name, const StringRef& pollerName, void* userData=nullptr);
	virtual ~EventLoopThread(void);
	EventLoop& MutableLoop() { return mLoop; }

protected:
	virtual void OnRun()override;
	virtual bool OnBeforeJoin()override;

protected:
	EventLoop mLoop;
};

MEDUSA_END;
