// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/ThreadEvent.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Threading/Mutex.h"
MEDUSA_BEGIN;


class PooledThread
{
public:
	typedef Delegate<bool(PooledThread& sender)> CompleteDelegate;
public:
	PooledThread(const StringRef& name, CompleteDelegate completeDelegate, void* userData);
	virtual ~PooledThread(void);

	virtual bool Initialize();
	virtual bool Uninitialize();
	void Stop();
	void Start();
	void WaitForComplete();
	void Activate(ICommand* val);

	ICommand* Command() const { return mCommand; }
	bool IsIdle()const;
private:
	void OnThredCallback(Thread& thread);
	void OnRun();

protected:
	Thread mThread;
	ThreadEvent mStartEvent;
	ThreadEvent mCompleteEvent;
	ICommand* mCommand;
	NonRecursiveMutex mCommandMutex;
	CompleteDelegate mCompleteDelegate;
};

MEDUSA_END;
