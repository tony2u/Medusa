// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Threading/Thread.h"
#include "Core/Collection/List.h"
#include "Core/Threading/ThreadEvent.h"
#include "Core/Pattern/SwapValue.h"
#include "Core/Threading/Mutex.h"

MEDUSA_BEGIN;

class BaseThreadCommandProcessor
{
	typedef SwapValue<List<ICommand*>> CommandQueue;
protected:
	BaseThreadCommandProcessor();
	~BaseThreadCommandProcessor(void);

	virtual bool Initialize(bool disableThreading = false);
	virtual bool Uninitialize();
public:
	void Start();
	void Stop();

	void Clear();
	void StopAndClear();

	void Receive(ICommand* command);
	void ReceiveAsync(ICommand* command);

	void Receive(const List<ICommand*>& commands);
	void ReceiveAsync(const List<ICommand*>& commands);


	void WaitForComplete();
private:
	void OnProcess();

	void OnThreadCallbackHelper(Thread& thread);
protected:
	Thread mThread;
	ThreadEvent mStartEvent;
	ThreadEvent mCompleteEvent;

	NonRecursiveMutex mCommandMutex;
	CommandQueue mCommands;
	bool mThreadingDisabled;
};


MEDUSA_END;