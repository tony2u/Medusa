// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/ThreadEvent.h"

MEDUSA_BEGIN;


class PulseThread:public Thread
{
public:
	PulseThread(const StringRef& name = StringRef::Empty);
	~PulseThread(void);

	void Pulse();
	void WaitForComplete();

	bool IsThreadingDisabled() const { return mThreadingDisabled; }
	void DisableThreadingDisabled(bool val) { mThreadingDisabled = val; }
protected:
	virtual bool OnBeforeStart()override;
	virtual bool OnBeforeJoin()override;

	virtual void OnAfterJoin()override;
	virtual void OnRun()override;

	void OnThreadCallback(Thread& thread);

protected:
	virtual void OnPulse();

protected:
	Thread mThread;
	ThreadEvent mStartEvent;
	ThreadEvent mCompleteEvent;
	bool mThreadingDisabled;


};

MEDUSA_END;
