// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Collection/HashSet.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Threading/Mutex.h"
#include "Core/String/HeapString.h"
#include "Core/Threading/win/ThreadPoolImp_win.h"
#include "Core/Threading/posix/ThreadPoolImp_posix.h"

MEDUSA_BEGIN;


class ThreadPool :public Singleton<ThreadPool>, protected ThreadPoolImp
{
	friend class Singleton < ThreadPool > ;
	friend class ThreadPoolWork;
	friend class ThreadPoolTimer;
	friend class ThreadPoolWait;

	ThreadPool();
	~ThreadPool(void);
public:
	bool Initialize(uint minCount = ThreadPool::MinCount, uint maxCount = ThreadPool::MaxCount, bool autoManaged = true);
	void Uninitialize();
#pragma region Work
public:
	ThreadPoolWork* TrySumbitWork(Action0 action);
	ThreadPoolWork* TrySumbitWork(Action1 action, void* userData);

	ThreadPoolWork* CreateWork(const StringRef& name, ICommand* command);
	ThreadPoolWork* CreateWork(ICommand* command);

	ThreadPoolWork* FindWork(const StringRef& name)const;

	void SubmitWork(ThreadPoolWork& work);
	void WaitWork(ThreadPoolWork& work, bool cancelPending = false);
	void DeleteWork(ThreadPoolWork* work);

	void SubmitWork(const StringRef& name);
	void WaitWork(const StringRef& name, bool cancelPending = false);
	void DeleteWork(const StringRef& name);
	void WaitAllWork(bool cancelPending = false);
	void ClearAllWork();
#pragma endregion Work
#pragma region Timer
public:
	ThreadPoolTimer* CreateTimer(const StringRef& name, ICommand* command, uint delay = 0, uint repeatCount = 0, uint repeatInterval = 0, uint repeatIntervalRange = 0);
	ThreadPoolTimer* CreateTimer(ICommand* command, uint delay = 0, uint repeatCount = 0, uint repeatInterval = 0, uint repeatIntervalRange = 0);

	ThreadPoolTimer* FindTimer(const StringRef& name)const;

	void SubmitTimer( ThreadPoolTimer& timer);
	void WaitTimer( ThreadPoolTimer& timer, bool cancelPending = false);
	void DeleteTimer(ThreadPoolTimer* timer);

	void SubmitTimer(const StringRef& name);
	void WaitTimer(const StringRef& name, bool cancelPending = false);
	void DeleteTimer(const StringRef& name);

	void WaitAllTimer(bool cancelPending = false);
	void ClearAllTimer();
#pragma endregion Timer
#pragma region Wait
public:
	ThreadPoolWait* CreateWait(const StringRef& name, ICommand* command, IWaitable* waitable);
	ThreadPoolWait* CreateWait(ICommand* command, IWaitable* waitable);

	ThreadPoolWait* FindWait(const StringRef& name)const;

	void SubmitWait( ThreadPoolWait& wait);
	void WaitWait( ThreadPoolWait& wait, bool cancelPending = false);
	void DeleteWait(ThreadPoolWait* wait);

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
	Dictionary<HeapString, ThreadPoolWork*> mNamedWorks;
	HashSet<ThreadPoolWork*> mUnnamedWorks;


	Dictionary<HeapString, ThreadPoolTimer*> mNamedTimers;
	HashSet<ThreadPoolTimer*> mUnnamedTimers;

	Dictionary<HeapString, ThreadPoolWait*> mNamedWaits;
	HashSet<ThreadPoolWait*> mUnnamedWaits;
};



MEDUSA_END;
