// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BaseFrameCommandProcessor.h"
#include "Core/Log/Log.h"
#include "Core/Command/ICommand.h"
#include "Core/Profile/PerformanceCounter.h"
#include "Core/Threading/ScopedLock.h"

MEDUSA_BEGIN;


BaseFrameCommandProcessor::BaseFrameCommandProcessor()
	:mThreadingDisabled(false), mIsFrameEnabled(false)
{

}

BaseFrameCommandProcessor::~BaseFrameCommandProcessor(void)
{
	Uninitialize();
}

bool BaseFrameCommandProcessor::Initialize(bool disableThreading/*=false*/)
{
	mThreadingDisabled = disableThreading;
	if (!mThreadingDisabled)
	{
		mThread.SetCallback(Bind(&BaseFrameCommandProcessor::OnThreadCallbackHelper, this));
		mInstantStartEvent.Initialize();
		mInstantCompleteEvent.Initialize();
		mFrameStartEvent.Initialize(false, false);

	}

	return true;
}

bool BaseFrameCommandProcessor::Uninitialize()
{
	StopAndClear();
	if (!mThreadingDisabled)
	{
		mInstantStartEvent.Uninitialize();
		mInstantCompleteEvent.Uninitialize();

	}
	return true;
}


void BaseFrameCommandProcessor::Clear()
{
	{
		ScopedLock lock(mInstantCommandMutex);
		mInstantCommands.Swap();
		OnProcessInstant();
	}


	{
		ScopedLock lock(mFrameCommandMutex);
		CommandQueue::ValueRef backCommands = mFrameCommands.MutableBack();
		SAFE_RELEASE_COLLECTION(backCommands);
		CommandQueue::ValueRef frontCommands = mFrameCommands.MutableFront();
		SAFE_RELEASE_COLLECTION(frontCommands);
	}

}


void BaseFrameCommandProcessor::StopAndClear()
{
	Stop();
	Clear();
}

void BaseFrameCommandProcessor::Start()
{
	if (!mThreadingDisabled)
	{
		mThread.Start();
	}
}

void BaseFrameCommandProcessor::Stop()
{
	RETURN_IF_TRUE(mThreadingDisabled);
	mThread.PrepareToCancel();

	mInstantStartEvent.Set();

	mThread.Join();
}

void BaseFrameCommandProcessor::ReceiveInstant(ICommand* command)
{
	RETURN_IF_NULL(command);

	if (mThreadingDisabled)
	{
		command->Execute();
	}
	else
	{
		{
			ScopedLock lock(mInstantCommandMutex);
			CommandQueue::ValueRef commands = mInstantCommands.MutableBack();
			commands.Push(command);
			SAFE_RETAIN(command);
		}


		mInstantStartEvent.Set();
	}

}

void BaseFrameCommandProcessor::ReceiveInstant(const List<ICommand*>& commands)
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
			ScopedLock lock(mInstantCommandMutex);
			CommandQueue::ValueRef myCommands = mInstantCommands.MutableBack();
			myCommands.AddRange(commands);
			SAFE_RETAIN_COLLECTION(commands);
		}


		mInstantStartEvent.Set();
	}
}


void BaseFrameCommandProcessor::ProcessInstant(ICommand* command)
{
	RETURN_IF_NULL(command);
	if (mThreadingDisabled)
	{
		command->Execute();
	}
	else
	{
		{
			ScopedLock lock(mInstantCommandMutex);
			CommandQueue::ValueRef commands = mInstantCommands.MutableBack();
			commands.Push(command);
			SAFE_RETAIN(command);
		}


		mInstantStartEvent.Set();

		WaitForInstantComplete();
	}
}


void BaseFrameCommandProcessor::ReceiveInstantAsync(ICommand* command)
{
	RETURN_IF_NULL(command);


	{
		ScopedLock lock(mInstantCommandMutex);
		CommandQueue::ValueRef commands = mInstantCommands.MutableBack();
		commands.Push(command);
		SAFE_RETAIN(command);
	}

	mInstantStartEvent.Set();

}

void BaseFrameCommandProcessor::ReceiveInstantAsync(const List<ICommand*>& commands)
{
	{
		ScopedLock lock(mInstantCommandMutex);
		CommandQueue::ValueRef myCommands = mInstantCommands.MutableBack();
		myCommands.AddRange(commands);
		SAFE_RETAIN_COLLECTION(commands);
	}

	mInstantStartEvent.Set();
}

void BaseFrameCommandProcessor::ReceiveFrame(ICommand* command)
{
	RETURN_IF_NULL(command);
	if (mThreadingDisabled)
	{
		command->Execute();
	}
	else
	{
		ScopedLock lock(mFrameCommandMutex);
		CommandQueue::ValueRef commands = mFrameCommands.MutableBack();
		commands.Push(command);
		SAFE_RETAIN(command);
	}
}

void BaseFrameCommandProcessor::ReceiveFrame(const List<ICommand*>& commands)
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
		ScopedLock lock(mFrameCommandMutex);
		CommandQueue::ValueRef myCommands = mFrameCommands.MutableBack();
		myCommands.AddRange(commands);
		SAFE_RETAIN_COLLECTION(commands);
	}
}

void BaseFrameCommandProcessor::ReceiveFrameAsync(ICommand* command)
{
	RETURN_IF_NULL(command);
	ScopedLock lock(mFrameCommandMutex);
	CommandQueue::ValueRef commands = mFrameCommands.MutableBack();
	commands.Push(command);
	SAFE_RETAIN(command);
}

void BaseFrameCommandProcessor::ReceiveFrameAsync(const List<ICommand*>& commands)
{
	ScopedLock lock(mFrameCommandMutex);
	CommandQueue::ValueRef myCommands = mFrameCommands.MutableBack();
	myCommands.AddRange(commands);
	SAFE_RETAIN_COLLECTION(commands);
}

void BaseFrameCommandProcessor::StartFrame()
{
	//start frame commands
	//stop instant commands
	if (!mThreadingDisabled)
	{
		mFrameStartEvent.Set();
		mInstantStartEvent.Set();
	}

}


void BaseFrameCommandProcessor::OnThreadCallbackHelper(Thread& thread)
{
	while (!thread.IsCancelled())
	{
		if (mFrameStartEvent.IsSet())
		{
			TrySwapFrameCommands();
			OnProcessFrame();
			mFrameStartEvent.Reset();
			mFrameCompleteEvent.Set();
		}
		else
		{
			mInstantStartEvent.Wait();

			{
				ScopedLock lock(mInstantCommandMutex);
				CommandQueue::ValueRef backCommands = mInstantCommands.MutableBack();
				if (!backCommands.IsEmpty())
				{
					mInstantCommands.Swap();
				}
			}

			OnProcessInstant();
			mInstantCompleteEvent.Set();
		}
	}

}

void BaseFrameCommandProcessor::TrySwapFrameCommands()
{
	ScopedLock lock(mFrameCommandMutex);
	CommandQueue::ConstValueRef backCommands = mFrameCommands.Back();
	if (!backCommands.IsEmpty())
	{
		CommandQueue::ValueRef frontCommands = mFrameCommands.MutableFront();
		SAFE_RELEASE_COLLECTION(frontCommands);
		mFrameCommands.Swap();
	}
}

void BaseFrameCommandProcessor::WaitForInstantComplete()
{
	if (mThreadingDisabled)
	{
		mInstantCommands.Swap();
		OnProcessInstant();
	}
	else
	{
		mInstantCompleteEvent.Wait();
	}

}

void BaseFrameCommandProcessor::OnProcessInstant()
{
	CommandQueue::ValueRef commands = mInstantCommands.MutableFront();
	FOR_EACH_COLLECTION(i, commands)
	{
		ICommand* command = *i;
		command->Execute();
		SAFE_RELEASE(command);
	}
	commands.Clear();
}

void BaseFrameCommandProcessor::OnProcessFrame()
{
	CommandQueue::ConstValueRef commands = mFrameCommands.Front();
	FOR_EACH_COLLECTION(i, commands)
	{
		ICommand* command = *i;
		command->Execute();
	}
}

void BaseFrameCommandProcessor::WaitForFrameComplete()
{
	if (mThreadingDisabled)
	{
		OnProcessFrame();
	}
	else
	{
		mFrameCompleteEvent.Wait();
	}
}





MEDUSA_END;