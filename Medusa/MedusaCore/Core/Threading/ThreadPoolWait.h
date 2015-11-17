// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Command/ICommand.h"
#include "Core/String/HeapString.h"
#include "Core/Threading/IWaitable.h"
#include "Core/Threading/posix/ThreadPoolWaitImp_posix.h"
#include "Core/Threading/win/ThreadPoolWaitImp_win.h"

MEDUSA_BEGIN;


class ThreadPoolWait :protected ThreadPoolWaitImp,public ICommand
{
public:
	enum class WaitResult
	{
		Success,
		Timeout,
		Abandoned
	};
private:
	friend class ThreadPool;
	ThreadPoolWait(const StringRef& name, ICommand* command, IWaitable* waitable, uint timeoutMilliseconds = (uint)-1);
	~ThreadPoolWait(void);
public:
	StringRef Name() const { return mName; }
	ICommand* Command() const { return mCommand; }

	void Sumbit();
	void Cancel();
	void Wait(bool cancelPending = false);

	void Run(WaitResult result);
	virtual bool OnExecute()override;
private:
	ThreadPoolWait(const ThreadPoolWait&);
	ThreadPoolWait& operator=(const ThreadPoolWait&);
protected:
	HeapString mName;
	ICommand* mCommand;
	IWaitable* mWaitable;

	WaitResult mResult;
	uint mTimeout;	//in milliseconds,0 means no wait,-1 means wait infinite
};

MEDUSA_END;
