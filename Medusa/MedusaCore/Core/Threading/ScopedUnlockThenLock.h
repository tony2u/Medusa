// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Threading/Mutex.h"

MEDUSA_BEGIN;

class ScopedUnlockThenLock
{
public:
	typedef Mutex MutexType;
public:
	ScopedUnlockThenLock(MutexType& mutex, bool unlockNow = true) :mMutex(mutex)
	{
		if (unlockNow)
		{
			mMutex.Unlock();
		}
	}

	~ScopedUnlockThenLock()
	{
		mMutex.Lock();
	}
private:
	ScopedUnlockThenLock(const ScopedUnlockThenLock &);
	ScopedUnlockThenLock& operator=(const ScopedUnlockThenLock &);
private:
	MutexType& mMutex;
};

MEDUSA_END;
