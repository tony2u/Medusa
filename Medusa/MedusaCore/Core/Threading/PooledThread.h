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


class PooledThread:public Thread
{
public:
	typedef Delegate<bool(PooledThread& sender)> CompleteDelegate;
public:
	PooledThread(const StringRef& name, CompleteDelegate completeDelegate, void* userData=nullptr);
	virtual ~PooledThread(void);

	void WaitForComplete();
	void Activate(const ShareCommand& val);

	const ShareCommand& Command() const { return mCommand; }
	bool IsIdle()const;
private:
	virtual bool OnBeforeJoin()override;
	virtual void OnAfterJoin()override;

	virtual void OnRun()override;
	virtual void OnRunCommands();

protected:
	ThreadEvent mStartEvent;
	ThreadEvent mCompleteEvent;
	ShareCommand mCommand;
	NonRecursiveMutex mCommandMutex;
	CompleteDelegate mCompleteDelegate;
};

MEDUSA_END;
