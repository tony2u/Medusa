// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Threading/Thread.h"
#include "Core/Collection/List.h"
#include "Core/Threading/ThreadEvent.h"
#include "Core/Pattern/SwapValue.h"
#include "Core/Threading/Mutex.h"
#include "Core/Log/Log.h"
#include "Core/Command/ICommand.h"
#include "Core/Threading/ScopedLock.h"
MEDUSA_BEGIN;

template<typename TCommand>
class TFrameCommandExecutor:public Thread
{
	static_assert(std::is_same<ICommand, TCommand>::value || std::is_base_of<ICommand, TCommand>::value, "TCommand must inherit from ICommand");
	using CommandType = Share<TCommand>;
	typedef SwapValue<List<CommandType>> CommandQueue;
protected:
	TFrameCommandExecutor()
	{

	}
	virtual ~TFrameCommandExecutor(void)
	{
		Uninitialize();
	}
public:
	virtual bool Initialize(bool disableThreading = false)
	{
		mThreadingDisabled = disableThreading;
		if (!mThreadingDisabled)
		{
			mInstantStartEvent.Initialize();
			mInstantCompleteEvent.Initialize();
			mFrameStartEvent.Initialize(false, false);

		}

		return true;
	}
	virtual bool Uninitialize()
	{
		StopAndClear();
		if (!mThreadingDisabled)
		{
			mInstantStartEvent.Uninitialize();
			mInstantCompleteEvent.Uninitialize();

		}
		return true;
	}
public:
	void Clear()
	{
		{
			ScopedLock lock(mInstantCommandMutex);
			mInstantCommands.Swap();
			OnProcessInstant();
		}


		{
			ScopedLock lock(mFrameCommandMutex);
			mFrameCommands.MutableBack().Clear();
			mFrameCommands.MutableFront().Clear();
		}
	}
	void StopAndClear()
	{
		Join();
		Clear();
	}

	void ExecuteInstant(const CommandType& command)
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
				commands.Add(command);
			}


			mInstantStartEvent.Set();
		}
	}
	void ExecuteInstantAsync(const CommandType& command)
	{
		RETURN_IF_NULL(command);


		{
			ScopedLock lock(mInstantCommandMutex);
			CommandQueue::ValueRef commands = mInstantCommands.MutableBack();
			commands.Add(command);
		}

		mInstantStartEvent.Set();
	}
	void ProcessInstant(const CommandType& command)
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
				commands.Add(command);
			}


			mInstantStartEvent.Set();

			WaitForInstantComplete();
		}
	}

	void ExecuteInstant(const List<CommandType>& commands)
	{
		if (mThreadingDisabled)
		{
			for (auto item : commands)
			{
				item->Execute();
			}
		}
		else
		{
			{
				ScopedLock lock(mInstantCommandMutex);
				CommandQueue::ValueRef myCommands = mInstantCommands.MutableBack();
				myCommands.AddRange(commands);
			}


			mInstantStartEvent.Set();
		}
	}
	void ExecuteInstantAsync(const List<CommandType>& commands)
	{
		{
			ScopedLock lock(mInstantCommandMutex);
			CommandQueue::ValueRef myCommands = mInstantCommands.MutableBack();
			myCommands.AddRange(commands);
		}

		mInstantStartEvent.Set();
	}


	void ExecuteFrame(const CommandType& command)
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
			commands.Add(command);
		}
	}
	void ExecuteFrameAsync(const CommandType& command)
	{
		RETURN_IF_NULL(command);
		ScopedLock lock(mFrameCommandMutex);
		CommandQueue::ValueRef commands = mFrameCommands.MutableBack();
		commands.Add(command);
	}

	void ExecuteFrame(const List<CommandType>& commands)
	{
		if (mThreadingDisabled)
		{
			for (auto item : commands)
			{
				item->Execute();
			}
		}
		else
		{
			ScopedLock lock(mFrameCommandMutex);
			CommandQueue::ValueRef myCommands = mFrameCommands.MutableBack();
			myCommands.AddRange(commands);
		}
	}
	void ExecuteFrameAsync(const List<CommandType>& commands)
	{
		ScopedLock lock(mFrameCommandMutex);
		CommandQueue::ValueRef myCommands = mFrameCommands.MutableBack();
		myCommands.AddRange(commands);
	}
	void StartFrame()
	{
		//start frame commands
		//stop instant commands
		if (!mThreadingDisabled)
		{
			mFrameStartEvent.Set();
			mInstantStartEvent.Set();
		}
	}

	void WaitForInstantComplete()
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
	void WaitForFrameComplete()
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
protected:
	virtual bool OnBeforeStart() { return !mThreadingDisabled; }
	virtual bool OnBeforeJoin()
	{
		RETURN_FALSE_IF_TRUE(mThreadingDisabled);
		PrepareToCancel();
		mInstantStartEvent.Set();
		return true;
	}

	void OnProcessInstant()
	{
		CommandQueue::ValueRef commands = mInstantCommands.MutableFront();
		for (auto& command : commands)
		{
			command->Execute();
		}
		commands.Clear();
	}
	void OnProcessFrame()
	{
		CommandQueue::ConstValueRef commands = mFrameCommands.Front();
		for (auto& command : commands)
		{
			command->Execute();
		}
	}


	virtual void OnRun()
	{
		while (!IsCancelled())
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
	void TrySwapFrameCommands()
	{
		ScopedLock lock(mFrameCommandMutex);
		CommandQueue::ConstValueRef backCommands = mFrameCommands.Back();
		if (!backCommands.IsEmpty())
		{
			 mFrameCommands.MutableFront().Clear();
			mFrameCommands.Swap();
		}
	}
protected:
	CommandQueue mInstantCommands;
	NonRecursiveMutex mInstantCommandMutex;
	ThreadEvent mInstantStartEvent;
	ThreadEvent mInstantCompleteEvent;


	CommandQueue mFrameCommands;
	NonRecursiveMutex mFrameCommandMutex;

	ThreadEvent mFrameStartEvent;
	ThreadEvent mFrameCompleteEvent;


	bool mThreadingDisabled=false;
	volatile bool mIsFrameEnabled=false;
};



MEDUSA_END;