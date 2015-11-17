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

class BaseFrameCommandProcessor
{
	typedef SwapValue<List<ICommand*>> CommandQueue;
protected:
	BaseFrameCommandProcessor();
	~BaseFrameCommandProcessor(void);
public:
	virtual bool Initialize(bool disableThreading = false);
	virtual bool Uninitialize();
public:
	void Start();
	void Stop();

	void Clear();
	void StopAndClear();

	void ReceiveInstant(ICommand* command);
	void ReceiveInstantAsync(ICommand* command);
	void ProcessInstant(ICommand* command);

	void ReceiveInstant(const List<ICommand*>& commands);
	void ReceiveInstantAsync(const List<ICommand*>& commands);


	void ReceiveFrame(ICommand* command);
	void ReceiveFrameAsync(ICommand* command);

	void ReceiveFrame(const List<ICommand*>& commands);
	void ReceiveFrameAsync(const List<ICommand*>& commands);
	void StartFrame();

	void WaitForInstantComplete();
	void WaitForFrameComplete();

private:
	void OnProcessInstant();
	void OnProcessFrame();


	void OnThreadCallbackHelper(Thread& thread);
	void TrySwapFrameCommands();
protected:
	Thread mThread;
	
	CommandQueue mInstantCommands;
	NonRecursiveMutex mInstantCommandMutex;
	ThreadEvent mInstantStartEvent;
	ThreadEvent mInstantCompleteEvent;


	CommandQueue mFrameCommands;
	NonRecursiveMutex mFrameCommandMutex;

	ThreadEvent mFrameStartEvent;
	ThreadEvent mFrameCompleteEvent;


	bool mThreadingDisabled;
	volatile bool mIsFrameEnabled;
};


MEDUSA_END;