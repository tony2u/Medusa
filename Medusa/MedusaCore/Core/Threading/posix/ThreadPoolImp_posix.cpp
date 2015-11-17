// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/posix/ThreadPoolImp_posix.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/System/Environment.h"
#include "Core/Threading/PooledThread.h"
MEDUSA_BEGIN;


ThreadPoolImp::ThreadPoolImp()
{
}

ThreadPoolImp::~ThreadPoolImp(void)
{

}

bool ThreadPoolImp::InitializeHelper(uint minCount /*= ThreadPoolImp::MinCount*/, uint maxCount /*= ThreadPoolImp::MaxCount*/, bool autoManaged /*= true*/)
{
	//default is 0-1500
	mMinThreadCount = Math::Max(minCount, 2U);
	mMaxThreadCount = maxCount;
	mThreadIdCount = 0;

	if (autoManaged)
	{
		uint cpuCount = Environment::Instance().GetCPUCount();
		mMinThreadCount = 2;
		mMaxThreadCount = cpuCount * 2 + 2;
	}

	FOR_EACH_SIZE(i, minCount)
	{
		PooledThread* thread = CreateThread();
		mAllThreads.Push(thread);
	}
	mIdleThreadCount = mMinThreadCount;

	return true;
}

void ThreadPoolImp::UninitialzieHelper()
{

}

void ThreadPoolImp::Enqueue(ICommand* command)
{
	//find a idle thread
	PooledThread* thread = EnqueueWorkToIdleThread(command);
	if (thread == nullptr)
	{
		//reach max thread count
		//insert into work queue and wait for invoking
		//we need these code because we may hit the point that all threads are busy without any work in queue, but we get a new work right now
		ScopedLock lock(mCommandQueueMutex);
		command->Retain();
		mCommands.MutableFront().Push(command);
	}
}


PooledThread* ThreadPoolImp::EnqueueWorkToIdleThread(ICommand* command)
{
	ScopedLock lock(mThreadMutex);
	PooledThread* thread = nullptr;
	if (mIdleThreadCount > 0)
	{
		uintp threadCount = mAllThreads.Count();
		FOR_EACH_SIZE(i, threadCount)
		{
			thread = mAllThreads[i];
			if (thread->IsIdle())
			{
				thread->Activate(command);
				return thread;
			}
		}
	}
	else
	{
		if (mAllThreads.Count() < mMaxThreadCount)
		{
			//create new thread
			thread = CreateThread();
			thread->Activate(command);
			mAllThreads.Push(thread);
		}
	}


	return thread;
}

PooledThread* ThreadPoolImp::CreateThread()
{
	HeapString threadName;
	threadName.Format("ThreadPool::{}", mThreadIdCount++);
	PooledThread* thread = new PooledThread(threadName, Bind(&ThreadPoolImp::OnPooledThreadComplete,this), this);
	thread->Start();
	mAllThreads.Push(thread);

	return thread;
}

bool ThreadPoolImp::OnPooledThreadComplete(PooledThread& thread)
{
	{
		//try to find work 
		ScopedLock lock(mCommandQueueMutex);
		CommandQueue::ValueRef commands = mCommands.MutableFront();
		if (!commands.IsEmpty())
		{
			ICommand* command = commands.PopWithReturn();
			thread.Activate(command);
			command->Release();
			return true;	//continue running
		}
	}

	{
		ScopedLock lock(mThreadMutex);
		//Note that at this time mIdleThreadCount not include self thread
		uintp allThreadCount = mAllThreads.Count();
		uintp busyThreadCount = allThreadCount - mIdleThreadCount;
		bool isReleaseSelf = false;
		if (busyThreadCount >= mMinThreadCount)
		{
			isReleaseSelf = true;
		}
		else
		{
			isReleaseSelf = mIdleThreadCount + 1 > (mMinThreadCount - busyThreadCount);	//+1 means self
		}

		if (isReleaseSelf)
		{
			PooledThread* p = &thread;
			mAllThreads.Remove(&thread);
			delete p;	//it's safe because we have lost current thread ref and won't run any code under this thread
			return false;
		}
		else
		{
			++mIdleThreadCount;
			return true;
		}
	}
}


void ThreadPoolImp::CancelPendingCommands(ICommand* command)
{
	ScopedLock lock(mCommandQueueMutex);
	CommandQueue::ValueRef commands = mCommands.MutableBack();

	RETURN_IF_EMPTY(commands);
	RETURN_IF_FALSE(commands.Contains(command));

	FOR_EACH_COLLECTION(i, commands)
	{
		ICommand* temp = *i;
		if (temp != command)
		{
			commands.Push(temp);
		}
		else
		{
			temp->Release();
		}
	}
	commands.Clear();
	mCommands.Swap();
}


MEDUSA_END;

#endif
