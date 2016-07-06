// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Threading/Mutex.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;


template<typename THost>
class NoThreadingLockPolicy
{
public:
	class Lock :public INonCopyable
	{
	public:
		Lock(const THost&) {}
		Lock(const THost*) {}
		Lock() {}
		~Lock() {}
	};
};

template<typename THost>
class ClassThreadingLockPolicy
{
public:
	class Lock :public INonCopyable
	{
	public:
		Lock(const THost&) { mMutex.Lock(); }
		Lock(const THost*) { mMutex.Lock(); }
		Lock() { mMutex.Lock(); }
		~Lock() { mMutex.Unlock(); }
	};
private:
	static RecursiveMutex mMutex;
};

template<typename THost>
class ObjectThreadingLockPolicy
{
public:
	class Lock :public INonCopyable
	{
	public:
		Lock(const THost&) { mMutex.Lock(); }
		Lock(const THost*) { mMutex.Lock(); }
		~Lock() { mMutex.Unlock(); }
	private:
		RecursiveMutex mMutex;
	};
};

MEDUSA_END;
