// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Threading/Mutex.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;

class ScopedNoLock:public INonCopyable
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
	MutexType& mMutex;
};

MEDUSA_END;
