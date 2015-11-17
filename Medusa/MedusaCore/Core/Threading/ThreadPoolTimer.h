// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Command/ICommand.h"
#include "Core/String/HeapString.h"
#include "Core/Threading/posix/ThreadPoolTimerImp_posix.h"
#include "Core/Threading/win/ThreadPoolTimerImp_win.h"

MEDUSA_BEGIN;


class ThreadPoolTimer :protected ThreadPoolTimerImp,public ICommand
{
	friend class ThreadPool;
	ThreadPoolTimer(const StringRef& name, ICommand* command, uint delay = 0, uint repeatCount = 0, uint repeatInterval = 0, uint repeatIntervalRange = 0);
	~ThreadPoolTimer(void);
public:
	StringRef Name() const { return mName; }
	ICommand* Command() const { return mCommand; }

	uint Delay() const { return mDelay; }
	void SetDelay(uint val) { mDelay = val; }

	uint RepeatCount() const { return mRepeatCount; }
	void SetRepeatCount(uint val) { mRepeatCount = val; }

	uint RepeatInterval() const { return mRepeatInterval; }
	void SetRepeatInterval(uint val) { mRepeatInterval = val; }

	uint RepeatIntervalRange() const { return mRepeatIntervalRange; }
	void SetRepeatIntervalRange(uint val) { mRepeatIntervalRange = val; }

	void Sumbit();
	void Wait(bool cancelPending = false);
	bool IsSubmitted()const;

	void Cancel();
	virtual bool OnExecute()override;
private:
	ThreadPoolTimer(const ThreadPoolTimer&);
	ThreadPoolTimer& operator=(const ThreadPoolTimer&);
protected:
	HeapString mName;
	ICommand* mCommand;

	uint mDelay;	//0 means invoke this right now, others to wait sometime in milliseconds
	uint mRepeatCount;	//0 means not repeat,-1 means repeat forever
	uint mRepeatInterval;	//in milliseconds
	uint mRepeatIntervalRange;	//interval changes in range(+-),in milliseconds

};

MEDUSA_END;
