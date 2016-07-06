// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Threading/Mutex.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;

class ScopedLock:public INonCopyable
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
		mMutex.TryLockFor(milliseconds);
	}
	~ScopedLock()
	{
		mMutex.Unlock();
	}
private:
	MutexType& mMutex;
};

MEDUSA_END;
