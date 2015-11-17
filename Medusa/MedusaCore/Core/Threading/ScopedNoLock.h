// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Threading/Mutex.h"

MEDUSA_BEGIN;

class ScopedNoLock
{
public:
	typedef NoMutex MutexType;
public:
	ScopedNoLock(MutexType& mutex) :mMutex(mutex)
	{
		mMutex.Lock();
	}

	ScopedNoLock(MutexType& mutex, long milliseconds) :mMutex(mutex)
	{
		mMutex.LockTimeout(milliseconds);
	}
	~ScopedNoLock()
	{
		mMutex.Unlock();
	}
private:
	ScopedNoLock(const ScopedNoLock &);
	ScopedNoLock& operator=(const ScopedNoLock &);
private:
	MutexType& mMutex;
};

MEDUSA_END;
