// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING

#include "Core/Threading/Semaphore.h"
#include "Core/Chrono/StopWatch.h"
#include "Core/Threading/Thread.h"

MEDUSA_BEGIN;

Semaphore::Semaphore(uint initialValue/*=0*/, uint maxLimit /*= Math::UIntMaxValue*/, bool isInitializeNow /*= true*/)
{
	if (isInitializeNow)
	{
		Initialize(initialValue, maxLimit);
	}
}

Semaphore::~Semaphore()
{
	Uninitialize();
}


void Semaphore::Initialize(uint initialValue/*=0*/, uint maxLimit /*= Math::UIntMaxValue*/)
{
#ifdef __APPLE__
    mSem = dispatch_semaphore_create(initialValue);
#else
   sem_init(&mSem, 0, initialValue);
#endif
}

void Semaphore::Uninitialize()
{
#ifdef __APPLE__
    dispatch_release(mSem);
#else
    sem_destroy(&mSem);
#endif

}


void Semaphore::Set(uint count)
{
	if (count == 1)
	{
#ifdef __APPLE__
        dispatch_semaphore_signal(mSem);
#else
        sem_post(&mSem);
#endif
        
		
	}
	else
	{
#if defined(MEDUSA_ANDROID)||defined(MEDUSA_IOS)
		//android has no sem_post_multiple
		FOR_EACH_SIZE(i, count)
		{
#ifdef __APPLE__
            dispatch_semaphore_signal(mSem);
#else
            sem_post(&mSem);
#endif
		}
#else
		sem_post_multiple(&mSem, count);
#endif
	}

}


void Semaphore::Set()
{
	Set(1);
}

bool Semaphore::Wait()
{
#ifdef __APPLE__
    dispatch_semaphore_wait(mSem, DISPATCH_TIME_FOREVER);
#else
   sem_wait(&mSem);
#endif
	return true;
}

bool Semaphore::WaitTimeout(long milliseconds)
{
	const int sleepMillis = 5;
	StopWatch watch;
	watch.Start();
	do
	{
		RETURN_TRUE_IF_TRUE(TryWait());
		Thread::Sleep(sleepMillis);
		watch.Shot();
	} while (watch.ElapsedMilliseconds() < milliseconds);
	return false;
}

bool Semaphore::TryWait()
{
#ifdef __APPLE__
    return dispatch_semaphore_wait(mSem, 0)==0;
#else
    return sem_trywait(&mSem) == 0;
#endif
    
	
}

MEDUSA_END;
#endif