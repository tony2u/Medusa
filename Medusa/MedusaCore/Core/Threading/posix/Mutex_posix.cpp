// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING

#include "Core/Threading/Mutex.h"
#include "Core/Chrono/DateTime.h"

#if defined(MEDUSA_IOS)
#include "Core/Chrono/StopWatch.h"
#include "Core/Threading/Thread.h"
#endif

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
	pthread_mutexattr_t attr;

	::pthread_mutexattr_init(&attr);
	::pthread_mutexattr_settype(&attr, isRecursive ? PTHREAD_MUTEX_RECURSIVE : PTHREAD_MUTEX_NORMAL);
	::pthread_mutex_init(&mMutex, &attr);
	::pthread_mutexattr_destroy(&attr);

	mIsInitialized = true;
}

void Mutex::Uninitialize()
{
	RETURN_IF_FALSE(mIsInitialized);
	::pthread_mutex_destroy(&mMutex);
	mIsInitialized = false;
}

void Mutex::Lock()
{
	::pthread_mutex_lock(&mMutex);
}


bool Mutex::TryLock()
{
	return ::pthread_mutex_trylock(&mMutex) == 0;
}

bool Mutex::TryLockFor(long milliseconds)
{
#if (defined(MEDUSA_ANDROID) && __ANDROID_API__<=19)
	return pthread_mutex_lock_timeout_np(&mMutex, milliseconds);
#elif defined(MEDUSA_IOS)
    const int sleepMillis = 5;
    StopWatch watch;
    watch.Start();
    do
    {
        RETURN_TRUE_IF_ZERO(pthread_mutex_trylock(&mMutex));
        Thread::Sleep(sleepMillis);
        watch.Shot();
    } while (watch.ElapsedMilliseconds() < milliseconds);
    return false;
#else
	struct timespec abstime = DateTime::ToAbsoluteTime(milliseconds);
	return pthread_mutex_timedlock(&mMutex, &abstime) == 0;
#endif
}


void Mutex::Unlock()
{
	::pthread_mutex_unlock(&mMutex);
}

MEDUSA_END;

#endif
