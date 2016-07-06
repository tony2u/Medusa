// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING

#include "Core/Threading/Mutex.h"
#include "Core/Chrono/StopWatch.h"
#include "Core/Threading/Thread.h"

MEDUSA_BEGIN;

Mutex::Mutex(bool isRecursive /*= true*/, bool isInitializeNow /*= true*/)
{
	if (isInitializeNow)
	{
		Initialize(isRecursive);
	}
}

Mutex::~Mutex()
{
	Uninitialize();
}

void Mutex::Initialize(bool isRecursive /*= true*/)
{
	RETURN_IF_TRUE(mIsInitialized);
	InitializeCriticalSectionAndSpinCount(&mMutex, 4000);
	mIsInitialized = true;
}

void Mutex::Uninitialize()
{
	RETURN_IF_FALSE(mIsInitialized);
	DeleteCriticalSection(&mMutex);
	mIsInitialized = false;
}

void Mutex::Lock()
{
	EnterCriticalSection(&mMutex);

}

bool Mutex::TryLock()
{
	return TryEnterCriticalSection(&mMutex) == TRUE;
}

bool Mutex::TryLockFor(long milliseconds)
{
	const int sleepMillis = 5;
	StopWatch watch;
	watch.Start();
	do
	{
		RETURN_TRUE_IF_TRUE(TryLock());
		Thread::Sleep(sleepMillis);
		watch.Shot();
	} while (watch.ElapsedMilliseconds() < milliseconds);
	return false;
}

void Mutex::Unlock()
{
	LeaveCriticalSection(&mMutex);
}

MEDUSA_END;

#endif
