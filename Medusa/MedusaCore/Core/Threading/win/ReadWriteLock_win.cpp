// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING
#include "Core/Threading/ReadWriteLock.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Threading/Thread.h"

MEDUSA_BEGIN;

ReadWriteLock::ReadWriteLock(bool isInitializeNow /*= true*/)
{
	mLock.Ptr = nullptr;
	if (isInitializeNow)
	{
		Initialize();
	}
}

ReadWriteLock::~ReadWriteLock()
{
	Uninitialize();
}

void ReadWriteLock::Initialize()
{
	if (mLock.Ptr==nullptr)
	{
		InitializeSRWLock(&mLock);
	}
}

void ReadWriteLock::Uninitialize()
{
	//no need to destroy explicitly
}

void ReadWriteLock::BeginRead()
{
	AcquireSRWLockShared(&mLock);
}

bool ReadWriteLock::TryBeginRead()
{
	return TryAcquireSRWLockShared(&mLock) == TRUE;
}

bool ReadWriteLock::BeginReadTimeout(long milliseconds)
{
	const int sleepMillis = 5;
	StopWatch watch;
	watch.Start();
	do
	{
		RETURN_TRUE_IF_TRUE(TryBeginRead());
		Thread::Sleep(sleepMillis);
		watch.Shot();
	} while (watch.ElapsedMilliseconds() < milliseconds);
	return false;
}

void ReadWriteLock::EndRead()
{
	ReleaseSRWLockShared(&mLock);
}

void ReadWriteLock::BeginWrite()
{
	AcquireSRWLockExclusive(&mLock);
}

bool ReadWriteLock::TryBeginWrite()
{
	return TryAcquireSRWLockExclusive(&mLock) == TRUE;
}

bool ReadWriteLock::BeginWriteTimeout(long milliseconds)
{
	const int sleepMillis = 5;
	StopWatch watch;
	watch.Start();
	do
	{
		RETURN_TRUE_IF_TRUE(TryBeginWrite());
		Thread::Sleep(sleepMillis);
		watch.Shot();
	} while (watch.ElapsedMilliseconds() < milliseconds);
	return false;
}

void ReadWriteLock::EndWrite()
{
	ReleaseSRWLockExclusive(&mLock);
}



MEDUSA_END;
#endif
