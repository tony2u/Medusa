// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/ReadWriteLock.h"
#include "Core/Profile/PerformanceCounter.h"

#if defined(MEDUSA_ANDROID)||defined(MEDUSA_IOS)
#include "Core/Profile/StopWatch.h"
#include "Core/Threading/Thread.h"
#endif
MEDUSA_BEGIN;

ReadWriteLock::ReadWriteLock(bool isInitializeNow /*= true*/)
{
	mLock = PTHREAD_RWLOCK_INITIALIZER;
	if (isInitializeNow)
	{
		Initialize();
	}
}

ReadWriteLock::~ReadWriteLock()
{
}

void ReadWriteLock::Initialize()
{
    pthread_rwlock_init(&mLock, nullptr);
}

void ReadWriteLock::Uninitialize()
{
    pthread_rwlock_destroy(&mLock);
    mLock = PTHREAD_RWLOCK_INITIALIZER;
}


void ReadWriteLock::BeginRead()
{
	::pthread_rwlock_rdlock(&mLock);
}

bool ReadWriteLock::TryBeginRead()
{
	return ::pthread_rwlock_tryrdlock(&mLock) == 0;
}

bool ReadWriteLock::BeginReadTimeout(long milliseconds)
{
#if defined(MEDUSA_ANDROID)||defined(MEDUSA_IOS)
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

#else
	struct timespec abstime = PerformanceCounter::ToAbsoluteTime(milliseconds);
	int result = pthread_rwlock_timedrdlock(&mLock, &abstime);
	return result == 0;
#endif
}

void ReadWriteLock::EndRead()
{
	pthread_rwlock_unlock(&mLock);
}

void ReadWriteLock::BeginWrite()
{
	pthread_rwlock_wrlock(&mLock);
}

bool ReadWriteLock::TryBeginWrite()
{
	return ::pthread_rwlock_trywrlock(&mLock) == 0;
}

bool ReadWriteLock::BeginWriteTimeout(long milliseconds)
{
#if defined(MEDUSA_ANDROID)||defined(MEDUSA_IOS)
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

#else
	struct timespec abstime = PerformanceCounter::ToAbsoluteTime(milliseconds);
	int result = pthread_rwlock_timedwrlock(&mLock, &abstime);
	return result == 0;
#endif

}

void ReadWriteLock::EndWrite()
{
	pthread_rwlock_unlock(&mLock);
}

MEDUSA_END;
#endif
