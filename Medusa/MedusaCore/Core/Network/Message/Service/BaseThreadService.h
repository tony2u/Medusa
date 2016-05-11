// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "IService.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/ThreadEvent.h"
#include "Core/Threading/Mutex.h"

MEDUSA_BEGIN;

class BaseThreadService:public IService
{
public:
	BaseThreadService(size_t id, StringRef host, ushort port);
	virtual ~BaseThreadService();

public:
	virtual bool Start();
	virtual void Stop();

	virtual void Submit(IMessage* message);
protected:
	virtual void OnStart() {}
	virtual void OnRun() {}

private:
	void OnThread(Thread& thread);
protected:
	Thread mThread;

	ThreadEvent mThreadEvent;
	NonRecursiveMutex mMessageMutex;
};
MEDUSA_END;
