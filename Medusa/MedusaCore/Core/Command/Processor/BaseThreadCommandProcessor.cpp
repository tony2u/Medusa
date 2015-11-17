// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BaseThreadCommandProcessor.h"
#include "Core/Log/Log.h"
#include "Core/Command/ICommand.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Threading/Thread.h"

MEDUSA_BEGIN;


BaseThreadCommandProcessor::BaseThreadCommandProcessor()
	:mThreadingDisabled(false)
{

}

BaseThreadCommandProcessor::~BaseThreadCommandProcessor(void)
{
	Uninitialize();
}

bool BaseThreadCommandProcessor::Initialize(bool disableThreading/*=false*/)
{
	mThreadingDisabled = disableThreading;
	if (!mThreadingDisabled)
	{
		mThread.SetCallback(Bind(&BaseThreadCommandProcessor::OnThreadCallbackHelper, this));
		mStartEvent.Initialize();
		mCompleteEvent.Initialize();
	}

	return true;
}

bool BaseThreadCommandProcessor::Uninitialize()
{
	StopAndClear();
	if (!mThreadingDisabled)
	{
		mStartEvent.Uninitialize();
		mCompleteEvent.Uninitialize();
	}
	return true;
}


void BaseThreadCommandProcessor::Clear()
{
	mCommands.Swap();
	OnProcess();
}


void BaseThreadCommandProcessor::StopAndClear()
{
	Stop();
	Clear();
}

void BaseThreadCommandProcessor::Start()
{
	if (!mThreadingDisabled)
	{
		mThread.Start();
	}
}

void BaseThreadCommandProcessor::Stop()
{
	RETURN_IF_TRUE(mThreadingDisabled);
	mThread.PrepareToCancel();

	mStartEvent.Set();

	mThread.Join();
}

void BaseThreadCommandProcessor::Receive(ICommand* command)
{
	RETURN_IF_NULL(command);

	if (mThreadingDisabled)
	{
		command->Execute();
	}
	else
	{
		{
			ScopedLock lock(mCommandMutex);
			CommandQueue::ValueRef commands = mCommands.MutableBack();
			commands.Push(command);
			SAFE_RETAIN(command);
		}


		mStartEvent.Set();
	}

}

void BaseThreadCommandProcessor::Receive(const List<ICommand*>& commands)
{
	if (mThreadingDisabled)
	{
		FOR_EACH_COLLECTION(i, commands)
		{
			ICommand* item = *i;
			item->Execute();
		}
	}
	else
	{
		{
			ScopedLock lock(mCommandMutex);
			CommandQueue::ValueRef myCommands = mCommands.MutableBack();
			myCommands.AddRange(commands);
			SAFE_RETAIN_COLLECTION(commands);
		}

		mStartEvent.Set();
	}
}

void BaseThreadCommandProcessor::ReceiveAsync(ICommand* command)
{
	RETURN_IF_NULL(command);

	{
		ScopedLock lock(mCommandMutex);
		CommandQueue::ValueRef commands = mCommands.MutableBack();
		commands.Push(command);
		SAFE_RETAIN(command);
	}


	mStartEvent.Set();
}

void BaseThreadCommandProcessor::ReceiveAsync(const List<ICommand*>& commands)
{
	{
		ScopedLock lock(mCommandMutex);

		CommandQueue::ValueRef myCommands = mCommands.MutableBack();
		myCommands.AddRange(commands);
		SAFE_RETAIN_COLLECTION(commands);
	}


	mStartEvent.Set();

}


void BaseThreadCommandProcessor::OnThreadCallbackHelper(Thread& thread)
{
	while (!thread.IsCancelled())
	{
		mStartEvent.Wait();

		{
			ScopedLock lock(mCommandMutex);
			mCommands.Swap();
		}

		OnProcess();
		mCompleteEvent.Set();
	}

}


void BaseThreadCommandProcessor::WaitForComplete()
{
	if (mThreadingDisabled)
	{
		mCommands.Swap();
		OnProcess();
	}
	else
	{
		mCompleteEvent.Wait();
	}

}

void BaseThreadCommandProcessor::OnProcess()
{
	CommandQueue::ValueRef commands = mCommands.MutableFront();
	FOR_EACH_COLLECTION(i, commands)
	{
		ICommand* command = *i;
		command->Execute();
		SAFE_RELEASE(command);
	}
	commands.Clear();
}


MEDUSA_END;