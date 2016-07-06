// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Collection/HashSet.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Threading/Mutex.h"
#include "Core/String/HeapString.h"
#include "Core/Threading/win/ThreadPoolImp_win.h"
#include "Core/Threading/posix/ThreadPoolImp_posix.h"

#include "ThreadPoolWork.h"
#include "ThreadPoolWait.h"
#include "ThreadPoolTimer.h"


MEDUSA_BEGIN;


class ThreadPool :protected ThreadPoolImp
{
	friend class ThreadPoolWork;
	friend class ThreadPoolTimer;
	friend class ThreadPoolWait;

	using WorkType = Share<ThreadPoolWork>;
	using TimerType = Share<ThreadPoolTimer>;
	using WaitType = Share<ThreadPoolWait>;

public:
	ThreadPool();
	virtual ~ThreadPool(void);
public:
	bool Initialize(uint minCount = ThreadPool::MinCount, uint maxCount = ThreadPool::MaxCount, bool autoManaged = true);
	void Uninitialize();
#pragma region Work
public:
	WorkType TrySumbitWork(Action action);
	WorkType TrySumbitWork(ActionWithUserData action, void* userData);

	WorkType CreateWork(const StringRef& name, const ShareCommand& command);
	WorkType CreateWork(const ShareCommand& command);

	WorkType FindWork(const StringRef& name)const;

	void SubmitWork(const WorkType& work);
	void WaitWork(const WorkType& work, bool cancelPending = false);
	void DeleteWork(const WorkType& work);

	void SubmitWork(const StringRef& name);
	void WaitWork(const StringRef& name, bool cancelPending = false);
	void DeleteWork(const StringRef& name);
	void WaitAllWork(bool cancelPending = false);
	void ClearAllWork();
#pragma endregion Work
#pragma region Timer
public:
	TimerType CreateTimer(const StringRef& name, const ShareCommand& command, uint delay = 0, uint repeatCount = 0, uint repeatInterval = 0, uint repeatIntervalRange = 0);
	TimerType CreateTimer(const ShareCommand& command, uint delay = 0, uint repeatCount = 0, uint repeatInterval = 0, uint repeatIntervalRange = 0);

	TimerType FindTimer(const StringRef& name)const;

	void SubmitTimer( const TimerType& timer);
	void WaitTimer(const TimerType& timer, bool cancelPending = false);
	void DeleteTimer(const TimerType& timer);

	void SubmitTimer(const StringRef& name);
	void WaitTimer(const StringRef& name, bool cancelPending = false);
	void DeleteTimer(const StringRef& name);

	void WaitAllTimer(bool cancelPending = false);
	void ClearAllTimer();
#pragma endregion Timer
#pragma region Wait
public:
	WaitType CreateWait(const StringRef& name, const ShareCommand& command, IWaitable* waitable);
	WaitType CreateWait(const ShareCommand& command, IWaitable* waitable);

	WaitType FindWait(const StringRef& name)const;

	void SubmitWait(const WaitType& wait);
	void WaitWait(const WaitType& wait, bool cancelPending = false);
	void DeleteWait(const WaitType& wait);

	void SubmitWait(const StringRef& name);
	void WaitWait(const StringRef& name, bool cancelPending = false);
	void DeleteWait(const StringRef& name);

	void WaitAllWait(bool cancelPending = false);
	void ClearAllWait();
#pragma endregion Wait

public:
	void WaitAll(bool cancelPending = false);
	void ClearAll();

protected:
	Dictionary<HeapString, Share<ThreadPoolWork>> mNamedWorks;
	HashSet<Share<ThreadPoolWork>> mUnnamedWorks;


	Dictionary<HeapString, Share<ThreadPoolTimer>> mNamedTimers;
	HashSet<Share<ThreadPoolTimer>> mUnnamedTimers;

	Dictionary<HeapString, Share<ThreadPoolWait>> mNamedWaits;
	HashSet<Share<ThreadPoolWait>> mUnnamedWaits;
};



MEDUSA_END;
