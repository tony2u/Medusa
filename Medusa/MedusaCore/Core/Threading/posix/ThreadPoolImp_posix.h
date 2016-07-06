// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Collection/Queue.h"
#include "Core/Collection/List.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Threading/Mutex.h"
#include "Core/Pattern/SwapValue.h"

MEDUSA_BEGIN;

/*
in general case, we won't create many threads,as we're not building a server ^_^
so it's ok to foreach threads to find a idle one
*/
class ThreadPoolImp
{
	typedef SwapValue<Queue<ShareCommand>> CommandQueue;
public:
	ThreadPoolImp();
	~ThreadPoolImp(void);
public:
	const static uint MinCount = 2;
	const static uint MaxCount = 8;
protected:
	bool InitializeHelper(uint minCount = ThreadPoolImp::MinCount, uint maxCount = ThreadPoolImp::MaxCount, bool autoManaged = true);
	void UninitialzieHelper();
protected:
	void Enqueue(const ShareCommand& command);
	void CancelPendingCommands(const ShareCommand& command);

private:
	bool OnPooledThreadComplete(PooledThread& thread);
	PooledThread* EnqueueWorkToIdleThread(const ShareCommand& command);
	PooledThread* CreateThread();

protected:
	NonRecursiveMutex mCommandQueueMutex;
	CommandQueue mCommands;

	NonRecursiveMutex mThreadMutex;
	uint mMinThreadCount;
	uint mMaxThreadCount;

	List<PooledThread*> mAllThreads;
	uint mIdleThreadCount;
	uint mThreadIdCount;
};

MEDUSA_END;

#endif