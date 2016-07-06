// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Threading/Mutex.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;

class ScopedUnlock:public INonCopyable
{
public:
	typedef Mutex MutexType;
public:
	ScopedUnlock(MutexType& mutex) :mMutex(mutex)
	{
		
	}

	~ScopedUnlock()
	{
		mMutex.Unlock();
	}
private:
	MutexType& mMutex;
};

MEDUSA_END;
