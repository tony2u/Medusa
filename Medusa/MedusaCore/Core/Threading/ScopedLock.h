// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Threading/Mutex.h"

MEDUSA_BEGIN;

class ScopedLock
{
public:
	typedef Mutex MutexType;
public:
	ScopedLock(MutexType& mutex) :mMutex(mutex)
	{
		mMutex.Lock();
	}

	ScopedLock(MutexType& mutex, long milliseconds) :mMutex(mutex)
	{
		mMutex.LockTimeout(milliseconds);
	}
	~ScopedLock()
	{
		mMutex.Unlock();
	}
private:
	ScopedLock(const ScopedLock &);
	ScopedLock& operator=(const ScopedLock &);
private:
	MutexType& mMutex;
};

MEDUSA_END;
