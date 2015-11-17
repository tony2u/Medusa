// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/ThreadEvent.h"

MEDUSA_BEGIN;


class PulseThread
{
public:
	PulseThread(const StringRef& name = StringRef::Empty);
	~PulseThread(void);

	virtual bool Initialize(bool disableThreading = false);
	virtual bool Uninitialize();
	void Stop();
	void Pulse();
	void WaitForComplete();
private:
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
