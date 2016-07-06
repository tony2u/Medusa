// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Threading/Mutex.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;


class ThreadEventImp
{
protected:
	struct ThreadEventMultipleWaiter
	{
		mutable NonRecursiveMutex Mutex;
		pthread_cond_t Cond;
		union
		{
			int FiredEventIndex; //WFSO
			int EventsLeftCount; //WFMO
		};
		bool IsWaitAll;

		ThreadEventMultipleWaiter(uint count, bool isWaitAll);
		~ThreadEventMultipleWaiter();

	};

	struct ThreadEventMultipleWaiterIndex
	{
		ThreadEventMultipleWaiterIndex(ThreadEventMultipleWaiter* waiter,int index);
		ThreadEventMultipleWaiter* Waiter;
		int Index;
	};
public:
	ThreadEventImp();
	~ThreadEventImp(void);

protected:
	
	bool TryWaitWithoutLock();
#ifdef MEDUSA_THREADING_MULTIPLE_WAIT
	void TryRemoveExpiredWaitsWithoutLock(ThreadEventMultipleWaiter* waiter);
	void RegisterWaitWithoutLock(ThreadEventMultipleWaiter* waiter, int index);
#endif
protected:
	mutable NonRecursiveMutex mMutex;
	pthread_cond_t mCond;
	volatile bool mState;
	bool mIsAutoReset;

#ifdef MEDUSA_THREADING_MULTIPLE_WAIT
	//support for multiple wait
	List<ThreadEventMultipleWaiterIndex, NoCompare> mRegisteredWaits;
#endif
};

MEDUSA_END;
#endif