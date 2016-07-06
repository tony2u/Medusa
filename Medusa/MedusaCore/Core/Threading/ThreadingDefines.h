// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "CorePlatform/CorePlatformDefines.h"
#include "CorePlatform/CommonMarcos.h"

MEDUSA_BEGIN;



enum class ThreadState
{
	None,
	Running,
	Cancelled
};

enum class ExecuteOption
{
	Sync,
	Async,
	Deferred
};

#ifndef MEDUSA_POSIX_THREADING


typedef HANDLE ThreadHandle;
typedef uint32 ThreadId;
typedef HANDLE ThreadNativeHandle;


enum class ThreadingSchedulePolicy
{
	Default,	//time split 
	FIFO,	//real time, fist in first run
	RR, //real time, time splice loop
	Min,
	SCHED_MAX
};

enum class ThreadPriority	//[IGNORE_PRE_DECLARE]
{
	Idle = THREAD_PRIORITY_IDLE,//-15
	Lowest = THREAD_PRIORITY_LOWEST,//-2
	Low = THREAD_PRIORITY_BELOW_NORMAL,//-1
	Normal = THREAD_PRIORITY_NORMAL,//0
	High = THREAD_PRIORITY_ABOVE_NORMAL,//1
	Highest = THREAD_PRIORITY_HIGHEST,//2
	Critical = THREAD_PRIORITY_TIME_CRITICAL,//15
};

class MutexImp
{
protected:
	CRITICAL_SECTION mMutex;
};


class SemaphoreImp
{
protected:
	HANDLE mSem;
};

class ReadWriteLockImp
{
protected:
	SRWLOCK mLock;
};


class ThreadImp
{
public:
	ThreadHandle Handle()const { return mThread; }
protected:
	ThreadHandle mThread;
	ThreadId mThreadId;
};

#endif

#if defined (MEDUSA_POSIX_THREADING) 



typedef pthread_t ThreadHandle;
typedef pthread_t ThreadId;
typedef pthread_t ThreadNativeHandle;

enum class ThreadingSchedulePolicy
{
	Default = SCHED_OTHER,	//time split 
	FIFO = SCHED_FIFO,	//real time, fist in first run
	RR = SCHED_RR, //real time, time splice loop
	Min = Default,
	SCHED_MAX = RR
};

enum class ThreadPriority	//[IGNORE_PRE_DECLARE]
{
	Idle,
	Lowest,
	Low,
	Normal,
	High,
	Highest,
	Critical,
};


class MutexImp
{
protected:
	pthread_mutex_t mMutex;
};

class SemaphoreImp
{
protected:
#ifdef __APPLE__
	dispatch_semaphore_t    mSem;
#else
	sem_t                   mSem;
#endif

};

class ReadWriteLockImp
{
protected:
	pthread_rwlock_t mLock;
};


class ThreadImp
{
public:
	ThreadHandle Handle()const { return mThread; }
protected:
	ThreadHandle mThread;
};


#endif


MEDUSA_END;
