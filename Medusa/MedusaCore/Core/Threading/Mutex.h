// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "ThreadingDefines.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;


class Mutex :public MutexImp, public INonCopyable
{
	friend class ThreadEvent;
public:
	Mutex(bool isRecursive = true, bool isInitializeNow = true);
	~Mutex();

	void Initialize(bool isRecursive = true);
	void Uninitialize();
	void Lock();
	bool TryLock();
	bool TryLockFor(long milliseconds);

	void Unlock();
private:
	bool mIsInitialized = false;
};

/*
A not-recursive Mutex is similar to a Mutex,
which means that a deadlock will occur if the same
thread tries to lock a mutex it has already locked again.
Locking a not-recursive Mutex is faster than locking a recursive Mutex.
*/
class NonRecursiveMutex :public Mutex
{
public:
	NonRecursiveMutex(bool isInitializeNow = true)
		:Mutex(false, isInitializeNow)
	{
	}

};


/*
A not-recursive Mutex is similar to a Mutex,
which means that a deadlock will occur if the same
thread tries to lock a mutex it has already locked again.
Locking a not-recursive Mutex is faster than locking a recursive Mutex.
*/
class RecursiveMutex :public Mutex
{
public:
	RecursiveMutex(bool isInitializeNow = true)
		:Mutex(true, isInitializeNow)
	{
	}

};


class NoMutex :public INonCopyable
{
	friend class ThreadEvent;
public:
	NoMutex(bool isRecursive = true, bool isInitializeNow = true) {}
	~NoMutex() {}

	void Initialize(bool isRecursive = true) {}
	void Uninitialize() {}
	void Lock() {}
	bool TryLock() { return false; }
	bool LockTimeout(long milliseconds) { return false; }
	bool TryLockFor(long milliseconds) { return false; }

	void Unlock() {}
};

MEDUSA_END;
